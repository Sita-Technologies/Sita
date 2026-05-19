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

#undef INC_ITEM_HPP_
#ifndef TDx64
#ifndef OUTLINE_HPP_
#define INC_ITEM_HPP_
#define OUTLINE_HPP_
#endif
#endif

#ifdef TDx64
#ifndef OUTLINE64_HPP_
#define INC_ITEM_HPP_
#define OUTLINE64_HPP_
#endif
#endif

#ifdef INC_ITEM_HPP_
#include "outline_decs.hpp"
#include "item.hpp"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <set>

#include "def64.inc"

#ifdef TDx64
#undef HANDTABLE_ITEMSIZE_MASK
#define HANDTABLE_ITEMSIZE_MASK 0x03ffffff
#undef ITEM_ID_WIDTH
#define ITEM_ID_WIDTH 32
#else
#define HANDTABLE_ITEMSIZE_MASK 0x3fff
#define ITEM_ID_WIDTH 16
#endif


#ifndef TDx64
struct SymbolLookup{
	uint32_t hitem;
	uint8_t* str;
	struct SymbolLookup* next;
};
#endif

class COutline {
private:
	FILE* handle = NULL;
	struct FileHdr file_hdr;
	struct Outline* outline = NULL;
	SymbolHash symbol_hash;
	char* ax_lib_info = NULL;
	char* class_relationships = NULL;
	char* co_class_list = NULL;
	struct CompressionHeader cmphdr;
	struct StringTable* string_table = NULL;
	struct tagOSEG** tag_oseg = NULL;
	struct HandTable** hand_table = NULL;
	struct tagPERMSYM*** symbols = NULL;
	char* str_data = NULL;
	struct ClassMap {
		uint32_t size;
		uint64_t* item;
	} class_map = {0, NULL};
	struct OrdinalMap {
		uint32_t size;
		uint64_t* item;
	};
	struct DynalibMap {
		uint32_t size;
		struct OrdinalMap* ordinal_map;
	} dynamlib_map = {0, NULL};
	std::map<uint64_t, uint64_t> item_loop_info = std::map<uint64_t, uint64_t>();
	// Item ids (full 32-bit / 64-bit form: seginf<<ITEM_ID_WIDTH | handle) that
	// save() should skip when emitting the segment heap-block chain. Used by
	// project-mode -p to drop individual library items that share a segment
	// with main items (segment-level suppress_segment cannot be used there).
	std::set<uint64_t> suppressed_items = std::set<uint64_t>();
	// dialog_dlgitems[dialog_item_id][dlgitem_operand] = control_item_id
	//   - dialog_item_id and control_item_id are full 64-bit item ids on
	//     x64 (truncating to 32-bit loses the seg half).
	//   - dlgitem_operand is the 32-bit control identifier from the SAL
	//     bytecode (uint32 in both arches).
	std::map<uint64_t, std::map<uint32_t, uint64_t>> dialog_dlgitems = std::map<uint64_t, std::map<uint32_t, uint64_t>>();
	// Reverse map: handler item id (an `On <event>` item) → owning class
	// item id. Built by walking every item with a CLASS_MSGS body 0x12 and
	// parsing the (msgcode, target_handler_item, fn_ptr) entries inside.
	// Used by `decompile.cpp:ExtFunction` to resolve the class-ref operand
	// of `@RunBaseClassMsg(...)` (opcode 0x119/0x1bc) — that operand points
	// at a per-class handler item, not at the user-visible class symbol.
	std::map<uint64_t, uint64_t> handler_to_class_map = std::map<uint64_t, uint64_t>();
	// Per control-instance type → owning class definition's item id.
	// The text writer always emits `Class: <name>` for control instances
	// (Custom Control / Data Field / etc.); without it the linker can't bind
	// `obj.member` accesses ("Symbol is undefined" / "Undefined function").
	// Built once at preprocess time by walking the outline, finding all
	// CClass-derived class definitions and grouping by the control type
	// they're a class for; if a control type has exactly ONE class definition
	// (or one selected via Default Classes), the binding is unambiguous.
	std::map<uint16_t, uint64_t> default_class_for_control_type = std::map<uint16_t, uint64_t>();

