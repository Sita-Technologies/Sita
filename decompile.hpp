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

#ifndef DECOMPILE_HPP_
#define DECOMPILE_HPP_
#include "outline_decs.hpp"
#include "sal_datatypes.hpp"
#include "item.hpp"

struct DecompileInfo {
	class COutline* outline;
	uint32_t* memory_item;
	struct CompileBlock* compile_block;
	struct tagOPERATOR* expression;
	datatype expected_return_type;
	varscope var_scope;
	uint8_t outer_precedence;
	uint32_t* result_info; // a value that may be returned by the decompile-function
};

void decompile_expression(struct DecompileInfo di);

#endif /* DECOMPILE_HPP_ */
