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

#ifndef SALNUMBER_HPP_
#define SALNUMBER_HPP_
#include "outline_decs.hpp"

uint8_t is_null(const struct SalNumber* num);
void sprint_number(char* out, const struct SalNumber* num);
void print_number(const struct SalNumber* num);
void sprint_date(char* out, const struct SalNumber* num);
void print_date(const struct SalNumber* num);
void sprint_time(char* out, const struct SalNumber* num);
void print_time(const struct SalNumber* num);
uint8_t is_zero_or_null(const struct SalNumber* num);
bool boolval(const struct SalNumber* num);
void sprint_bool(char* str, const struct SalNumber* num);

#endif /* SALNUMBER_HPP_ */
