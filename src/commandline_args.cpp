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

#include <stdio.h>
#include "commandline_args.hpp"

bool verbose = false;
char* input_fn = NULL;
char* item_dump_dir = NULL;
char* res_dump_dir = NULL;
char* app_output = NULL;
char* apt_output = NULL;
char* project_dir = NULL;
bool project_text_mode = false;

void print_usage(const char* command) {
	printf("usage: %s [option [option [...]]] <input.exe|.app|.apl>\n",command);
	puts("decompiler for programs created with opentext Gupta Team Developer 5.1-7.4");
	puts("input may be a compiled .exe or a binary .app / .apl source file (auto-detected via MGDR magic).");
	puts("");
	puts("output (mutually exclusive):");
	puts("  -a <file>       write decompiled program to single .app file (binary)");
	puts("  -t <file>       write decompiled program to single .apt file (text, UTF-16LE+BOM+CRLF)");
	puts("  -p <dir>        write decompiled project to <dir>: main .app + .apl per File Include (binary)");
	puts("  -P <dir>        write decompiled project to <dir>: main .apt + .apl per File Include (text)");
	puts("                  no output flag => write decompiled .apt-shaped text (UTF-8/LF) to stdout");
	puts("");
	puts("auxiliary outputs:");
	puts("  -r <dir>        dump embedded resources (icons, bitmaps, ...) into <dir>.");
	puts("                  may be combined with any output flag, or used alone to extract resources");
	puts("                  without decompilation. with -p / -P and no -r, resources are dumped into");
	puts("                  the project directory alongside the main file and split .apl libraries.");
	puts("                  filenames embedded in the .exe are sanitized (no '..', no absolute paths,");
	puts("                  no drive letters); rejected names fall back to a safe resource_SSSSHHHH.bin.");
	puts("");
	puts("debug:");
	puts("  -v              verbose/debug output (prepends item-id/type/flags; dumps full ItemBody data;");
	puts("                  output is no longer a clean .apt stream)");
	puts("  -d <dir>        dump raw tag-OSEG segment data as item_<id>.bin into <dir>");
	puts("");
	puts("  --              end of options; the next arg is the input filename even if it starts with -");
}

static bool set_output_mode(char** slot, char* value) {
	int set_count = 0;
	if (app_output) set_count++;
	if (apt_output) set_count++;
	if (project_dir) set_count++;
	if (set_count > 0) {
		fprintf(stderr,"error: only one of -a, -t, -p, -P may be specified\n");
		return false;
	}
	*slot = value;
	return true;
}

bool parse_command_line(int argc, char** argv) {
	for (int i=1; i<argc; i++) {
		if (argv[i][0] == '-') {
			switch (argv[i][1]) {
			case '-':
				if (argv[i][2] == 0) {
					if (argc == i+2 && !input_fn) {
						input_fn = argv[++i];
						return true;
					}else{
						return false;
					}
				}
				return false;
			case 'v':
				verbose = true;
				break;
			case 'd':
				if (i+1 < argc && !item_dump_dir) {
					item_dump_dir = argv[++i];
				}else{
					return false;
				}
				break;
			case 'r':
				if (i+1 < argc && !res_dump_dir) {
					res_dump_dir = argv[++i];
				}else{
					return false;
				}
				break;
			case 'a':
				if (i+1 < argc) {
					if (!set_output_mode(&app_output, argv[++i])) return false;
				}else{
					return false;
				}
				break;
			case 't':
				if (i+1 < argc) {
					if (!set_output_mode(&apt_output, argv[++i])) return false;
				}else{
					return false;
				}
				break;
			case 'p':
				if (i+1 < argc) {
					if (!set_output_mode(&project_dir, argv[++i])) return false;
					project_text_mode = false;
				}else{
					return false;
				}
				break;
			case 'P':
				if (i+1 < argc) {
					if (!set_output_mode(&project_dir, argv[++i])) return false;
					project_text_mode = true;
				}else{
					return false;
				}
				break;
			default:
				return false;
			}
		}else if (!input_fn) {
			input_fn = argv[i];
		}else{
			return false;
		}
	}
	return input_fn != 0;
}

bool is_verbose() {
	return verbose;
}

void set_verbose(bool verbose) {
	::verbose = verbose;
}

const char* get_input_filename() {
	return input_fn;
}

const char* get_item_dump_dir() {
	return item_dump_dir;
}

const char* get_resource_dump_dir() {
	return res_dump_dir;
}

const char* get_effective_resource_dir() {
	if (res_dump_dir) return res_dump_dir;
	if (project_dir) return project_dir;
	return NULL;
}

const char* get_app_output_filename() {
	return app_output;
}

const char* get_apt_output_filename() {
	return apt_output;
}

const char* get_project_dir() {
	return project_dir;
}

bool is_project_text_mode() {
	return project_text_mode;
}

bool is_binary_app_output() {
	return get_app_output_filename() != NULL
		|| (get_project_dir() != NULL && !is_project_text_mode());
}

bool is_remove_importflag() {
	// The import flag (tagITEM flags bit 0x400) marks items that were
	// pulled in via a File Include directive. cbi -b uses it to recognize
	// inlined library content as already-merged so adjacent .apl resolution
	// doesn't trigger "Duplicate symbol". Leaving the flag intact preserves
	// the per-item marker that cbi -c originally set.
	return false;
}