	long OsReadFast(unsigned long length, char* result);
	// if compressed == NULL: read from file this->handle
	unsigned long OsDeCompress(unsigned long output_len, void* decompressed, unsigned long input_len, void* compressed = NULL);
	struct HandTable* create_handtable(struct tagOSEG* item_content, uint64_t item_id);
	void init_symbol_lookup();
	void init_class_msgs_map();
	void init_dynalink_function_map();

	uint8_t is_null(struct SalNumber* num);
	void print_flag(uint32_t flag, const char* flag_name);
	void print_stat(uint32_t value, const char* name);

	// helper function for find-children-call
	uint32_t find_siblings_of_type_and_run(void (*callback)(class COutline* outline, uint64_t item, void* param), void* param, uint64_t item, const uint16_t* type, bool only_one_match);

public:
	struct RuntimeMemoryScope* get_memory(uint64_t item_id, varscope scope);
	COutline(FILE* handle);

	uint64_t top_item();
	/**
	 * get next sibling
	 */
	uint64_t next_item(uint64_t item_id);
	/**
	 * get child
	 */
	uint64_t child_item(uint64_t item_id);
	tagITEM* get_item(uint64_t item_id);
	uint64_t item_pointer_dereference(uint64_t item);

	void add_class_item(uint64_t class_id, uint64_t item_id);
	uint64_t get_class_item(uint64_t class_id);

	// Register `class_def_item` as a class definition for control instances
	// of type `control_type`. Called from CClass::first_pass once per class
	// definition. If multiple class definitions register for the same control
	// type, the most recently registered wins ("first class declared" heuristic).
	void register_class_for_control_type(uint16_t control_type, uint64_t class_def_item);
	// Returns the class definition's item id for control instances of
	// `control_type`, or 0 if no class is registered (instances render
	// without a `Class:` line).
	uint64_t get_default_class_for_control_type(uint16_t control_type);

	// Raw access to a sub-handle's heap-block data within an OSEG segment.
	// Used to read auxiliary (non-tagITEM) heap blocks like the class-name
	// string referenced by a FunctionalVar's WINATTR handle_id. Returns NULL
	// if seginf or handle_id are out of range. The pointer is the start of
	// the heap-block payload (i.e. just after the tagHEAPBLK header).
	uint8_t* get_handle_data(uint32_t seginf, uint32_t handle_id);

	// Total size in bytes of a handle's heap-block payload (excludes the
	// tagHEAPBLK header). Returns 0 for invalid seginf/handle_id. Used by
	// the WINATTR string-handle scan to bound-check the raw block before
	// reading its length-prefixed UTF-16LE payload.
	uint32_t get_handle_data_size(uint32_t seginf, uint32_t handle_id);

	// True iff the handle's block carries a tagITEM header (HANDTABLE_ITEMSIZE_MASK+1
	// bit set on the size field). False for raw heap blocks (HString, length-prefixed
	// strings used as Title / Status Text values, etc.). Used by the WINATTR-
	// handle scan to discriminate string handles from item handles.
	bool is_handle_tagitem(uint32_t seginf, uint32_t handle_id);

	// Maximum used handle id within an OSEG segment (1..maxUsedHandle is the
	// valid range for WINATTR-embedded handle ids). Returns 0 if seginf is
	// invalid or the segment is missing.
	uint32_t get_max_handle(uint32_t seginf);

	void add_dynalib_var(uint16_t libsal, uint16_t ordinal, uint64_t item);
	uint64_t get_dynalib_var(uint16_t libsal, uint16_t ordinal);

	void set_item_loop_info(uint64_t item, uint64_t data);
	uint64_t get_item_loop_info(uint64_t item);

