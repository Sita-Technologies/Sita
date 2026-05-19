/**
 * This file is part of Sita Team Decompiler.
 *
 * Sita Team Decompiler is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 *
 * Sita Team Decompiler is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Sita Team Decompiler. If not, see
 * <https://www.gnu.org/licenses/>.
 */

#include "process_outline.hpp"

#include "helper.hpp"
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <map>
#include <vector>
#include <string>

#ifdef __unix__
#include <unistd.h>
#endif

// Distinguish a true inherited class-child from a class-instance control
// with its own override.
//
// CLASSCHILDOFFSET (body 0x21) is 8 bytes (2× uint32). The first word is the
// offset into the base class's slot table:
//   - Truly inherited (derived class re-declaration): first word NON-ZERO,
//     points at the base-class slot. cbi -c re-creates the item via the
//     `Derived From` chain; emitting the text declaration causes
//     "Duplicate symbol" at cbi -b time. Skip in text mode.
//   - Class-template instance (instance of a class with its own per-control
//     override): body 0x21 is still present on every child control of the
//     instance, but its first word is ZERO — the instance owns its slot, no
//     back-pointer needed. Must NOT skip: the override's Message Actions /
//     handler body is its own subtree and we'd lose the entire compiled
//     SAL bytecode.
//
// Defined under a unique name per build so the 32-bit / 64-bit translation
// units don't collide at link time.
#ifdef TDx64
#define IS_INHERITED_CHILD_REF_FN is_inherited_child_ref64
#else
#define IS_INHERITED_CHILD_REF_FN is_inherited_child_ref
#endif
static bool IS_INHERITED_CHILD_REF_FN(class COutline& outline, uint64_t item) {
	struct ItemBody* ib = CItem::get_itembody(&outline, item, 0x21);
	if (!ib) return false;
	if (ib->size < 8) return false;
	uint32_t offset_word = *((uint32_t*)((uint8_t*)ib + 1));
	return offset_word != 0;
}

#ifndef TDx64
// Emit the outline-level prefix `.head <indent> -  ` so each item's line is
// directly compatible with the TD `.apt` text format (UTF-8/LF still — the
// final encoding wrapper handles UTF-16LE/BOM/CRLF). One side effect: when
// an item's print() emits an embedded `\n` (the Application Description's
// title+body string, or a multi-line SAL string literal in code), the
// continuation line(s) appear bare with no `.head` prefix — exactly what
// `.apt` requires for Application Description body and multi-line strings.
// `print_indent` runs once per item, so it only prefixes the first line.
void print_indent(uint32_t indent) {
	oprintf(".head %u -  ", indent);
}
#endif

// ===== Project-mode state and helpers =====
//
// File index 0 is the main file; indices >= 1 are libraries discovered by
// walking FILE_INCLUDE (item type 0x83) directives. Each item's
// `proj_membership` entry is a bitmap: bit i set means the item should appear
// in proj_files[i]. Library items get exactly one bit (their own); main items
// get bit 0 plus any bits required as synthetic parents for descendant
// library items (so a "External Functions" header in main will also appear in
// any .apl that contributes children to that section).

