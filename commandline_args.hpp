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

#ifndef COMMANDLINE_ARGS_HPP_
#define COMMANDLINE_ARGS_HPP_
#include <stdio.h>

void print_usage(const char* command);
bool parse_command_line(int argc, char** argv);

bool is_verbose();
bool is_remove_importflag();
const char* get_input_filename();
const char* get_item_dump_dir();
const char* get_resource_dump_dir();
const char* get_app_output_filename();

#endif
