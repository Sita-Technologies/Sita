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

#undef INC_ITEM_HPP_
#ifndef TDx64
#ifndef PROCESS_OUTLINE_HPP_
#define INC_ITEM_HPP_
#define PROCESS_OUTLINE_HPP_
#endif
#endif

#ifdef TDx64
#ifndef PROCESS_OUTLINE64_HPP_
#define INC_ITEM_HPP_
#define PROCESS_OUTLINE64_HPP_
#endif
#endif

#ifdef INC_ITEM_HPP_

#include "COutline.hpp"
#include "commandline_args.hpp"

void print_indent(uint32_t indent);
void iterate_items(COutline& outline, uint64_t item, uint32_t indention, uint64_t* parent_memory_item, bool first_pass = false);
bool process_outline(COutline& outline);

#endif
#undef INC_ITEM_HPP_
