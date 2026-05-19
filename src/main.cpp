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

#define SITA_VERSION "0.9"

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
	// Banner goes to stderr so stdout stays a valid `.apt` text stream
	// (UTF-8/LF, .head-prefixed).
	fprintf(stderr,"opensource Sita Team Decompiler " SITA_VERSION "\n\n");

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
	create_dir_if_not_exists(get_project_dir());

	// For -t, buffer output in memory then convert UTF-8/LF → UTF-16LE+BOM+CRLF
	// at the end (the encoding `cbi -c` expects). Without -t we stream UTF-8/LF
	// directly to stdout.
	char* apt_buf = NULL;
	struct outstream out;
	out.buf = NULL;
	out.f = stdout;
	out.pos = 0;
	if (get_apt_output_filename()) {
		apt_buf = (char*)malloc(1);
		if (!apt_buf) {
			fprintf(stderr,"cannot allocate output buffer\n");
			return 1;
		}
		apt_buf[0] = 0;
		out.f = NULL;
		out.buf = &apt_buf;
	}
	oset(out);

	COutline outline(td);

	if (outline.get_file_hdr().version < VERSION_TD51) {
		fprintf(stderr,"error: binaries created with TD before version 5.1 are not supported\n");
		exit(1); // versions before TD 5.1 not supported
	}

	int rc = 1;
	if (outline.get_file_hdr().flags & FLAG_IS_64BIT) {
		if (outline.get_file_hdr().version < VERSION_TD70) {
			fprintf(stderr,"error: 64bit flag set for binary created with TD before version 7.0\n");
			exit(1);
		}
		// load as 64bit binary
		COutline64 outline64(td);
		init_system_vars64();
		rc = process_outline(outline64) ? 0 : 1;
	} else {
		// process 32bit binary
		init_system_vars();
		rc = process_outline(outline) ? 0 : 1;
	}

	if (apt_buf) {
		if (rc == 0 && get_apt_output_filename()) {
			if (!write_utf16_apt(get_apt_output_filename(), apt_buf)) {
				fprintf(stderr,"cannot write to apt file %s\n",get_apt_output_filename());
				rc = 1;
			}
		}
		free(apt_buf);
	}
	return rc;
}
