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

#ifndef HELPER_HPP_
#define HELPER_HPP_
#include <stdlib.h>
#include <stdio.h>


// if buf != NULL, write to buf (realloc each time)
// else, write to file f (which may be stdout)
struct outstream {
	FILE* f; // only used if buf == 0
	char** buf;
	size_t pos; // only used if buf != 0
};

template<typename T> T alloc(size_t s);
void fread_or_throw(void* dst, size_t num, FILE* handle);
void fseek_or_throw(FILE* handle, size_t offset);

size_t strlen_utf16(const char16_t* str);
void print_utf16(const char16_t* str, size_t len);
void print_utf16(const char16_t* str);
void print_utf16_quoted(const char16_t* str, size_t len);
void print_utf16_quoted(const char16_t* str);

size_t count_linebreaks(const char16_t* str, size_t len); // in UTF-16 string
size_t count_linebreaks(const char16_t* str); // in UTF-16 string

void oset(struct outstream out);
void oprintf(const char* format, ...);
void oputs(const char* str);

struct tm* SecondsSinceEpochToDateTime(struct tm* pTm, int64_t SecondsSinceEpoch);

// Validate a relative path for use as an output filename inside a Sita-
// controlled directory (project dir, resource dump dir). Translates
// Windows `\` to forward `/`, rejects absolute paths, drive letters, and
// any `..` or `.` segment so an attacker-controlled .exe cannot write
// outside the chosen directory. Subdirectories are allowed and will be
// created if mkdir_parents() is called on the resulting path.
// Returns true on success and writes the cleaned path to out_rel.
#include <string>
bool sanitize_relpath(const std::string& in, std::string& out_rel);

// Recursively `mkdir` all parent components of `path` (treating `path` as
// a file path). No-op if no parent or already existing. Silently ignores
// EEXIST.
void mkdir_parents(const std::string& path);

// Convert a UTF-8 LF buffer (Sita's internal text format) to UTF-16LE
// + BOM + CRLF and write to `path` (binary mode). This is the encoding
// `cbi -c` expects for `.apt` / `.apl` source files. Returns false if
// the file couldn't be opened.
bool write_utf16_apt(const char* path, const char* utf8_buf);

#endif /* HELPER_HPP_ */