	void set_dialog_dlgitem(uint64_t dialog, uint32_t dlgitem, uint64_t item);
	uint64_t get_dialog_dlgitem(uint64_t dialog, uint32_t dlgitem);
	// Search all registered dialogs for `dlgitem`. Returns the unique item
	// if exactly one dialog registered it; returns 0 if no match or
	// multiple matches. For resolving `hWndForm.<ctrl>` in Internal
	// Functions where the enclosing form is unknown at compile time.
	uint64_t find_unique_dlgitem(uint32_t dlgitem);

	uint64_t insert_item(uint32_t seginf);

	bool add_variable(uint64_t item_id, enum varscope scope, uint16_t offset, uint64_t reference);
	uint64_t lookup_variable(uint64_t item_id, enum varscope scope, uint16_t offset, bool print_namespace = false);
	bool has_any_variable(uint64_t item_id, varscope scope);

	/**
	 * only direct children (not recursive)
	 * type: 0-terminated array
	 * returns number of performed callback-calls
	 */
	uint32_t find_children_of_type_and_run(void (*callback)(class COutline* outline, uint64_t item, void* param), void* param, uint64_t item, const uint16_t* type, bool only_one_match = true);

	const char16_t* symbol_lookup(uint64_t item_id);
	// Look up the owning class for a handler item id (the bytecode-side
	// operand 1 of `@RunBaseClassMsg(...)` references a per-class `On <event>`
	// handler item, not the class itself). Returns 0 if the handler isn't
	// registered in any class's CLASS_MSGS table.
	uint64_t class_for_handler(uint64_t handler_item_id);
	// Resolve a PERMSYM name by its flat position in the symbol-hash table
	// (flat_index = j * 0x97 + bucket). The compiler emits bytecode
	// references by flat index for class-member dereferences like
	// `hWnd.<name>`; at runtime the resolver walks the bucket and matches
	// by hItemOwner against the hWnd's class. For decompilation we only
	// need the symbol name, which is identical across matching PERMSYMs.
	const char16_t* permsym_name_by_flat_index(uint32_t flat_index);
	uint64_t permsym_item_by_flat_index(uint32_t flat_index);
	// Late-bound `..method` overload disambiguation: walk every permsym in
	// the bucket whose name matches the j-th permsym's, and prefer one whose
	// hItem has a Parameters (0x89) subtree with exactly `expected_arg_count`
	// children. Falls back to the j-th permsym if no better match is found.
	// Returns 0 if the flat-index is invalid.
	uint64_t permsym_item_by_flat_and_arity(uint32_t flat_index, uint8_t expected_arg_count);
	const struct String* string_lookup(uint32_t string_id);
	void sprint_number(char out[300], struct SalNumber* num);
	void sprint_date(char out[32], struct SalNumber* num);

	bool change_item_size(uint64_t item_id, uint32_t new_size);

	// handle must be a handle to a file opened in "w+b" or "r+b" mode;
	// writing starts at current stream position
	// retruns number of bytes written
	uint32_t save(FILE* handle);

	// Mark a segment as suppressed: save() will emit an empty HItem entry for
	// it (offset=0, size=0). Used by project-mode -p output to drop entire
	// library segments from the main .app while keeping the outline-level
	// File Include directive in place. seginf is the high half of a 32-bit
	// item id (item_id >> ITEM_ID_WIDTH).
	void suppress_segment(uint32_t seginf);

	// Mark a single item (full id) for suppression in save(). The item's
	// tagITEM heap block is dropped from its segment's heap chain; auxiliary
	// blocks belonging to the item (strings, ItemBody data) are not followed
	// — they remain as orphans inside the segment but are unreachable. For
	// segment-level removal use suppress_segment() instead (more efficient).
	void suppress_item(uint64_t item_id);

	void print_stats();
	struct FileHdr get_file_hdr();
};

#endif /* OUTLINE_HPP_ */
#undef INC_ITEM_HPP_