namespace {

struct ProjectFile {
	std::string path;            // absolute output path
	char* buf;                   // text buffer (UTF-8 LF, grown via realloc)
	bool text_mode;              // true => convert to UTF-16LE+BOM+CRLF on close
};

// Per-item membership over an arbitrary number of project files. Word 0 =
// bits 0..63, word 1 = bits 64..127, etc. Length = ceil(file_count/64),
// with trailing zero-words elided (helpers tolerate short bitmaps as "the
// rest is 0").
typedef std::vector<uint64_t> BitMap;

inline void bm_set(BitMap& b, int idx) {
	int w = idx >> 6;
	if ((int)b.size() <= w) b.resize(w + 1, 0);
	b[w] |= (1ULL << (idx & 63));
}

inline bool bm_test(const BitMap& b, int idx) {
	int w = idx >> 6;
	if ((int)b.size() <= w) return false;
	return (b[w] & (1ULL << (idx & 63))) != 0;
}

inline void bm_or(BitMap& dst, const BitMap& src) {
	if (dst.size() < src.size()) dst.resize(src.size(), 0);
	for (size_t i = 0; i < src.size(); i++) dst[i] |= src[i];
}

inline void bm_clear_main(BitMap& b) {
	if (!b.empty()) b[0] &= ~(uint64_t)1;
}

// Set bits 1..(file_count-1) — every lib but main. Used by force_skeleton_into_libs.
inline BitMap bm_all_libs(int file_count) {
	BitMap b;
	if (file_count <= 1) return b;
	int last_w = (file_count - 1) >> 6;
	b.assign((size_t)(last_w + 1), 0);
	for (int w = 0; w < last_w; w++) b[w] = ~(uint64_t)0;
	int rem = file_count - (last_w << 6);  // bits in last word: 1..64
	b[last_w] = (rem == 64) ? ~(uint64_t)0 : ((1ULL << rem) - 1);
	b[0] &= ~(uint64_t)1;  // exclude main
	return b;
}

struct ProjectState {
	bool active = false;
	std::vector<ProjectFile> files;                // [0] = main; [1..] = libs
	std::map<uint64_t, int> lib_index_by_hitem;    // FILE_INCLUDE item_id → file idx
	std::map<uint64_t, BitMap> membership;         // item_id → multi-word file bitmap
};

ProjectState g_proj;

// Read the INCLUDEHITEM (0x10) body of an item; 0 if not present.
uint32_t read_includehitem(COutline& outline, uint64_t item_id) {
	struct ItemBody* ib = CItem::get_itembody(&outline, item_id, 0x10);
	if (!ib) return 0;
	return *((uint32_t*)((uint8_t*)ib + 1));
}

// Decode the TEXT (0x01) body of an item from UTF-16LE to UTF-8.
std::string read_text_utf8(COutline& outline, uint64_t item_id) {
	struct ItemBody* tb = CItem::get_itembody(&outline, item_id, 0x01);
	if (!tb) return std::string();
	const char16_t* src = (const char16_t*)tb->data;
	size_t chars = tb->size / 2;
	std::string out;
	for (size_t i = 0; i < chars; i++) {
		uint16_t c = src[i];
		if (c == 0) break;
		if (c < 0x80) {
			out.push_back((char)c);
		} else if (c < 0x800) {
			out.push_back((char)(0xc0 | (c >> 6)));
			out.push_back((char)(0x80 | (c & 0x3f)));
		} else {
			out.push_back((char)(0xe0 | (c >> 12)));
			out.push_back((char)(0x80 | ((c >> 6) & 0x3f)));
			out.push_back((char)(0x80 | (c & 0x3f)));
		}
	}
	return out;
}

// Walk the outline tree once, find every FILE_INCLUDE (0x83) item, register
// it as a library output. Recurse into children to pick up nested library
// includes (a library .apl can include another .apl; in the compiled binary
// the directive item itself is inlined, so it's reachable via tree walk).
void discover_libs_recursive(COutline& outline, uint64_t item, const std::string& project_dir, bool text_mode) {
	while (item) {
		tagITEM* p = outline.get_item(item);
		if (p && p->type == Item::Type::FILE_INCLUDE) {
			std::string raw = read_text_utf8(outline, item);
			std::string rel;
			if (sanitize_relpath(raw, rel)) {
				std::string full = project_dir + "/" + rel;
				mkdir_parents(full);

				ProjectFile pf;
				pf.path = full;
				pf.buf = (char*)malloc(1);
				pf.buf[0] = 0;
				pf.text_mode = text_mode;
				int idx = (int)g_proj.files.size();
				g_proj.files.push_back(pf);
				g_proj.lib_index_by_hitem[item] = idx;
				fprintf(stderr,"library: %s -> %s\n", raw.c_str(), full.c_str());
			} else {
				fprintf(stderr,"warning: rejecting unsafe library path \"%s\" (path traversal protection)\n", raw.c_str());
			}
		}
		uint64_t deref = outline.item_pointer_dereference(item);
		if (deref && deref != item) {
			discover_libs_recursive(outline, deref, project_dir, text_mode);
		}
		uint64_t child = outline.child_item(item);
		if (child) discover_libs_recursive(outline, child, project_dir, text_mode);
		item = outline.next_item(item);
	}
}

// Post-order walk: for each item, compute the bitmap of files it should
// appear in. Library items inherit their lib-id down through descendants
// that don't carry their own INCLUDEHITEM; main items aggregate their
// descendants' lib bits so they show up as synthetic parents in those libs.
BitMap compute_membership_recursive(COutline& outline, uint64_t item, uint32_t inherited_lib_hitem) {
	BitMap aggregate;
	while (item) {
		uint32_t my_inc = read_includehitem(outline, item);
		uint32_t my_lib_hitem = my_inc != 0 ? my_inc : inherited_lib_hitem;

		// `Symbol Import:` (item type 0x028f / EXT_LIBRARY) declarations
		// must live exclusively in main's `External Assemblies` block —
		// cbi -c rejects them inside any `.apl` with "This item type is not
		// allowed here". Their INCLUDEHITEM back-points to whichever typed-
		// lib FILE_INCLUDE brought the symbol in, but that's a provenance
		// link, not the declaration's home. Force such items (and any
		// inheritance to descendants — though Symbol Import: is a leaf in
		// practice) to route to main only.
		tagITEM* p_type_check = outline.get_item(item);
		if (p_type_check && p_type_check->type == Item::Type::EXT_LIBRARY) {
			my_lib_hitem = 0;
		}

		int my_idx = 0;  // default: main
		if (my_lib_hitem != 0) {
			auto it = g_proj.lib_index_by_hitem.find(my_lib_hitem);
			if (it != g_proj.lib_index_by_hitem.end()) {
				my_idx = it->second;
			}
			// else: unknown lib, fall back to main (idx 0)
		}

		BitMap descendant;
		uint64_t deref = outline.item_pointer_dereference(item);
		if (deref && deref != item) {
			BitMap sub = compute_membership_recursive(outline, deref, my_lib_hitem);
			bm_or(descendant, sub);
		}
		uint64_t child = outline.child_item(item);
		if (child) {
			BitMap sub = compute_membership_recursive(outline, child, my_lib_hitem);
			bm_or(descendant, sub);
		}

		BitMap result;
		bm_set(result, my_idx);
		if (my_lib_hitem == 0) {
			// main item: stays in main, plus any lib bits coming from descendants
			bm_clear_main(descendant);  // strip bit 0; my_idx=0 already covers main
			bm_or(result, descendant);
		}
		// else: library item — own lib only (nested includes handled via my_inc above)
		g_proj.membership[item] = result;
		bm_or(aggregate, result);

		item = outline.next_item(item);
	}
	return aggregate;
}

// Walk the outline tree and clear the TEXT (path) body of every
// FILE_INCLUDE directive (top-level + nested). Used by single-file
// **text** mode (`-t`) where library content is inlined into the
// emitted `.apt` and text has no per-item import-flag marker — leaving
// any path intact would tell cbi -c to re-merge the adjacent `.apl`,
// causing `Duplicate symbol` against the inlined copy. With every path
// cleared, cbi -c treats every directive as a no-op and relies entirely
// on the inlined content.
//
// NOT used for `-a` (binary): the per-item import flag (tagITEM bit
// 0x400, preserved through `is_remove_importflag()=false`) lets cbi -b
// distinguish inlined items from to-be-merged ones; clearing paths
// there would actually break cbi -b's bytecode resolution chain for
// transitively-imported symbols.
//
// NOT used for project modes (`-p` / `-P`) which keep every path so
// cbi resolves the adjacent split `.apl` files.
void clear_file_include_paths(COutline& outline, uint64_t item) {
	while (item) {
		tagITEM* p = outline.get_item(item);
		if (!p) break;
		if (p->type == Item::Type::FILE_INCLUDE) {
			CItem::remove_itembody(&outline, item, 0x01);
		}
		uint64_t deref = outline.item_pointer_dereference(item);
		if (deref && deref != item) {
			clear_file_include_paths(outline, deref);
		}
		uint64_t child = outline.child_item(item);
		if (child) {
			clear_file_include_paths(outline, child);
		}
		item = outline.next_item(item);
	}
}

// Force the structural skeleton items (Outline Version, Design-time Settings,
// Libraries, Global Declarations, Window Defaults) into every library's
// membership bitmap. Without these, cbi -c silently rejects the .apl as a
// structural error: only the Application Description and content-bearing
// sections like External Functions are pulled in by the descendant-aggregation
// rule, but cbi requires the full top-level skeleton to be present.
//
// `dt_subtree` toggles when we descend into Design-time Settings — every item
// in that subtree gets the full lib-bit set so the settings rows appear in
// the .apl. Window Defaults and Libraries are forced as headers only: their
// children (main-app default styles, FILE_INCLUDE directives) stay main-only.
//
// Global Declarations is forced as a header too — Window Defaults (item
// type 0xe4) is a child of Global Declarations (0x7c) in the outline tree,
// so a forced empty Window Defaults inside an .apl whose Global Declarations
// didn't pick up a lib-bit via descendant-aggregation (typical for shell-
// only .apls that contain nothing but nested `File Include:` directives)
// would emit at .head 2 with no `.head 1 - Global Declarations` parent —
// cbi -c rejects with "Item type not allowed here". Forcing the parent
// header keeps the structure consistent for shell-only and content-bearing
// libs alike.
void force_skeleton_into_libs(COutline& outline, uint64_t item, bool dt_subtree) {
	if (g_proj.files.size() < 2) return;
	BitMap all_lib_bits = bm_all_libs((int)g_proj.files.size());
	while (item) {
		tagITEM* p = outline.get_item(item);
		if (!p) break;
		bool descend_dt = dt_subtree;
		bool force_header = dt_subtree;
		switch (p->type) {
			case Item::Type::OUTLINE_VERSION:
			case Item::Type::LIBRARIES:
			case Item::Type::GLOBAL_DECLARATIONS:
			case Item::Type::WINDOW_DEFAULTS:
				force_header = true;
				break;
			case Item::Type::DESIGNTIME_SETTINGS:
				force_header = true;
				descend_dt = true;
				break;
			default:
				break;
		}
		if (force_header) {
			bm_or(g_proj.membership[item], all_lib_bits);
		}
		uint64_t deref = outline.item_pointer_dereference(item);
		if (deref && deref != item) {
			force_skeleton_into_libs(outline, deref, descend_dt);
		}
		uint64_t child = outline.child_item(item);
		if (child) {
			force_skeleton_into_libs(outline, child, descend_dt);
		}
		item = outline.next_item(item);
	}
}

// Compose the main file's path: <project_dir>/<input-basename>.<ext>.
std::string main_output_path(const char* project_dir, const char* input_filename, bool text_mode) {
	std::string base = input_filename ? input_filename : "out";
	size_t slash = base.find_last_of("/\\");
	if (slash != std::string::npos) base = base.substr(slash + 1);
	size_t dot = base.find_last_of('.');
	if (dot != std::string::npos) base = base.substr(0, dot);
	std::string ext = text_mode ? ".apt" : ".app";
	return std::string(project_dir) + "/" + base + ext;
}

void project_finalize() {
	// Flush all text-mode files. Libraries always emit as .apt-shaped UTF-16
	// per the .apl convention; the main file matches the project's mode.
	for (size_t i = 0; i < g_proj.files.size(); i++) {
		ProjectFile& pf = g_proj.files[i];
		if (!pf.buf) continue;
		bool ok = false;
		if (pf.text_mode || i >= 1) {
			// All libraries (i >= 1) emit as text .apl regardless of mode —
			// binary library synthesis is deferred (cbi accepts text .apl).
			ok = write_utf16_apt(pf.path.c_str(), pf.buf);
		} else {
			// Main file in text mode (i == 0 and pf.text_mode true) handled
			// above. Binary main is written separately via outline.save().
			ok = write_utf16_apt(pf.path.c_str(), pf.buf);
		}
		if (!ok) fprintf(stderr,"warning: failed to write %s\n", pf.path.c_str());
		free(pf.buf);
		pf.buf = NULL;
		fprintf(stderr,"wrote %s\n", pf.path.c_str());
	}
}

} // namespace

