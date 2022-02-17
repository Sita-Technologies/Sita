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

#define _CRT_SECURE_NO_WARNINGS

#include "COutline.hpp"
#include "helper.hpp"
#include "item.hpp"
#include "system_variables.hpp"
#include "commandline_args.hpp"
#include <stdio.h>
#include <string.h>
#ifdef __unix__ 
#include <dirent.h>
#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
#pragma comment (lib, "Shlwapi.lib")
#include <shlwapi.h>
#include <direct.h>
#else
#error "neither Unix nor Windows environment defined"
#endif
#include <sys/stat.h>

// alpha version
// TODO: complete DispatchFunction
// TODO: Sal-Functions (like SalMessageBox etc.): expected datatypes of parameters, return value datatype
// TODO: Sal-Functions: fix long function names in sal_functions.hpp:INT_LOCALS (they are cut)
// TODO: ext-fun-calls: dynamic calls as well as expected datatypes of parameters
// TODO: improve support of variable scopes: 0x01 (when does it fail??), 0x02 (On ...), 0x04 (item.cpp: support more types in CObject::get_class), ...
// TODO: find out in which cases these var scopes are used and support them: 0x06, 0x09, 0x0a, 0x0b, 0x0d (what about scope 0x0c? does it even exist?)
// TODO: handle empty object-references in PutCheck, GetCheck, PutString, ..... --> direct reference to object containing the command
// TODO: line-number in tagITEM-flag: deal with overflows ;; how to deal with MAC or LINUX linebreaks??
// TODO: item.cpp:CObject::get_class: play around with different object/class types since structure WINATTR is not understood yet
// TODO: restore apl-files from .exe??
// TODO: fix resource dumping;; output .app file, .apl files, and resources into one folder
// TODO: external functions: datatypes (LPLONG, TEMPLATE, ...)
// TODO: work on FIXMEs in all source files
// TODO: replace exceptions on type-error by warnings (if -v flag is set) in decompile.cpp

// beta version
// TODO: test and support other versions than opentext Gupta Team Developer 7.2.0 // check "Outline Version" // what about string-encoding? is it always UTF-16?
// TODO: support 64bit apps
// TODO: analyze Object Nationalizer string language/translation table
// TODO: try to detect Sal Constants (like e.g. MB_OK in SalMessageBox calls) and replace Numbers by these constants
// TODO: WM_-constants: compare with dumped constants

// release version
// TODO: remove -v commandline flag
// TODO: const string --> replace later occuring string references by name of const variable?
// TODO: display all relevant item-body-elements, e.g. "Window Default" settings or "Design-time Settings"
// TODO: item body: attributes/properties [WINATTR]
// TODO: sanity: detect and leave infinite loops when processing next_sibling, child, and item pointers.
// TODO: work on TODOs in all source files
// TODO: check exception handling, work on memory alloc and free

#define SITA_VERSION "0.1-alpha_pre"

void print_indent(uint32_t indent) {
	for (uint32_t i=0; i<indent; i++) {
		oputs(" ");
	}
}

