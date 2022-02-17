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

#include "SalNumber.hpp"
#include "helper.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

uint8_t is_null(const struct SalNumber* num) {
	if (num == 0) {
		return 1;
	}
	if (num->size == 0) {
		return 1;
	}
	return 0;
}

void sprint_number(char* out, const struct SalNumber* number) {
	if (!out) {
		return;
	}
	*out = 0;

	if (is_null(number)) {
		sprintf(out,"NUMBER_Null");
		return;
	}

	// clone number since it will be modified during processing negative numbers
	struct SalNumber n;
	struct SalNumber* num = &n;
	memset(num,0,sizeof(struct SalNumber));
	if (number->size <= 0x18) {
		num->size = number->size;;
	}else{
		num->size = 0x18;
	}
	memcpy(num->payload,number->payload,num->size);

	if (num->size == 1) {
		sprintf(out,"0");
		return;
	}

	//uint8_t negative = 0;
	if ((num->payload[0]&0x80) != 0x80) {
		sprintf(out,"-"); // negative numbers
		//negative = 1;
		num->payload[0] = ~num->payload[0];
		for (int i=1;i<num->size;i++) {
			num->payload[i] = 0x64 - num->payload[i];
			if (num->payload[i] == 0xff) {
				num->payload[i] = 0;
			}
		}
	}
	uint8_t pos = 1;
	uint8_t printed_any = 0;
	for (uint8_t i=(num->payload[0]&0x7f); i>0x40; i--) {
		if (pos < 0x18 && pos < num->size) {
			if (printed_any || num->payload[pos]/10) {
				sprintf(out+strlen(out),"%c",'0'+num->payload[pos]/10);
				printed_any = 1;
			}
			if (printed_any || num->payload[pos]%10) {
				sprintf(out+strlen(out),"%c",'0'+num->payload[pos]%10);
				printed_any = 1;
			}
		}else if (printed_any) {
			sprintf(out+strlen(out),"00");
		}
		pos++;
	}
	if (pos < 0x18 && pos < num->size) {
		if (!printed_any) {
			sprintf(out+strlen(out),"0");
		}
		sprintf(out+strlen(out),".");
		for (uint8_t i=0x40; i>(num->payload[0]&0x7f); i--) {
			sprintf(out+strlen(out),"00");
		}
		for (;pos < 0x18 && pos < num->size;pos++) {
			sprintf(out+strlen(out),"%c",'0'+num->payload[pos]/10);
			if ((pos != 0x17 && pos != num->size-1) || num->payload[pos]%10) {
				sprintf(out+strlen(out),"%c",'0'+num->payload[pos]%10);
			}
		}
	}
}

void print_number(const struct SalNumber* num) {
	char buf[300];
	sprint_number(buf,num);
	oputs(buf);
}

void sprint_date(char* str, const struct SalNumber* num) {
	// num contains number of days since 1899-12-30 0:00:00 (GMT)

	if (!str) {
		return;
	}

	char buf[300];
	sprint_number(buf,num);
	setlocale(LC_ALL, "en_US");
	double diff = atof(buf);
	diff*=60.0*60.0*24.0; // days to seconds
	double stamp = diff-2209161600.0; // -2209161600: Unix timestamp of Dec 30th, 1899 (GMT)
	int64_t seconds = (int64_t)stamp;
	if (seconds > stamp) seconds--; // force [seconds <= stamp] for double->int conversion of negative numbers
	struct tm* nowtm;
	time_t nowtime = seconds;
	nowtm = gmtime(&nowtime);
	char tmbuf[64];
	strftime(tmbuf, sizeof tmbuf, "%Y-%m-%d-%H.%M.%S", nowtm);
	// compute micro seconds
	uint32_t nano_x10 = (uint32_t)((stamp-(double)seconds)*10000000.0);
	if (nano_x10%10>4) {
		nano_x10+=10;
	}
	sprintf(str,"%s.%06u",tmbuf,nano_x10/10);
}

void print_date(const struct SalNumber* num) {
	char str[256];
	sprint_date(str,num);
	oputs(str);
}

uint8_t is_zero_or_null(const struct SalNumber* num) {
	if (num == 0) {
		return 1;
	}
	if (num->size == 0) {
		return 1;
	}
	if (num->size == 1) {
		return 1;
	}
	for (uint8_t i=1; i<0x18 && i<num->size; i--) {
		if (num->payload[i] != 0x00) {
			return 0;
		}
	}
	return 1;
}

bool boolval(const struct SalNumber* number) {
	if (is_null(number)) {
		return false;
	}
	if (number->size == 1) {
		return false;
	}

	// clone number since it will be modified during processing negative numbers
	struct SalNumber n;
	struct SalNumber* num = &n;
	memset(num,0,sizeof(struct SalNumber));
	if (number->size <= 0x18) {
		num->size = number->size;;
	}else{
		num->size = 0x18;
	}
	memcpy(num->payload,number->payload,num->size);

	if ((num->payload[0]&0x80) != 0x80) {
		num->payload[0] = ~num->payload[0];
		for (int i=1;i<num->size;i++) {
			num->payload[i] = 0x64 - num->payload[i];
			if (num->payload[i] == 0xff) {
				num->payload[i] = 0;
			}
		}
	}
	uint8_t pos = 1;
	for (uint8_t i=(num->payload[0]&0x7f); i>0x40; i--) {
		if (pos < 0x18 && pos < num->size) {
			if (num->payload[pos]/10 || num->payload[pos]%10) {
				return true;
			}
		}
		pos++;
	}
	if (pos < 0x18 && pos < num->size) {
		for (;pos < 0x18 && pos < num->size;pos++) {
			if (num->payload[pos]/10 || num->payload[pos]%10) {
				return true;
			}
		}
	}
	return false;
}

void sprint_bool(char* str, const struct SalNumber* num) {
	if (!str) {
		return;
	}
	if (boolval(num)) {
		strcpy(str,"TRUE");
	}else{
		strcpy(str,"FALSE");
	}
	return;
}
