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
#ifndef DECOMPILE_HPP_
#define INC_ITEM_HPP_
#define DECOMPILE_HPP_
#endif
#endif

#ifdef TDx64
#ifndef DECOMPILE64_HPP_
#define INC_ITEM_HPP_
#define DECOMPILE64_HPP_
#endif
#endif

#ifdef INC_ITEM_HPP_

#include "outline_decs.hpp"
#include "sal_datatypes.hpp"
#include "item.hpp"

#include "def64.inc"

struct DecompileInfo {
	class COutline* outline;
	uint64_t* memory_item;
	struct CompileBlock* compile_block;
	struct tagOPERATOR* expression;
	datatype expected_return_type;
	varscope var_scope;
	uint8_t outer_precedence;
	uint64_t* result_info; // a value that may be returned by the decompile-function
	// If non-NULL, the enclosing call supplied a SAL-constant family for
	// this operand (e.g. "MB_" for SalMessageBox's 3rd arg). When a literal
	// number reaches Const() with this set, it's resolved against the family
	// before falling back to the raw integer.
	const char* constant_family;
	// When IntFunction recurses into a func-ref expression (IntFunSetupLate
	// etc.) with INTFUNCLASS expected type, this carries the call's expected
	// arg count so the func-ref handler can disambiguate overloads via
	// arity (late-bound polymorphic dispatch like `.._Clear` where multiple
	// classes define different signatures). 0 means "unknown / not in call
	// context".
	uint8_t caller_arg_count;
};

void decompile_expression(struct DecompileInfo di);

#endif
#undef INC_ITEM_HPP_
