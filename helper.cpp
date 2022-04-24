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
typedef unsigned uint;
#else
#error "neither Unix nor Windows environment defined"
#endif
#include "helper.hpp"
#include "item.hpp"
#include "sal_datatypes.hpp"
#include <exception>
#include <time.h>

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
	out_buffer += WideCharToMultiByte(CP_UTF8, 0, (LPCWCH)str, (int)len/2, out, (int)out_len, NULL, NULL);
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
	out_buffer += WideCharToMultiByte(CP_UTF8, 0, (LPCWCH)str, (int)len/2, out, (int)out_len, NULL, NULL);
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


/**
 * Windows gmtime cannot deal with negative values:
 * https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/gmtime-s-gmtime32-s-gmtime64-s
 *
 * SecondsSinceEpochToDateTime copied from stackoverflow to solve stupid Windows problem
 * https://stackoverflow.com/questions/11188621/how-can-i-convert-seconds-since-the-epoch-to-hours-minutes-seconds-in-java/11197532#11197532
 */

struct tm* SecondsSinceEpochToDateTime(struct tm* pTm, int64_t SecondsSinceEpoch)
{
  uint64_t sec;
  uint quadricentennials, centennials, quadrennials, annuals/*1-ennial?*/;
  uint year, leap;
  uint yday, hour, min;
  uint month, mday, wday;
  static const uint daysSinceJan1st[2][13]=
  {
    {0,31,59,90,120,151,181,212,243,273,304,334,365}, // 365 days, non-leap
    {0,31,60,91,121,152,182,213,244,274,305,335,366}  // 366 days, leap
  };
/*
  400 years:

  1st hundred, starting immediately after a leap year that's a multiple of 400:
  n n n l  \
  n n n l   } 24 times
  ...      /
  n n n l /
  n n n n

  2nd hundred:
  n n n l  \
  n n n l   } 24 times
  ...      /
  n n n l /
  n n n n

  3rd hundred:
  n n n l  \
  n n n l   } 24 times
  ...      /
  n n n l /
  n n n n

  4th hundred:
  n n n l  \
  n n n l   } 24 times
  ...      /
  n n n l /
  n n n L <- 97'th leap year every 400 years
*/

  // Re-bias from 1970 to 1601:
  // 1970 - 1601 = 369 = 3*100 + 17*4 + 1 years (incl. 89 leap days) =
  // (3*100*(365+24/100) + 17*4*(365+1/4) + 1*365)*24*3600 seconds
  sec = SecondsSinceEpoch + 11644473600LL;

  wday = (uint)((sec / 86400 + 1) % 7); // day of week

  // Remove multiples of 400 years (incl. 97 leap days)
  quadricentennials = (uint)(sec / 12622780800ULL); // 400*365.2425*24*3600
  sec %= 12622780800ULL;

  // Remove multiples of 100 years (incl. 24 leap days), can't be more than 3
  // (because multiples of 4*100=400 years (incl. leap days) have been removed)
  centennials = (uint)(sec / 3155673600ULL); // 100*(365+24/100)*24*3600
  if (centennials > 3)
  {
    centennials = 3;
  }
  sec -= centennials * 3155673600ULL;

  // Remove multiples of 4 years (incl. 1 leap day), can't be more than 24
  // (because multiples of 25*4=100 years (incl. leap days) have been removed)
  quadrennials = (uint)(sec / 126230400); // 4*(365+1/4)*24*3600
  if (quadrennials > 24)
  {
    quadrennials = 24;
  }
  sec -= quadrennials * 126230400ULL;

  // Remove multiples of years (incl. 0 leap days), can't be more than 3
  // (because multiples of 4 years (incl. leap days) have been removed)
  annuals = (uint)(sec / 31536000); // 365*24*3600
  if (annuals > 3)
  {
    annuals = 3;
  }
  sec -= annuals * 31536000ULL;

  // Calculate the year and find out if it's leap
  year = 1601 + quadricentennials * 400 + centennials * 100 + quadrennials * 4 + annuals;
  leap = !(year % 4) && (year % 100 || !(year % 400));

  // Calculate the day of the year and the time
  yday = sec / 86400;
  sec %= 86400;
  hour = sec / 3600;
  sec %= 3600;
  min = sec / 60;
  sec %= 60;

  // Calculate the month
  for (mday = month = 1; month < 13; month++)
  {
    if (yday < daysSinceJan1st[leap][month])
    {
      mday += yday - daysSinceJan1st[leap][month - 1];
      break;
    }
  }

  // Fill in C's "struct tm"
  memset(pTm, 0, sizeof(*pTm));
  pTm->tm_sec = sec;          // [0,59]
  pTm->tm_min = min;          // [0,59]
  pTm->tm_hour = hour;        // [0,23]
  pTm->tm_mday = mday;        // [1,31]  (day of month)
  pTm->tm_mon = month - 1;    // [0,11]  (month)
  pTm->tm_year = year - 1900; // 70+     (year since 1900)
  pTm->tm_wday = wday;        // [0,6]   (day since Sunday AKA day of week)
  pTm->tm_yday = yday;        // [0,365] (day since January 1st AKA day of year)
  pTm->tm_isdst = -1;         // daylight saving time flag

  return pTm;
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
