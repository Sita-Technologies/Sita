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

#include "system_variables.hpp"
#include <string.h>

extern const uint16_t max_system_var = 0x1f3;
const char* system_vars[max_system_var];

void init_system_vars() {
	memset(system_vars,0x00,max_system_var*sizeof(const char*));
	system_vars[0x04] = "hWndForm";
	system_vars[0x08] = "hWndMDI";
	system_vars[0x0c] = "hWndNULL";
	system_vars[0x10] = "hWndItem";
	system_vars[0x14] = "hWndFrame";
	system_vars[0x18] = "wParam";
	system_vars[0x31] = "lParam";
	system_vars[0x4a] = "nArgCount";
	system_vars[0x63] = "strArgArray"; // ARRAY
	system_vars[0x67] = "SqlDatabase";
	system_vars[0x6b] = "SqlINI";
	system_vars[0x6f] = "SqlUDL";
	system_vars[0x73] = "SqlUser";
	system_vars[0x77] = "SqlPassword";
	system_vars[0x7b] = "SqlNoRecovery";
	system_vars[0x94] = "SqlInMessage";
	system_vars[0xad] = "SqlOutMessage";
	system_vars[0xc6] = "SqlResultSet";
	system_vars[0xdf] = "SqlIsolationLevel";
	system_vars[0xe3] = "SqlServername";
	system_vars[0xe7] = "SqlConnectOptions";
	system_vars[0xeb] = "bStaticsAsWindows";
	system_vars[0x104] = "bMenuBarAsRibbonBar";
	system_vars[0x11d] = "bMaxDataLengthInBytes";
	system_vars[0x136] = "bDeferCreatingTabChildren";
	system_vars[0x14f] = "n_SW_Null";
	system_vars[0x168] = "dt_SW_Null";
	system_vars[0x181] = "STRING_Null";
	system_vars[0x185] = "BINARY_Null";
	// DATETIME_Null // 0x189???
	system_vars[0x1a2] = "____sql_temp_STRING";
	system_vars[0x1a6] = "wpfEventName";
	system_vars[0x1aa] = "LastException";
	// TEMPLATE_Null // seems to be a Handle???
}

void init_system_vars64() {
	memset(system_vars,0x00,max_system_var*sizeof(const char*));
	system_vars[0x04] = "hWndForm";
	system_vars[0x0c] = "hWndMDI";
	system_vars[0x14] = "hWndNULL";
	system_vars[0x1c] = "hWndItem";
	system_vars[0x24] = "hWndFrame";
	system_vars[0x2c] = "wParam";
	system_vars[0x45] = "lParam";
	system_vars[0x5e] = "nArgCount";
	system_vars[0x77] = "strArgArray"; // ARRAY
	system_vars[0x7f] = "SqlDatabase";
	system_vars[0x87] = "SqlINI";
	system_vars[0x8f] = "SqlUDL";
	system_vars[0x97] = "SqlUser";
	system_vars[0x9f] = "SqlPassword";
	system_vars[0xa7] = "SqlNoRecovery";
	system_vars[0xc0] = "SqlInMessage";
	system_vars[0xd9] = "SqlOutMessage";
	system_vars[0xf2] = "SqlResultSet";
	system_vars[0x10b] = "SqlIsolationLevel";
	system_vars[0x113] = "SqlServername";
	system_vars[0x11b] = "SqlConnectOptions";
	system_vars[0x123] = "bStaticsAsWindows";
	system_vars[0x13c] = "bMenuBarAsRibbonBar";
	system_vars[0x155] = "bMaxDataLengthInBytes";
	system_vars[0x16e] = "bDeferCreatingTabChildren";
	system_vars[0x187] = "n_SW_Null";
	system_vars[0x1a0] = "dt_SW_Null";
	system_vars[0x1b9] = "STRING_Null";
	system_vars[0x1c1] = "BINARY_Null";
	// DATETIME_Null // 0x1c9???
	system_vars[0x1e2] = "____sql_temp_STRING";
	system_vars[0x1ea] = "wpfEventName";
	system_vars[0x1f2] = "LastException";
	// TEMPLATE_Null // seems to be a Handle???
}
