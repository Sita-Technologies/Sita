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
#include "process_outline.hpp"
#define TDx64
#include "COutline.hpp"
#include "process_outline.hpp"
#undef TDx64
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

#include "undef64.inc"

// alpha version
// TODO: improve support for 64bit apps
// TODO: complete DispatchFunction
// TODO: foreach-Statement of TD7.4: what about the CODE itembody? do we need it? how to use labels??
// TODO: Sal-Functions (like SalMessageBox etc.): expected datatypes of parameters, return value datatype
// TODO: ext-fun-calls: dynamic calls as well as expected datatypes of parameters
// TODO: improve support of variable scopes: 0x02 (On ...), 0x04 (item.cpp: support more types in CObject::get_class), 0x08 (this scope fails sometimes)
// TODO: find out in which cases these var scopes are used and support them: 0x06, 0x09, 0x0a, 0x0b, 0x0d (what about scope 0x0c? does it even exist?)
// TODO: handle empty object-references in PutCheck, GetCheck, PutString, ..... --> direct reference to object containing the command???
// TODO: item.cpp:CObject::get_class: play around with different object/class types since structure WINATTR is not understood yet
// TODO: line-number in tagITEM-flag: deal with overflows ;; how to deal with MAC or LINUX linebreaks?
// TODO: external functions: datatypes (LPLONG, TEMPLATE, ...)
// TODO: check hstringtable compression type == 0x3; try to force TD to abstain from compression for specific test exe file -- if successful, test with this file
// TODO: work on FIXMEs in all source files

// beta version
// TODO: analyze Object Nationalizer string language/translation table
// TODO: try to detect Sal Constants (like e.g. MB_OK in SalMessageBox calls) and replace Numbers by these constants
// TODO: WM_-constants: compare with dumped constants
// TODO: extract apl-files as separate files
// TODO: fix resource dumping;; output .app file, .apl files, and resources into one folder

// release version
// TODO: remove -v commandline flag
// TODO: const string --> replace later occuring string references by name of const variable?
// TODO: display all relevant item-body-elements, e.g. "Window Default" settings or "Design-time Settings"
// TODO: item body: attributes/properties [WINATTR]
// TODO: sanity: detect and quit infinite loops when processing next_sibling, child, and item pointers.
// TODO: work on TODOs in all source files
// TODO: check exception handling, work on memory alloc and free

#define SITA_VERSION "0.1-alpha_pre3"

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
		print_usage(argc>0?*argv:"Sita");
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

	if (outline.get_file_hdr().version < VERSION_TD51) {
		fprintf(stderr,"error: binaries created with TD before version 5.1 are not supported\n");
		exit(1); // versions before TD 5.1 not supported
	}
	if (outline.get_file_hdr().flags & FLAG_IS_64BIT) {
		if (outline.get_file_hdr().version < VERSION_TD70) {
			fprintf(stderr,"error: 64bit flag set for binary created with TD before version 7.0\n");
			exit(1);
		}
		// load as 64bit binary
		COutline64 outline(td);
		return process_outline(outline)?0:1;
	}

	// process 32bit binary
	return process_outline(outline)?0:1;
}
