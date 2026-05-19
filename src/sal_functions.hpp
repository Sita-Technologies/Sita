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

#ifndef SAL_FUNCTIONS_HPP_
#define SAL_FUNCTIONS_HPP_

#include "sal_datatypes.hpp"
#include <stdint.h>

struct func_header {
	const char* name;
	enum datatype return_type;
	uint8_t num_parameters;
	enum datatype* parameters;
};

extern enum datatype any[];

#define NUM_INT_LOCALS 1483
extern struct func_header INT_LOCALS[NUM_INT_LOCALS];

// Resolve a SAL constant value to its name within the given family.
// Family keys are prefixes like "MB_", "TBL_", "COLOR_". Returns NULL if no
// match.
const char* resolve_sal_constant(const char* family_key, int64_t value);

// For (SAL function name, 0-based param index), return the constant-family
// key that param accepts (e.g. "MB_" for SalMessageBox's nFlags), or NULL.
const char* lookup_sal_param_family(const char* function, uint8_t param_index);

// Return the constant-family key for `function`'s return value, or NULL.
// Used to resolve `If SomeFunc() = <literal>` comparisons.
const char* lookup_sal_return_family(const char* function);

#endif /* SAL_FUNCTIONS_HPP_ */