void iterate_items(COutline& outline, uint64_t item, uint32_t indention, uint64_t* parent_memory_item, bool first_pass) {
	uint32_t last_sibling = 0;
	while (item) {

		uint64_t memory_item[0x20];
		if (parent_memory_item) {
			memcpy(memory_item,parent_memory_item,sizeof(uint64_t)*0x20);
		}else{
			memset(memory_item,0,sizeof(uint64_t)*0x20);
		}

		tagITEM* p_item = outline.get_item(item);
		if (!p_item) {
			return;
		}

		uint64_t deref = outline.item_pointer_dereference(item);
		if (deref && deref != item) {

			if (is_verbose() && !first_pass) {
				print_indent(indention);
				oprintf("%04x.%04x: ",item>>ITEM_ID_WIDTH,item&((1LL<<ITEM_ID_WIDTH)-1LL));
				oprintf("[0x%04x]",p_item->type);
				oprintf("(flgs:0x%08x)",p_item->flags);
				oputs("<NULL> ");
				tag_items[p_item->type]->print(&outline,item,memory_item);
				oputs("\n");
			}

			iterate_items(outline,deref,indention, memory_item, first_pass);
		}else if (p_item->type != Item::Type::POINTER){
			// Dynalink declarations have no working text-form representation
			// in cbi: -c accepts them under Variables / Internal Functions
			// silently, but -b later crashes in OamDynLibAllocImportItem(NULL)
			// because the (HLIBSAL, ORDINAL) binding to the parent Dynalib is
			// binary-only. Suppress text output AND child-recursion for any
			// item whose type-name starts with "Dynalink ". Binary modes
			// (-a / -p) still emit normally. first_pass is left running so
			// addvar/symbol-table registration keeps populating the
			// dynamlib_map for refs at other call sites.
			bool dynalink_skip = !first_pass
				&& !is_binary_app_output()
				&& p_item->type < TAG_ITEMS_AMOUNT
				&& tag_items[p_item->type]->get_name()
				&& strncmp(tag_items[p_item->type]->get_name(), "Dynalink ", 9) == 0;
			// Inherited class-child items have a CLASSCHILDOFFSET body (0x21)
			// pointing at the base class's slot; cbi -c writes them implicitly
			// via the class's `Derived From` chain, so re-emitting them in
			// text mode causes "Duplicate symbol" at cbi -b time. Skip in
			// text mode; binary modes (-a / -p) keep the explicit reference.
			//
			// Refinement: instance controls on a Form Window that is itself
			// an instance of a class template ALSO carry body 0x21, but with
			// the offset-word zeroed (the instance owns its slot — no back-
			// pointer to a base class). Discriminator lives in
			// `is_inherited_child_ref()`.
			bool inherited_child_skip = !first_pass
				&& !is_binary_app_output()
				&& IS_INHERITED_CHILD_REF_FN(outline, item);
			// `External Assemblies` (0x28e) and its `Symbol Import:` (0x28f)
			// children are binary-only — cbi -c rejects them in any text
			// placement with modal "This item type is not allowed here". Skip
			// in text mode; binary modes (-a / -p) preserve them via
			// outline.save() in the main outline (the routing in
			// compute_membership_recursive keeps them out of any text `.apl`
			// even when -p emits binary main + text libraries).
			bool symbol_import_skip = !first_pass
				&& !is_binary_app_output()
				&& (p_item->type == Item::Type::EXTERNAL_ASSEMBLIES
				    || p_item->type == Item::Type::EXT_LIBRARY);
			if (first_pass) {
				if (p_item->type < TAG_ITEMS_AMOUNT) {
					tag_items[p_item->type]->first_pass(&outline,item, memory_item);
				}
			}else if (dynalink_skip || inherited_child_skip || symbol_import_skip) {
				// fall through to next-sibling — skip print + recurse
			}else{
				if (p_item->type < TAG_ITEMS_AMOUNT) {
					tag_items[p_item->type]->preprocess(&outline,item,memory_item);
				}

				if (g_proj.active) {
					// Project mode: emit the item's text into one or more
					// per-file buffers based on its membership bitmap. Pure-
					// library items emit to one file; synthetic-parent main
					// items (those that contain library children) emit to
					// every file that needs them.
					const BitMap& bits = g_proj.membership[item];
					int file_count = (int)g_proj.files.size();
					for (int idx = 0; idx < file_count; idx++) {
						if (!bm_test(bits, idx)) continue;
						struct outstream out;
						out.f = NULL;
						out.buf = &g_proj.files[idx].buf;
						out.pos = strlen(g_proj.files[idx].buf);
						oset(out);
						print_indent(indention);
						if (is_verbose()) {
							oprintf("%04x.%04x: ",item>>ITEM_ID_WIDTH,item&((1LL<<ITEM_ID_WIDTH)-1LL));
							oprintf("[0x%04x]",p_item->type);
							oprintf("(flgs:0x%08x)",p_item->flags);
						}
						if (p_item->type >= TAG_ITEMS_AMOUNT) {
							oputs("???");
						}else{
							tag_items[p_item->type]->print(&outline,item,memory_item);
						}
						if (p_item->flags & 0x1000) {
							oputs(" !__Exported");
						}
						oputs("\n");
						if (p_item->type < TAG_ITEMS_AMOUNT) {
							tag_items[p_item->type]->print_extra_lines(&outline, item, indention);
						}
					}
					// Leave the outstream pointed at the main buffer so that
					// any stray oputs from postprocess goes somewhere safe.
					struct outstream out0;
					out0.f = NULL;
					out0.buf = &g_proj.files[0].buf;
					out0.pos = strlen(g_proj.files[0].buf);
					oset(out0);
				} else if (!get_app_output_filename() || is_verbose()) {
					print_indent(indention);
					if (is_verbose()) {
						oprintf("%04x.%04x: ",item>>ITEM_ID_WIDTH,item&((1LL<<ITEM_ID_WIDTH)-1LL));
						oprintf("[0x%04x]",p_item->type);
						oprintf("(flgs:0x%08x)",p_item->flags);
					}
					if (p_item->type >= TAG_ITEMS_AMOUNT) {
						oputs("???");
					}else{
						tag_items[p_item->type]->print(&outline,item,memory_item);
					}
					if (p_item->flags & 0x1000) {
						oputs(" !__Exported");
					}
					oputs("\n");
					if (p_item->type < TAG_ITEMS_AMOUNT) {
						tag_items[p_item->type]->print_extra_lines(&outline, item, indention);
					}
				}

				if (is_binary_app_output() && p_item->type < TAG_ITEMS_AMOUNT) {
					tag_items[p_item->type]->decompile(&outline,item,memory_item);
					p_item = outline.get_item(item);
				}
			}
		}else{
			if (is_verbose() && !first_pass && !get_app_output_filename()) {
				print_indent(indention);
				oprintf("%04x.%04x: ",item>>ITEM_ID_WIDTH,item&((1LL<<ITEM_ID_WIDTH)-1LL));
				oprintf("[0x%04x]",p_item->type);
				oprintf("(flgs:0x%08x)",p_item->flags);
				oputs("<NULL_noref> ");
				tag_items[p_item->type]->print(&outline,item,memory_item);
				oputs("\n");
			}
		}

		bool single_file_out = !first_pass && get_app_output_filename();
		bool project_bin_out = !first_pass && get_project_dir() && !is_project_text_mode();
		if (single_file_out || project_bin_out) {
			CItem::remove_itembody(&outline,item,0x30); // childlinecount
			CItem::remove_itembody(&outline,item,0x31); // previtem (recompute)
			// Strip compile-time-computed bodies — cbi -c-built .app's never
			// have these; cbi -b recomputes them. Leaving them in can cause
			// "Duplicate symbol" errors and other merge issues when cbi -b
			// resolves File Include from an adjacent .apl.
			CItem::remove_itembody(&outline,item,0x2c); // DT_MAKERUNDLG
			CItem::remove_itembody(&outline,item,0x2e); // COMPILER_STRUCT
			CItem::remove_itembody(&outline,item,0x2f); // COMPILER_INT
			CItem::remove_itembody(&outline,item,0x33); // VAROFFSET
			// ARRAYBOUNDS (0x0f) and MDARRAYBOUNDS (0x28) are runtime-only
			// bodies — source-form `.app` doesn't carry them; cbi -b
			// rebuilds them at compile time from the `[*]` / `[N]` /
			// `[lo:hi]` array suffix that lives in the variable's name
			// (body 0x01 TEXT). Sita reads them from the input `.exe` but
			// must drop them on `-a` output — leaving them in causes cbi -b
			// to mis-bind references with "Array variable expected" errors
			// (the array suffix in body 0x01 is added by `decompile_helper`
			// / `CItem::decompile`).
			CItem::remove_itembody(&outline,item,0x0f); // ARRAYBOUNDS
			CItem::remove_itembody(&outline,item,0x28); // MDARRAYBOUNDS
			// insert previtem
			if (last_sibling) {
				uint8_t tmp[5];
				memset(tmp,0,5);
				tmp[0] = 0x31;
				memcpy(tmp+1,&last_sibling,CItem::itembody_elementsize((struct ItemBody*)tmp));
				CItem::add_itembody(&outline,item,(struct ItemBody*)tmp);
			}
		}

		uint64_t next;
		next = outline.child_item(item);
		// Mirror the print-skip above: skip child recursion for Dynalink
		// items in text mode (children at .head L+1 would otherwise dangle
		// without their parent header).
		bool dynalink_skip_recurse = !first_pass
			&& !is_binary_app_output()
			&& p_item
			&& p_item->type < TAG_ITEMS_AMOUNT
			&& tag_items[p_item->type]->get_name()
			&& strncmp(tag_items[p_item->type]->get_name(), "Dynalink ", 9) == 0;
		// Mirror the print-skip above for inherited class-children.
		bool inherited_child_skip_recurse = !first_pass
			&& !is_binary_app_output()
			&& IS_INHERITED_CHILD_REF_FN(outline, item);
		// Mirror the print-skip above for External Assemblies and
		// Symbol Import: items in text mode.
		bool symbol_import_skip_recurse = !first_pass
			&& !is_binary_app_output()
			&& p_item
			&& (p_item->type == Item::Type::EXTERNAL_ASSEMBLIES
			    || p_item->type == Item::Type::EXT_LIBRARY);
		if (next && !dynalink_skip_recurse && !inherited_child_skip_recurse && !symbol_import_skip_recurse) {
			iterate_items(outline, next,indention+(outline.get_item(item)->type == Item::Type::POINTER?0:1),memory_item,first_pass);
		}

		p_item = outline.get_item(item); // repair after possible size-changing in recursive call
		if (p_item->type < TAG_ITEMS_AMOUNT) {
			tag_items[p_item->type]->postprocess(&outline,item,first_pass?NULL:memory_item);
		}

		next = outline.next_item(item);
		last_sibling = (item & (((1LL<<ITEM_ID_WIDTH)-1LL)));
		item = next;
	}
}

