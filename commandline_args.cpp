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

void print_usage(const char* command) {
	printf("usage: %s [option [option [...]]] <compiled.exe>\n",command);
	puts("decompiler for programs created with opentext Gupta Team Developer 6.0-7.4");
	puts("");
	puts("options:");
	puts("  -v              verbose/debug output");
	puts("  -d <dir>        dump segment data to dir");
	puts("  -r <dir>        dump resources to dir");
	puts("  -a <filename>   write decompiled program to app file");
	//puts("  -t <filename>   write decompiled program to apt file");
	//puts("  -q              quiet (don't print decompiled program to console)");
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
				if (i+1 < argc && !app_output) {
					app_output = argv[++i];
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

const char* get_input_filename() {
	return input_fn;
}

const char* get_item_dump_dir() {
	return item_dump_dir;
}

const char* get_resource_dump_dir() {
	return res_dump_dir;
}

const char* get_app_output_filename() {
	return app_output;
}

bool is_remove_importflag() {
	return true; // TODO: default to false? // add command line flag
}
