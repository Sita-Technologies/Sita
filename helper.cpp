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

#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#ifdef __unix__ 
#include <iconv.h>
#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
#include <windows.h>
#else
#error "neither Unix nor Windows environment defined"
#endif
#include "helper.hpp"
#include "item.hpp"
#include "sal_datatypes.hpp"
#include <exception>

template<typename T> inline T alloc(size_t s) {
	T m = (T)malloc(s);
	if (!m) {
		throw new std::bad_alloc();
	}
	memset(m,0,s);
	return m;
}

void fread_or_throw(void* dst, size_t num, FILE* handle) {
	if (fread(dst,num,1,handle) != 1) {
		throw new std::exception();
	}
}

void fseek_or_throw(FILE* handle, size_t offset) {
	if (fseek(handle, (long)offset, SEEK_SET)) {
		throw new std::exception();
	}
}

struct outstream OUTPUT = {
		stdout,
		0,
		0
};

void oset(struct outstream out) {
	OUTPUT.f = out.f;
	OUTPUT.buf = out.buf;
	OUTPUT.pos = out.pos;
}

void oprintf(const char* format, ...) {
	int cnt;
	void* tmp;
    va_list arglist;
    va_list arglist2;
    va_start(arglist, format);
	va_copy(arglist2,arglist);
    if (OUTPUT.buf) {
    	cnt = vsnprintf(NULL, 0, format, arglist);
    	if (cnt>0) {
    		tmp = realloc(*OUTPUT.buf, OUTPUT.pos + cnt + 1);
    		if (tmp) {
    			*OUTPUT.buf = (char*)tmp;
    			vsprintf(*OUTPUT.buf+OUTPUT.pos, format, arglist2);
    			OUTPUT.pos += cnt;
    		}
    	}
    }else{
    	vfprintf(OUTPUT.f, format, arglist);
    }
    va_end(arglist2);
    va_end(arglist);
}

void oputs(const char* str) {
    if (OUTPUT.buf) {
    	size_t cnt = strlen(str);
    	if (cnt>0) {
    		void* tmp = realloc(*OUTPUT.buf, OUTPUT.pos + cnt + 1);
    		if (tmp) {
    			*OUTPUT.buf = (char*)tmp;
    			strcpy(*OUTPUT.buf+OUTPUT.pos, str);
    			OUTPUT.pos += cnt;
    		}
    	}
    }else{
    	fputs(str, OUTPUT.f);
    }
}

size_t strlen_utf16(const char16_t* str) {
	size_t len = 0;
	while (*str != 0) {
		len+=2;
		str++;
	}
	return len;
}

void print_utf16(const char16_t* str, size_t len) {
	size_t out_len = 2*len+1;
	char* out = alloc<char*>(out_len);
	char* out_buffer = out;
#ifdef __unix__ 
	iconv_t str_convert = iconv_open("UTF-8", "UTF-16LE");
	iconv(str_convert, (char**)&str, &len, &out_buffer, &out_len);
	iconv_close(str_convert);
#else
	out_len = WideCharToMultiByte(CP_UTF8, WC_NO_BEST_FIT_CHARS, (LPCWCH)str, (int)len, out, (int)out_len, NULL, NULL);
	out_buffer += out_len;
#endif
	*out_buffer = 0;
	oputs(out);
	free(out);
}

void print_utf16(const char16_t* str) {
	print_utf16(str, strlen_utf16(str));
}

void print_utf16_quoted(const char16_t* str) {
	print_utf16_quoted(str, strlen_utf16(str));
}

void print_utf16_quoted(const char16_t* str, size_t len) {
	size_t out_len = 2*len+1;
	char* out = (char*)malloc(out_len);
	if (!out) {
		throw new std::bad_alloc();
	}
	char* out_buffer = out;
#ifdef __unix__ 
	iconv_t str_convert = iconv_open("UTF-8", "UTF-16LE");
	iconv(str_convert, (char**)&str, &len, &out_buffer, &out_len);
	iconv_close(str_convert);
#else
	out_len = WideCharToMultiByte(CP_UTF8, WC_NO_BEST_FIT_CHARS, (LPCWCH)str, (int)len, out, (int)out_len, NULL, NULL);
	out_buffer += out_len;
#endif
	*out_buffer = 0;
	oputs("\"");
	for (size_t i=0; i<out_len; i++) {
		if (!out[i]) {
			break;
		}
		if (out[i] == '\"') {
			oputs("\\\"");
		}else if (out[i] == '\\') {
			oputs("\\\\");
		}else{
			oprintf("%c",out[i]);
		}
	}
	oputs("\"");
	free(out);
}

size_t count_linebreaks(const char16_t* str, size_t len) {
	size_t count = 0;
	if (!str) {
		return 0;
	}
	while (*str && len>1) {
		if (str[0] == '\r' && str[1] == '\n') {
			count++;
			str++;
			len--;
		}
		str++;
		len--;
	}
	return count;
}

size_t count_linebreaks(const char16_t* str) {
	return count_linebreaks(str,strlen_utf16(str));
}

// instantiate alloc functions
template char* alloc(size_t);
template char16_t* alloc(size_t);
template uint32_t* alloc(size_t);
template enum datatype* alloc(size_t);
template struct Outline* alloc(size_t);
template struct tagITEM* alloc(size_t);
template struct RuntimeMemory* alloc(size_t);
template struct ItemBody* alloc(size_t);
template struct tagOSEG* alloc(size_t);
template struct tagOSEG** alloc(size_t);
template struct HandTable* alloc(size_t);
template struct HandTable** alloc(size_t);
template struct tagPERMSYM** alloc(size_t);
template struct tagPERMSYM*** alloc(size_t);