bool process_outline(COutline& outline) {
	if (is_verbose()) {
		oprintf("Information about %s:\n",get_input_filename());
		outline.print_stats();
	}

	// Project mode: discover libraries, set up output buffers, run iteration
	// with per-item routing. For -p (binary main), we additionally invoke
	// outline.save() with a "skip library items" pass; for -P (text main),
	// the main buffer is flushed as UTF-16 .apt alongside the libraries.
	if (get_project_dir()) {
		bool text_mode = is_project_text_mode();

		// File 0 = main
		ProjectFile main_pf;
		main_pf.path = main_output_path(get_project_dir(), get_input_filename(), text_mode);
		main_pf.buf = (char*)malloc(1);
		main_pf.buf[0] = 0;
		main_pf.text_mode = text_mode;
		g_proj.files.push_back(main_pf);

		discover_libs_recursive(outline, outline.top_item(), get_project_dir(), text_mode);
		compute_membership_recursive(outline, outline.top_item(), 0);
		force_skeleton_into_libs(outline, outline.top_item(), false);
		g_proj.active = true;

		// Run first_pass once to populate state; output redirection doesn't
		// affect first_pass since it doesn't print.
		struct outstream sink;
		sink.f = stderr; // first_pass shouldn't print anything except in -v
		sink.buf = NULL;
		sink.pos = 0;
		oset(sink);
		iterate_items(outline,outline.top_item(),0,NULL, true);

		// Print pass; iterate_items reads g_proj.* and routes per item.
		iterate_items(outline,outline.top_item(),0,NULL);

		g_proj.active = false;
		project_finalize();

		if (!text_mode) {
			// Binary main: write a .app via outline.save() with library items
			// suppressed. Two granularities cooperate:
			//   - Whole-segment suppress for segments where every member is
			//     library-only — efficient (HItem entry zeroed, no heap walk).
			//   - Per-item suppress for items that share a segment with main
			//     items (e.g. `Symbol Import: vtmisc` in segment 0x0002 of
			//     WikiSample). save() consults outline.suppressed_items inside
			//     the heap-block loop and skips matching tagITEMs.
			// The File Include directive itself stays — it's a main item with
			// bit 0 set (it lives in main, the lib content is what gets pulled
			// in elsewhere).
			std::map<uint32_t, uint64_t> segment_bits;
			// Note: we deliberately do NOT suppress library content from the
			// binary main. Source `.app`s (cbi -c output) carry library
			// content inlined alongside the File Include directive, and
			// cbi -b distinguishes the inlined version from the adjacent
			// `.apl` via the per-item import flag (tagITEM bit 0x400, set on
			// items with INCLUDEHITEM). With `is_remove_importflag()`
			// returning false, the flag survives through save() and cbi -b
			// recognises the inlined content as already-merged. Suppressing
			// library segments breaks main bytecode references into them
			// and triggers cbi -b crashes; the .apl emitted alongside is
			// for human source-style viewing/editing.
			(void)segment_bits;

			FILE* app_output = fopen(main_pf.path.c_str(),"w+b");
			if (app_output) {
				outline.save(app_output);
				fclose(app_output);
				fprintf(stderr,"binary main written to %s (libraries emitted as text .apl)\n", main_pf.path.c_str());
			} else {
				fprintf(stderr,"cannot write to app file %s\n", main_pf.path.c_str());
			}
		}

		g_proj.files.clear();
		g_proj.lib_index_by_hitem.clear();
		g_proj.membership.clear();
		return true;
	}

	if (get_app_output_filename() || !get_resource_dump_dir()) {
		// `-t` only: clear FILE_INCLUDE paths so cbi -c on the emitted
		// `.apt` doesn't try to merge an adjacent `.apl` against the
		// inlined library content (text format has no per-item import
		// flag to distinguish them, unlike `-a`'s binary path).
		if (get_apt_output_filename() && !get_app_output_filename()) {
			clear_file_include_paths(outline, outline.top_item());
		}

		iterate_items(outline,outline.top_item(),0,NULL, true);
		iterate_items(outline,outline.top_item(),0,NULL);

		if (is_verbose()) {
			oputs("\n=== STRING TABLE ===\n");
			uint32_t string_id = 0;
			const struct String* str = outline.string_lookup(string_id);
			while (str) {
				oprintf("0x%08x: ",string_id);
				print_utf16(str->str, str->len);
				oputs("\n");
				str = outline.string_lookup(++string_id);
			}
		}
		if (get_app_output_filename()) {
			FILE* app_output = fopen(get_app_output_filename(),"w+b");
			if (!app_output) {
				fprintf(stderr,"cannot write to app file %s\n",get_app_output_filename());
				return false;
			}
			outline.save(app_output);
			fclose(app_output);
			printf("decompiled app written to app file %s\n",get_app_output_filename());
		}
	}
	return true;
}