void iterate_items(COutline& outline, uint32_t item, uint32_t indention, uint32_t* parent_memory_item, bool first_pass = false) {
	uint16_t last_sibling = 0;
	while (item) {

		uint32_t memory_item[0x20];
		if (parent_memory_item) {
			memcpy(memory_item,parent_memory_item,sizeof(uint32_t)*0x20);
		}else{
			memset(memory_item,0,sizeof(uint32_t)*0x20);
		}

		tagITEM* p_item = outline.get_item(item);
		if (!p_item) {
			return;
		}

		uint32_t deref = outline.item_pointer_dereference(item);
		if (deref && deref != item) {

			if (is_verbose() && !first_pass) {
				print_indent(indention);
				oprintf("%04x.%04x: ",item>>16,item&0xFFFF);
				oprintf("[0x%04x]",p_item->type);
				oprintf("(flgs:0x%08x)",p_item->flags);
				oputs("<NULL> ");
				tag_items[p_item->type]->print(&outline,item,memory_item);
				oputs("\n");
			}

			iterate_items(outline,deref,indention, memory_item, first_pass);
		}else if (p_item->type != Item::Type::POINTER){
			if (first_pass) {
				if (p_item->type < TAG_ITEMS_AMOUNT) {
					tag_items[p_item->type]->first_pass(&outline,item, memory_item);
				}
			}else{
				if (p_item->type < TAG_ITEMS_AMOUNT) {
					tag_items[p_item->type]->preprocess(&outline,item,memory_item);
				}

				print_indent(indention);
				if (is_verbose()) {
					oprintf("%04x.%04x: ",item>>16,item&0xFFFF);
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

				if (get_app_output_filename() && p_item->type < TAG_ITEMS_AMOUNT) {
					tag_items[p_item->type]->decompile(&outline,item,memory_item);
					p_item = outline.get_item(item);
				}
			}
		}else{

			if (is_verbose() && !first_pass) {
				print_indent(indention);
				oprintf("%04x.%04x: ",item>>16,item&0xFFFF);
				oprintf("[0x%04x]",p_item->type);
				oprintf("(flgs:0x%08x)",p_item->flags);
				oputs("<NULL_noref> ");
				tag_items[p_item->type]->print(&outline,item,memory_item);
				oputs("\n");
			}
		}

		if (!first_pass && get_app_output_filename()) {
			CItem::remove_itembody(&outline,item,0x30); // childlinecount
			CItem::remove_itembody(&outline,item,0x31); // previtem (recompute)
			// insert previtem
			if (last_sibling) {
				struct ItemBody item_body;
				item_body.type = 0x31;
				item_body.size = last_sibling;
				CItem::add_itembody(&outline,item,&item_body);
			}
		}

		uint32_t next;
		next = outline.child_item(item);
		if (next) {
			iterate_items(outline, next,indention+(outline.get_item(item)->type == Item::Type::POINTER?0:1),memory_item,first_pass);
		}

		p_item = outline.get_item(item); // repair after possible size-changing in recursive call
		if (p_item->type < TAG_ITEMS_AMOUNT) {
			tag_items[p_item->type]->postprocess(&outline,item,first_pass?NULL:memory_item);
		}

		next = outline.next_item(item);
		last_sibling = (item & 0xffff);
		item = next;
	}
}

void create_dir_if_not_exists(const char* dirname) {
	if (!dirname) {
		return;
	}
	if (!*dirname) {
		return;
	}

#ifdef __unix__ 
	DIR* dir = opendir(dirname);
	if (dir) {
	    closedir(dir);
	    return;
	}else{
		if (mkdir(dirname,0755)==-1) {
			fprintf(stderr,"cannot create directory %s\n",dirname);
			exit(1);
		}else{
			return;
		}
	}
#else
	if (!PathIsDirectoryA(dirname)) {
		_mkdir(dirname);
	}
#endif
}

int main(int argc, char** argv) {
	puts("opensource Sita Team Decompiler " SITA_VERSION "\n");

	if (!parse_command_line(argc, argv)) {
		print_usage(*argv);
		return 1;
	}

	if (!get_input_filename()) {
		fprintf(stderr,"fatal: parse_command_line returned true, but input filename was not set\n");
		return 1;
	}

	FILE* td = 0;
	td = fopen(get_input_filename(), "rb");
	if (!td) {
		fprintf(stderr,"cannot open file %s\n",get_input_filename());
		return 1;
	}

	create_dir_if_not_exists(get_item_dump_dir());
	create_dir_if_not_exists(get_resource_dump_dir());

	struct outstream out;
	out.buf = NULL;
	out.f = stdout;
	out.pos = 0;
	oset(out);

	init_system_vars();
	COutline outline(td);


	if (is_verbose()) {
		oprintf("Information about %s:\n",argv[argc-1]);
		outline.print_stats();
	}
	if (outline.get_file_hdr().flags & FLAG_IS_64BIT) {
		fprintf(stderr,"error: 64bit binaries are not supported\n");
		exit(1); // 64bit not supported
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
		// create .app file
		FILE* app_output = fopen(get_app_output_filename(),"w+b");
		if (!app_output) {
			fprintf(stderr,"cannot write to file %s\n",get_app_output_filename());
			return 1;
		}
		outline.save(app_output);
		fclose(app_output);
	}
	return 0;
}
