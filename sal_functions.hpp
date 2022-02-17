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

struct func_header {
	const char* name;
	enum datatype return_type;
	uint8_t num_parameters;
	enum datatype* parameters;
};

enum datatype any[] = { ANY };

// TODO: update datatypes
struct func_header INT_LOCALS[1423] = {
		// 0x0000
		{"undefined",ANY,(uint8_t)-1,any},
		// 0x0001
		{"SqlImmediate",ANY,(uint8_t)-1,any},
		// 0x0002
		{"SqlPrepare",ANY,(uint8_t)-1,any},
		// 0x0003
		{"SqlExecute",ANY,(uint8_t)-1,any},
		// 0x0004
		{"SqlFetchNext",ANY,(uint8_t)-1,any},
		// 0x0005
		{"SqlExists",ANY,(uint8_t)-1,any},
		// 0x0006
		{"SqlFetchPrevious",ANY,(uint8_t)-1,any},
		// 0x0007
		{"SqlFetchRow",ANY,(uint8_t)-1,any},
		// 0x0008
		{"SqlSetCursorName",ANY,(uint8_t)-1,any},
		// 0x0009
		{"SqlDisconnect",ANY,(uint8_t)-1,any},
		// 0x000A
		{"SqlEnableFetchBackwar",ANY,(uint8_t)-1,any},
		// 0x000B
		{"SqlError",ANY,(uint8_t)-1,any},
		// 0x000C
		{"SqlGetErrorText",ANY,(uint8_t)-1,any},
		// 0x000D
		{"SqlConnect",ANY,(uint8_t)-1,any},
		// 0x000E
		{"SqlGetErrorPosition",ANY,(uint8_t)-1,any},
		// 0x000F
		{"SqlGetRollbackFlag",ANY,(uint8_t)-1,any},
		// 0x0010
		{"SqlSetIsolationLevel",ANY,(uint8_t)-1,any},
		// 0x0011
		{"SalIsValidNumber",ANY,(uint8_t)-1,any},
		// 0x0012
		{"SalIsValidDateTime",ANY,(uint8_t)-1,any},
		// 0x0013
		{"SalIsNull",ANY,(uint8_t)-1,any},
		// 0x0014
		{"SalIsValidDecimal",ANY,(uint8_t)-1,any},
		// 0x0015
		{"SalIsValidInteger",ANY,(uint8_t)-1,any},
		// 0x0016
		{"SalShowWindow",ANY,(uint8_t)-1,any},
		// 0x0017
		{"SalHideWindow",ANY,(uint8_t)-1,any},
		// 0x0018
		{"SalMessageBox",ANY,(uint8_t)-1,any},
		// 0x0019
		{"SalSendMsg",ANY,(uint8_t)-1,any},
		// 0x001A
		{"SalPostMsg",ANY,(uint8_t)-1,any},
		// 0x001B
		{"SalIsWindowVisible",ANY,(uint8_t)-1,any},
		// 0x001C
		{"SalCreateWindow",ANY,(uint8_t)-1,any},
		// 0x001D
		{"SalDestroyWindowExter",ANY,(uint8_t)-1,any},
		// 0x001E
		{"SalClearField",ANY,(uint8_t)-1,any},
		// 0x001F
		{"SalQuit",ANY,(uint8_t)-1,any},
		// 0x0020
		{"SalAbort",ANY,(uint8_t)-1,any},
		// 0x0021
		{"SalEditCanCut",ANY,(uint8_t)-1,any},
		// 0x0022
		{"SalEditCanPaste",ANY,(uint8_t)-1,any},
		// 0x0023
		{"SalEditCanUndo",ANY,(uint8_t)-1,any},
		// 0x0024
		{"SalTblReset",ANY,(uint8_t)-1,any},
		// 0x0025
		{"SalWaitCursor",ANY,(uint8_t)-1,any},
		// 0x0026
		{"HSLock",ANY,(uint8_t)-1,any},
		// 0x0027
		{"SalGetWindowText",ANY,(uint8_t)-1,any},
		// 0x0028
		{"SalSetWindowText",ANY,(uint8_t)-1,any},
		// 0x0029
		{"SalSetFieldEdit",ANY,(uint8_t)-1,any},
		// 0x002A
		{"SalQueryFieldEdit",ANY,(uint8_t)-1,any},
		// 0x002B
		{"SqlExtractArgs",ANY,(uint8_t)-1,any},
		// 0x002C
		{"SalLog",ANY,(uint8_t)-1,any},
		// 0x002D
		{"HSUnlock",ANY,(uint8_t)-1,any},
		// 0x002E
		{"SalModalDialog",ANY,(uint8_t)-1,any},
		// 0x002F
		{"SalEndDialog",ANY,(uint8_t)-1,any},
		// 0x0030
		{"SalEditClear",ANY,(uint8_t)-1,any},
		// 0x0031
		{"SalEditCopy",ANY,(uint8_t)-1,any},
		// 0x0032
		{"SalEditCut",ANY,(uint8_t)-1,any},
		// 0x0033
		{"SalEditPaste",ANY,(uint8_t)-1,any},
		// 0x0034
		{"SalEditUndo",ANY,(uint8_t)-1,any},
		// 0x0035
		{"SalParentWindow",ANY,(uint8_t)-1,any},
		// 0x0036
		{"SalInvalidateWindow",ANY,(uint8_t)-1,any},
		// 0x0037
		{"SalDisableWindow",ANY,(uint8_t)-1,any},
		// 0x0038
		{"SalEnableWindow",ANY,(uint8_t)-1,any},
		// 0x0039
		{"SalListQueryFile",ANY,(uint8_t)-1,any},
		// 0x003A
		{"SalListAdd",ANY,(uint8_t)-1,any},
		// 0x003B
		{"SalListClear",ANY,(uint8_t)-1,any},
		// 0x003C
		{"SalListDelete",ANY,(uint8_t)-1,any},
		// 0x003D
		{"SalListInsert",ANY,(uint8_t)-1,any},
		// 0x003E
		{"SalListQueryCount",ANY,(uint8_t)-1,any},
		// 0x003F
		{"SalListQuerySelection",ANY,(uint8_t)-1,any},
		// 0x0040
		{"SalListQueryState",ANY,(uint8_t)-1,any},
		// 0x0041
		{"SalListQueryText",ANY,(uint8_t)-1,any},
		// 0x0042
		{"SalListQueryTextLengt",ANY,(uint8_t)-1,any},
		// 0x0043
		{"SalListSelectString",ANY,(uint8_t)-1,any},
		// 0x0044
		{"SalListSetSelect",ANY,(uint8_t)-1,any},
		// 0x0045
		{"SalListSetMultiSelect",ANY,(uint8_t)-1,any},
		// 0x0046
		{"SalListFiles",ANY,(uint8_t)-1,any},
		// 0x0047
		{"SalTblClearSelection",ANY,(uint8_t)-1,any},
		// 0x0048
		{"SalTblQueryFocus",ANY,(uint8_t)-1,any},
		// 0x0049
		{"SalTblKillFocus",ANY,(uint8_t)-1,any},
		// 0x004A
		{"SalTblQueryContext",ANY,(uint8_t)-1,any},
		// 0x004B
		{"SalTblQueryScroll",ANY,(uint8_t)-1,any},
		// 0x004C
		{"SalTblQueryVisibleRan",ANY,(uint8_t)-1,any},
		// 0x004D
		{"SalTblScroll",ANY,(uint8_t)-1,any},
		// 0x004E
		{"SalTblSetContext",ANY,(uint8_t)-1,any},
		// 0x004F
		{"SalTblSetFocusRow",ANY,(uint8_t)-1,any},
		// 0x0050
		{"SalTblSetRange",ANY,(uint8_t)-1,any},
		// 0x0051
		{"SalTblDebug",ANY,(uint8_t)-1,any},
		// 0x0052
		{"SalTblQueryRowFlags",ANY,(uint8_t)-1,any},
		// 0x0053
		{"SalTblSetRowFlags",ANY,(uint8_t)-1,any},
		// 0x0054
		{"SalTblInsertRow",ANY,(uint8_t)-1,any},
		// 0x0055
		{"SalTblKillEdit",ANY,(uint8_t)-1,any},
		// 0x0056
		{"SalTblSetFocusCell",ANY,(uint8_t)-1,any},
		// 0x0057
		{"SalTblFindNextRow",ANY,(uint8_t)-1,any},
		// 0x0058
		{"SalTblFindPrevRow",ANY,(uint8_t)-1,any},
		// 0x0059
		{"SalTblFetchRow",ANY,(uint8_t)-1,any},
		// 0x005A
		{"SalTblDeleteRow",ANY,(uint8_t)-1,any},
		// 0x005B
		{"SalTblPaintRows",ANY,(uint8_t)-1,any},
		// 0x005C
		{"SalFileTell",ANY,(uint8_t)-1,any},
		// 0x005D
		{"SqlClearImmediate",ANY,(uint8_t)-1,any},
		// 0x005E
		{"SalNumberMod",ANY,(uint8_t)-1,any},
		// 0x005F
		{"SalStrGetBufferLength",ANY,(uint8_t)-1,any},
		// 0x0060
		{"SalStrSetBufferLength",ANY,(uint8_t)-1,any},
		// 0x0061
		{"SalScrollGetPos",ANY,(uint8_t)-1,any},
		// 0x0062
		{"SalScrollSetPos",ANY,(uint8_t)-1,any},
		// 0x0063
		{"SalScrollGetRange",ANY,(uint8_t)-1,any},
		// 0x0064
		{"SalExitWindows",ANY,(uint8_t)-1,any},
		// 0x0065
		{"SalLogLine",ANY,(uint8_t)-1,any},
		// 0x0066
		{"SqlClose",ANY,(uint8_t)-1,any},
		// 0x0067
		{"SqlOpen",ANY,(uint8_t)-1,any},
		// 0x0068
		{"SalSetArrayBounds",ANY,(uint8_t)-1,any},
		// 0x0069
		{"SalQueryArrayBounds",ANY,(uint8_t)-1,any},
		// 0x006A
		{"SalLogNumber",ANY,(uint8_t)-1,any},
		// 0x006B
		{"SalFileClose",ANY,(uint8_t)-1,any},
		// 0x006C
		{"SalFileOpen",ANY,(uint8_t)-1,any},
		// 0x006D
		{"SalFileGetChar",ANY,(uint8_t)-1,any},
		// 0x006E
		{"SalFileGetStr",ANY,(uint8_t)-1,any},
		// 0x006F
		{"SalFilePutChar",ANY,(uint8_t)-1,any},
		// 0x0070
		{"SalFilePutStr",ANY,(uint8_t)-1,any},
		// 0x0071
		{"SalFileRead",ANY,(uint8_t)-1,any},
		// 0x0072
		{"SalFileSeek",ANY,(uint8_t)-1,any},
		// 0x0073
		{"SalFileWrite",ANY,(uint8_t)-1,any},
		// 0x0074
		{"SalDateCurrent",ANY,(uint8_t)-1,any},
		// 0x0075
		{"SqlXDirectory",ANY,(uint8_t)-1,any},
		// 0x0076
		{"SalDateConstruct",ANY,(uint8_t)-1,any},
		// 0x0077
		{"SalDateDay",ANY,(uint8_t)-1,any},
		// 0x0078
		{"SalDateHour",ANY,(uint8_t)-1,any},
		// 0x0079
		{"SalDateMinute",ANY,(uint8_t)-1,any},
		// 0x007A
		{"SalDateMonth",ANY,(uint8_t)-1,any},
		// 0x007B
		{"SalDateMonthBegin",ANY,(uint8_t)-1,any},
		// 0x007C
		{"SalDateQuarter",ANY,(uint8_t)-1,any},
		// 0x007D
		{"SalDateQuarterBegin",ANY,(uint8_t)-1,any},
		// 0x007E
		{"SalDateSecond",ANY,(uint8_t)-1,any},
		// 0x007F
		{"SalDateToStr",ANY,(uint8_t)-1,any},
		// 0x0080
		{"SalDateWeekBegin",ANY,(uint8_t)-1,any},
		// 0x0081
		{"SalDateWeekday",ANY,(uint8_t)-1,any},
		// 0x0082
		{"SalDateYear",ANY,(uint8_t)-1,any},
		// 0x0083
		{"SalDateYearBegin",ANY,(uint8_t)-1,any},
		// 0x0084
		{"SalArrayAvg",ANY,(uint8_t)-1,any},
		// 0x0085
		{"SalArrayMax",ANY,(uint8_t)-1,any},
		// 0x0086
		{"SalArrayMin",ANY,(uint8_t)-1,any},
		// 0x0087
		{"SalArraySum",ANY,(uint8_t)-1,any},
		// 0x0088
		{"SalStrLeft",ANY,(uint8_t)-1,any},
		// 0x0089
		{"SalStrLength",ANY,(uint8_t)-1,any},
		// 0x008A
		{"SalStrLower",ANY,(uint8_t)-1,any},
		// 0x008B
		{"SalStrMid",ANY,(uint8_t)-1,any},
		// 0x008C
		{"SalStrProper",ANY,(uint8_t)-1,any},
		// 0x008D
		{"SalStrRepeat",ANY,(uint8_t)-1,any},
		// 0x008E
		{"SalStrReplace",ANY,(uint8_t)-1,any},
		// 0x008F
		{"SalStrRight",ANY,(uint8_t)-1,any},
		// 0x0090
		{"SalStrScan",ANY,(uint8_t)-1,any},
		// 0x0091
		{"SalStrToDate",ANY,(uint8_t)-1,any},
		// 0x0092
		{"SalStrToNumber",ANY,(uint8_t)-1,any},
		// 0x0093
		{"SalStrTrim",ANY,(uint8_t)-1,any},
		// 0x0094
		{"SalStrUpper",ANY,(uint8_t)-1,any},
		// 0x0095
		{"SalNumberRound",ANY,(uint8_t)-1,any},
		// 0x0096
		{"SalNumberToStr",ANY,(uint8_t)-1,any},
		// 0x0097
		{"SalNumberTruncate",ANY,(uint8_t)-1,any},
		// 0x0098
		{"SalDDEAddAtom",ANY,(uint8_t)-1,any},
		// 0x0099
		{"SalDDEDeleteAtom",ANY,(uint8_t)-1,any},
		// 0x009A
		{"SalDDEFindAtom",ANY,(uint8_t)-1,any},
		// 0x009B
		{"SalDDEGetAtomName",ANY,(uint8_t)-1,any},
		// 0x009C
		{"SalDDEAlloc",ANY,(uint8_t)-1,any},
		// 0x009D
		{"SalDDEFree",ANY,(uint8_t)-1,any},
		// 0x009E
		{"SalDDESend",ANY,(uint8_t)-1,any},
		// 0x009F
		{"SalDDEPost",ANY,(uint8_t)-1,any},
		// 0x00A0
		{"SalDDEExtract",ANY,(uint8_t)-1,any},
		// 0x00A1
		{"SalDDESetOptions",ANY,(uint8_t)-1,any},
		// 0x00A2
		{"SalDDESetDataText",ANY,(uint8_t)-1,any},
		// 0x00A3
		{"SalDDESetCmd",ANY,(uint8_t)-1,any},
		// 0x00A4
		{"SalDDEExtractOptions",ANY,(uint8_t)-1,any},
		// 0x00A5
		{"SalDDEExtractDataText",ANY,(uint8_t)-1,any},
		// 0x00A6
		{"SalDDEExtractCmd",ANY,(uint8_t)-1,any},
		// 0x00A7
		{"SalDDESendAll",ANY,(uint8_t)-1,any},
		// 0x00A8
		{"SalBringWindowToTop",ANY,(uint8_t)-1,any},
		// 0x00A9
		{"SalCompileAndEvaluate",ANY,(uint8_t)-1,any},
		// 0x00AA
		{"SalMessageBeep",ANY,(uint8_t)-1,any},
		// 0x00AB
		{"SalContextBreak",ANY,(uint8_t)-1,any},
		// 0x00AC
		{"SalContextCurrent",ANY,(uint8_t)-1,any},
		// 0x00AD
		{"SalStrLop",ANY,(uint8_t)-1,any},
		// 0x00AE
		{"SalScrollSetRange",ANY,(uint8_t)-1,any},
		// 0x00AF
		{"SalSetFocus",ANY,(uint8_t)-1,any},
		// 0x00B0
		{"SalGetFocus",ANY,(uint8_t)-1,any},
		// 0x00B1
		{"SalPicGetDescription",ANY,(uint8_t)-1,any},
		// 0x00B2
		{"SalDlgChooseColor",ANY,(uint8_t)-1,any},
		// 0x00B3
		{"SalLoadApp",ANY,(uint8_t)-1,any},
		// 0x00B4
		{"SalFmtGetFormat",ANY,(uint8_t)-1,any},
		// 0x00B5
		{"SalFmtGetParmInt",ANY,(uint8_t)-1,any},
		// 0x00B6
		{"SalFmtGetParmStr",ANY,(uint8_t)-1,any},
		// 0x00B7
		{"SalFmtGetProfile",ANY,(uint8_t)-1,any},
		// 0x00B8
		{"SalFmtIsValidField",ANY,(uint8_t)-1,any},
		// 0x00B9
		{"SalFmtSetFormat",ANY,(uint8_t)-1,any},
		// 0x00BA
		{"SalFmtSetParmInt",ANY,(uint8_t)-1,any},
		// 0x00BB
		{"SalFmtSetParmStr",ANY,(uint8_t)-1,any},
		// 0x00BC
		{"SalFmtSetProfile",ANY,(uint8_t)-1,any},
		// 0x00BD
		{"SalFmtValidateField",ANY,(uint8_t)-1,any},
		// 0x00BE
		{"SalFmtCopyProfile",ANY,(uint8_t)-1,any},
		// 0x00BF
		{"SalFmtFieldToStr",ANY,(uint8_t)-1,any},
		// 0x00C0
		{"SalPrtPrintForm",ANY,(uint8_t)-1,any},
		// 0x00C1
		{"SalPrtGetParmNum",ANY,(uint8_t)-1,any},
		// 0x00C2
		{"SalPrtSetParmNum",ANY,(uint8_t)-1,any},
		// 0x00C3
		{"SalPrtSetParmDefaults",ANY,(uint8_t)-1,any},
		// 0x00C4
		{"SalFmtStrToField",ANY,(uint8_t)-1,any},
		// 0x00C5
		{"SqlGetCursor",ANY,(uint8_t)-1,any},
		// 0x00C6
		{"SalGetItemName",ANY,(uint8_t)-1,any},
		// 0x00C7
		{"SalDebug",ANY,(uint8_t)-1,any},
		// 0x00C8
		{"SalFormGetParmNum",ANY,(uint8_t)-1,any},
		// 0x00C9
		{"SqlSystem",ANY,(uint8_t)-1,any},
		// 0x00CA
		{"SqlSetResultSet",ANY,(uint8_t)-1,any},
		// 0x00CB
		{"SalTimerSet",ANY,(uint8_t)-1,any},
		// 0x00CC
		{"SalTimerKill",ANY,(uint8_t)-1,any},
		// 0x00CD
		{"SalGetDataType",ANY,(uint8_t)-1,any},
		// 0x00CE
		{"SalGetMaxDataLength",ANY,(uint8_t)-1,any},
		// 0x00CF
		{"SalGetType",ANY,(uint8_t)-1,any},
		// 0x00D0
		{"SalTblGetColumnTitle",ANY,(uint8_t)-1,any},
		// 0x00D1
		{"SalTblSetColumnTitle",ANY,(uint8_t)-1,any},
		// 0x00D2
		{"SalWindowHandleToNumb",ANY,(uint8_t)-1,any},
		// 0x00D3
		{"SalNumberToWindowHand",ANY,(uint8_t)-1,any},
		// 0x00D4
		{"SqlSetLockTimeout",ANY,(uint8_t)-1,any},
		// 0x00D5
		{"SqlGetResultSetCount",ANY,(uint8_t)-1,any},
		// 0x00D6
		{"SqlGetModifiedRows",ANY,(uint8_t)-1,any},
		// 0x00D7
		{"SalNumRand",ANY,(uint8_t)-1,any},
		// 0x00D8
		{"SalNumSRand",ANY,(uint8_t)-1,any},
		// 0x00D9
		{"SalSendValidateMsg",ANY,(uint8_t)-1,any},
		// 0x00DA
		{"SalSendMsgToChildren",ANY,(uint8_t)-1,any},
		// 0x00DB
		{"SalPause",ANY,(uint8_t)-1,any},
		// 0x00DC
		{"SalTblSetColumnWidth",ANY,(uint8_t)-1,any},
		// 0x00DD
		{"SalTblQueryColumnWidt",ANY,(uint8_t)-1,any},
		// 0x00DE
		{"SalOutlineGetItemType",ANY,(uint8_t)-1,any},
		// 0x00DF
		{"SalOutlineGetItemText",ANY,(uint8_t)-1,any},
		// 0x00E0
		{"SalSetMaxDataLength",ANY,(uint8_t)-1,any},
		// 0x00E1
		{"SalResLoad",ANY,(uint8_t)-1,any},
		// 0x00E2
		{"SalAppFind",ANY,(uint8_t)-1,any},
		// 0x00E3
		{"SalStrIsValidIdentifi",ANY,(uint8_t)-1,any},
		// 0x00E4
		{"SalChangeLineCountLoc",ANY,(uint8_t)-1,any},
		// 0x00E5
		{"SalChangeLineCountNot",ANY,(uint8_t)-1,any},
		// 0x00E6
		{"SalIsOutlineSecondary",ANY,(uint8_t)-1,any},
		// 0x00E7
		{"SalChangeLineCountUnl",ANY,(uint8_t)-1,any},
		// 0x00E8
		{"SalItemGetLineNumber",ANY,(uint8_t)-1,any},
		// 0x00E9
		{"SalOutlineItemSetProp",ANY,(uint8_t)-1,any},
		// 0x00EA
		{"SalOutlineItemGetProp",ANY,(uint8_t)-1,any},
		// 0x00EB
		{"SalOutlineSetOutlineH",ANY,(uint8_t)-1,any},
		// 0x00EC
		{"SalOutlineShare",ANY,(uint8_t)-1,any},
		// 0x00ED
		{"SalFindWindow",ANY,(uint8_t)-1,any},
		// 0x00EE
		{"SalOutlineEnumWindowP",ANY,(uint8_t)-1,any},
		// 0x00EF
		{"SalOutlineEnumItemPro",ANY,(uint8_t)-1,any},
		// 0x00F0
		{"SalEditInsertObject",ANY,(uint8_t)-1,any},
		// 0x00F1
		{"SqlStore",ANY,(uint8_t)-1,any},
		// 0x00F2
		{"SqlRetrieve",ANY,(uint8_t)-1,any},
		// 0x00F3
		{"SqlDirectoryByName",ANY,(uint8_t)-1,any},
		// 0x00F4
		{"SqlGetParameter",ANY,(uint8_t)-1,any},
		// 0x00F5
		{"SqlSetParameter",ANY,(uint8_t)-1,any},
		// 0x00F6
		{"SalReportView",ANY,(uint8_t)-1,any},
		// 0x00F7
		{"SalReportPrint",ANY,(uint8_t)-1,any},
		// 0x00F8
		{"SalReportClose",ANY,(uint8_t)-1,any},
		// 0x00F9
		{"SalReportCmd",ANY,(uint8_t)-1,any},
		// 0x00FA
		{"SqlDropStoredCmd",ANY,(uint8_t)-1,any},
		// 0x00FB
		{"SalWinHelp",ANY,(uint8_t)-1,any},
		// 0x00FC
		{"SalReportReset",ANY,(uint8_t)-1,any},
		// 0x00FD
		{"SalAppEnable",ANY,(uint8_t)-1,any},
		// 0x00FE
		{"SalAppDisable",ANY,(uint8_t)-1,any},
		// 0x00FF
		{"SalListSetTabs",ANY,(uint8_t)-1,any},
		// 0x0100
		{"SalFileOpenExt",ANY,(uint8_t)-1,any},
		// 0x0101
		{"SalGetFirstChild",ANY,(uint8_t)-1,any},
		// 0x0102
		{"SalGetNextChild",ANY,(uint8_t)-1,any},
		// 0x0103
		{"SalDrawMenuBar",ANY,(uint8_t)-1,any},
		// 0x0104
		{"ArrayGet",ANY,(uint8_t)-1,any},
		// 0x0105
		{"ArrayPut",ANY,(uint8_t)-1,any},
		// 0x0106
		{"SalInitLPHSTRINGParam",ANY,(uint8_t)-1,any},
		// 0x0107
		{"SalReportCreate",ANY,(uint8_t)-1,any},
		// 0x0108
		{"SqlCommit",ANY,(uint8_t)-1,any},
		// 0x0109
		{"SalNumberToChar",ANY,(uint8_t)-1,any},
		// 0x010A
		{"SalPrtExtractRect",ANY,(uint8_t)-1,any},
		// 0x010B
		{"SalYieldEnable",ANY,(uint8_t)-1,any},
		// 0x010C
		{"SalYieldQueryState",ANY,(uint8_t)-1,any},
		// 0x010D
		{"SqlGetParameterAll",ANY,(uint8_t)-1,any},
		// 0x010E
		{"SqlSetParameterAll",ANY,(uint8_t)-1,any},
		// 0x010F
		{"SalOutlineLoad",ANY,(uint8_t)-1,any},
		// 0x0110
		{"SalOutlineUnload",ANY,(uint8_t)-1,any},
		// 0x0111
		{"SalOutlineTop",ANY,(uint8_t)-1,any},
		// 0x0112
		{"SalOutlineParent",ANY,(uint8_t)-1,any},
		// 0x0113
		{"SalOutlineItemType",ANY,(uint8_t)-1,any},
		// 0x0114
		{"SalOutlineNextLine",ANY,(uint8_t)-1,any},
		// 0x0115
		{"SalOutlineItemText",ANY,(uint8_t)-1,any},
		// 0x0116
		{"SalOutlineItemLevel",ANY,(uint8_t)-1,any},
		// 0x0117
		{"SalOutlineItemTitle",ANY,(uint8_t)-1,any},
		// 0x0118
		{"SalOutlineInsertItem",ANY,(uint8_t)-1,any},
		// 0x0119
		{"RunBaseClassMsg",ANY,(uint8_t)-1,any},
		// 0x011A
		{"SalOutlineSave",ANY,(uint8_t)-1,any},
		// 0x011B
		{"SalReportDlgOptions",ANY,(uint8_t)-1,any},
		// 0x011C
		{"SalStrLeftB",ANY,(uint8_t)-1,any},
		// 0x011D
		{"SalStringLengthB",ANY,(uint8_t)-1,any},
		// 0x011E
		{"SalStrMidB",ANY,(uint8_t)-1,any},
		// 0x011F
		{"SalStrReplaceB",ANY,(uint8_t)-1,any},
		// 0x0120
		{"SalStrRightB",ANY,(uint8_t)-1,any},
		// 0x0121
		{"SalColorSet",ANY,(uint8_t)-1,any},
		// 0x0122
		{"SalColorGet",ANY,(uint8_t)-1,any},
		// 0x0123
		{"SalColorToRGB",ANY,(uint8_t)-1,any},
		// 0x0124
		{"SalColorFromRGB",ANY,(uint8_t)-1,any},
		// 0x0125
		{"SalColorGetSysColor",ANY,(uint8_t)-1,any},
		// 0x0126
		{"SalFontSet",ANY,(uint8_t)-1,any},
		// 0x0127
		{"SalFontGet",ANY,(uint8_t)-1,any},
		// 0x0128
		{"SalFontGetSizes",ANY,(uint8_t)-1,any},
		// 0x0129
		{"SalFontGetNames",ANY,(uint8_t)-1,any},
		// 0x012A
		{"SalStrFull",ANY,(uint8_t)-1,any},
		// 0x012B
		{"SalStrHalf",ANY,(uint8_t)-1,any},
		// 0x012C
		{"SalStrFirstC",ANY,(uint8_t)-1,any},
		// 0x012D
		{"SalFileGetC",ANY,(uint8_t)-1,any},
		// 0x012E
		{"SalFilePutC",ANY,(uint8_t)-1,any},
		// 0x012F
		{"SalTblPopulate",ANY,(uint8_t)-1,any},
		// 0x0130
		{"SalTblDeleteSelected",ANY,(uint8_t)-1,any},
		// 0x0131
		{"SalTblDoInserts",ANY,(uint8_t)-1,any},
		// 0x0132
		{"SalTblDoUpdates",ANY,(uint8_t)-1,any},
		// 0x0133
		{"SalFileGetDrive",ANY,(uint8_t)-1,any},
		// 0x0134
		{"SalFileSetDrive",ANY,(uint8_t)-1,any},
		// 0x0135
		{"SalFileGetCurrentDire",ANY,(uint8_t)-1,any},
		// 0x0136
		{"SalFileSetCurrentDire",ANY,(uint8_t)-1,any},
		// 0x0137
		{"SalFileCopy",ANY,(uint8_t)-1,any},
		// 0x0138
		{"SalFileCreateDirector",ANY,(uint8_t)-1,any},
		// 0x0139
		{"SalFileRemoveDirector",ANY,(uint8_t)-1,any},
		// 0x013A
		{"SalEditCopyString",ANY,(uint8_t)-1,any},
		// 0x013B
		{"SalEditPasteString",ANY,(uint8_t)-1,any},
		// 0x013C
		{"SalTblAnyRows",ANY,(uint8_t)-1,any},
		// 0x013D
		{"SalTblCopyRows",ANY,(uint8_t)-1,any},
		// 0x013E
		{"SalListPopulate",ANY,(uint8_t)-1,any},
		// 0x013F
		{"SalStrIsValidNumber",ANY,(uint8_t)-1,any},
		// 0x0140
		{"SalStrIsValidDateTime",ANY,(uint8_t)-1,any},
		// 0x0141
		{"SalFmtIsValidPicture",ANY,(uint8_t)-1,any},
		// 0x0142
		{"SalFmtFormatNumber",ANY,(uint8_t)-1,any},
		// 0x0143
		{"SalFmtFormatDateTime",ANY,(uint8_t)-1,any},
		// 0x0144
		{"SalTblPasteRows",ANY,(uint8_t)-1,any},
		// 0x0145
		{"SalStrIsValidDecimal",ANY,(uint8_t)-1,any},
		// 0x0146
		{"SalOutlineIsBreak",ANY,(uint8_t)-1,any},
		// 0x0147
		{"SalOutlineCurrent",ANY,(uint8_t)-1,any},
		// 0x0148
		{"SalDlgSaveFile",ANY,(uint8_t)-1,any},
		// 0x0149
		{"SalOutlineSetBreak",ANY,(uint8_t)-1,any},
		// 0x014A
		{"SalOutlinePreviousSib",ANY,(uint8_t)-1,any},
		// 0x014B
		{"SalOutlineChildOfType",ANY,(uint8_t)-1,any},
		// 0x014C
		{"SalIsButtonChecked",ANY,(uint8_t)-1,any},
		// 0x014D
		{"SalDropFilesAcceptFil",ANY,(uint8_t)-1,any},
		// 0x014E
		{"SalEditPasteSpecial",ANY,(uint8_t)-1,any},
		// 0x014F
		{"SalCursorSetFile",ANY,(uint8_t)-1,any},
		// 0x0150
		{"SalCursorSetString",ANY,(uint8_t)-1,any},
		// 0x0151
		{"SalDragDropGetSource",ANY,(uint8_t)-1,any},
		// 0x0152
		{"SalDragDropGetTarget",ANY,(uint8_t)-1,any},
		// 0x0153
		{"SalDragDropEnableDrop",ANY,(uint8_t)-1,any},
		// 0x0154
		{"SalWinDebugBreak",ANY,(uint8_t)-1,any},
		// 0x0155
		{"HSGetRef",ANY,(uint8_t)-1,any},
		// 0x0156
		{"SalDragDropDisableDro",ANY,(uint8_t)-1,any},
		// 0x0157
		{"SalDragDropStart",ANY,(uint8_t)-1,any},
		// 0x0158
		{"SalDragDropStop",ANY,(uint8_t)-1,any},
		// 0x0159
		{"SalCursorClear",ANY,(uint8_t)-1,any},
		// 0x015A
		{"SalMapEnterToTab",ANY,(uint8_t)-1,any},
		// 0x015B
		{"SalPicClear",ANY,(uint8_t)-1,any},
		// 0x015C
		{"SalPicSetFile",ANY,(uint8_t)-1,any},
		// 0x015D
		{"SalPicSetFit",ANY,(uint8_t)-1,any},
		// 0x015E
		{"SalPicSetString",ANY,(uint8_t)-1,any},
		// 0x015F
		{"SalYieldStartMessages",ANY,(uint8_t)-1,any},
		// 0x0160
		{"SalYieldStopMessages",ANY,(uint8_t)-1,any},
		// 0x0161
		{"SalStrTokenize",ANY,(uint8_t)-1,any},
		// 0x0162
		{"SalListGetMultiSelect",ANY,(uint8_t)-1,any},
		// 0x0163
		{"SalListQueryMultiCoun",ANY,(uint8_t)-1,any},
		// 0x0164
		{"SalSetWindowLoc",ANY,(uint8_t)-1,any},
		// 0x0165
		{"SalGetWindowLoc",ANY,(uint8_t)-1,any},
		// 0x0166
		{"SalSetWindowSize",ANY,(uint8_t)-1,any},
		// 0x0167
		{"SalGetWindowSize",ANY,(uint8_t)-1,any},
		// 0x0168
		{"SalPixelsToFormUnits",ANY,(uint8_t)-1,any},
		// 0x0169
		{"SalFormUnitsToPixels",ANY,(uint8_t)-1,any},
		// 0x016A
		{"SalIsWindowEnabled",ANY,(uint8_t)-1,any},
		// 0x016B
		{"SalReportGetDateTimeV",ANY,(uint8_t)-1,any},
		// 0x016C
		{"SalUpdateWindow",ANY,(uint8_t)-1,any},
		// 0x016D
		{"SalMoveWindow",ANY,(uint8_t)-1,any},
		// 0x016E
		{"SalOutlineFirstChild",ANY,(uint8_t)-1,any},
		// 0x016F
		{"SalOutlineLastChild",ANY,(uint8_t)-1,any},
		// 0x0170
		{"SalOutlineNextSibling",ANY,(uint8_t)-1,any},
		// 0x0171
		{"SalListRedraw",ANY,(uint8_t)-1,any},
		// 0x0172
		{"SalNumberRandInit",ANY,(uint8_t)-1,any},
		// 0x0173
		{"SalNumberRandom",ANY,(uint8_t)-1,any},
		// 0x0174
		{"SalNumberTan",ANY,(uint8_t)-1,any},
		// 0x0175
		{"SalNumberArcTan",ANY,(uint8_t)-1,any},
		// 0x0176
		{"SalNumberArcTan2",ANY,(uint8_t)-1,any},
		// 0x0177
		{"SalNumberTanH",ANY,(uint8_t)-1,any},
		// 0x0178
		{"SalNumberSin",ANY,(uint8_t)-1,any},
		// 0x0179
		{"SalNumberArcSin",ANY,(uint8_t)-1,any},
		// 0x017A
		{"SalNumberSinH",ANY,(uint8_t)-1,any},
		// 0x017B
		{"SalNumberCos",ANY,(uint8_t)-1,any},
		// 0x017C
		{"SalNumberArcCos",ANY,(uint8_t)-1,any},
		// 0x017D
		{"SalNumberCosH",ANY,(uint8_t)-1,any},
		// 0x017E
		{"SalNumberAbs",ANY,(uint8_t)-1,any},
		// 0x017F
		{"SalNumberHypot",ANY,(uint8_t)-1,any},
		// 0x0180
		{"SalNumberLog",ANY,(uint8_t)-1,any},
		// 0x0181
		{"SalNumberLogBase10",ANY,(uint8_t)-1,any},
		// 0x0182
		{"SalNumberSqrt",ANY,(uint8_t)-1,any},
		// 0x0183
		{"SalCenterWindow",ANY,(uint8_t)-1,any},
		// 0x0184
		{"SalGetWindowState",ANY,(uint8_t)-1,any},
		// 0x0185
		{"SalPrtSetup",ANY,(uint8_t)-1,any},
		// 0x0186
		{"SalPrtGetDefault",ANY,(uint8_t)-1,any},
		// 0x0187
		{"SalPrtSetDefault",ANY,(uint8_t)-1,any},
		// 0x0188
		{"SalNumberHigh",ANY,(uint8_t)-1,any},
		// 0x0189
		{"SalNumberLow",ANY,(uint8_t)-1,any},
		// 0x018A
		{"SalHStringToNumber",ANY,(uint8_t)-1,any},
		// 0x018B
		{"SalNumberToHString",ANY,(uint8_t)-1,any},
		// 0x018C
		{"SalNumberPi",ANY,(uint8_t)-1,any},
		// 0x018D
		{"SalNumberExponent",ANY,(uint8_t)-1,any},
		// 0x018E
		{"SalNumberMin",ANY,(uint8_t)-1,any},
		// 0x018F
		{"SalNumberMax",ANY,(uint8_t)-1,any},
		// 0x0190
		{"SalStrIsValidCurrency",ANY,(uint8_t)-1,any},
		// 0x0191
		{"SalSetDefButton",ANY,(uint8_t)-1,any},
		// 0x0192
		{"SalGetDefButton",ANY,(uint8_t)-1,any},
		// 0x0193
		{"SalNumberPower",ANY,(uint8_t)-1,any},
		// 0x0194
		{"SalFmtGetPicture",ANY,(uint8_t)-1,any},
		// 0x0195
		{"SalFmtSetPicture",ANY,(uint8_t)-1,any},
		// 0x0196
		{"SalTblGetColumnWindow",ANY,(uint8_t)-1,any},
		// 0x0197
		{"SalTblQueryColumnPos",ANY,(uint8_t)-1,any},
		// 0x0198
		{"SalTblSetColumnPos",ANY,(uint8_t)-1,any},
		// 0x0199
		{"SalTblSetTableFlags",ANY,(uint8_t)-1,any},
		// 0x019A
		{"SalTblQueryTableFlags",ANY,(uint8_t)-1,any},
		// 0x019B
		{"SalTblQueryColumnFlag",ANY,(uint8_t)-1,any},
		// 0x019C
		{"SalTblDefineRowHeader",ANY,(uint8_t)-1,any},
		// 0x019D
		{"SalTblQueryRowHeader",ANY,(uint8_t)-1,any},
		// 0x019E
		{"SalTblDefineSplitWind",ANY,(uint8_t)-1,any},
		// 0x019F
		{"SalTblQuerySplitWindo",ANY,(uint8_t)-1,any},
		// 0x01A0
		{"SalTblSetLockedColumn",ANY,(uint8_t)-1,any},
		// 0x01A1
		{"SalTblQueryLockedColu",ANY,(uint8_t)-1,any},
		// 0x01A2
		{"SalTblQueryColumnID",ANY,(uint8_t)-1,any},
		// 0x01A3
		{"SalTblSetCellTextColo",ANY,(uint8_t)-1,any},
		// 0x01A4
		{"SalTblSetColumnFlags",ANY,(uint8_t)-1,any},
		// 0x01A5
		{"SalOutlineGetItemFlag",ANY,(uint8_t)-1,any},
		// 0x01A6
		{"SalOutlineSetItemFlag",ANY,(uint8_t)-1,any},
		// 0x01A7
		{"SalOutlineNextLikeIte",ANY,(uint8_t)-1,any},
		// 0x01A8
		{"SalReportGetNumberVar",ANY,(uint8_t)-1,any},
		// 0x01A9
		{"SalOutlineSetData",ANY,(uint8_t)-1,any},
		// 0x01AA
		{"SalOutlineDeleteItem",ANY,(uint8_t)-1,any},
		// 0x01AB
		{"SalOutlineItemIsInclu",ANY,(uint8_t)-1,any},
		// 0x01AC
		{"SalReportGetObjectVar",ANY,(uint8_t)-1,any},
		// 0x01AD
		{"SalReportGetStringVar",ANY,(uint8_t)-1,any},
		// 0x01AE
		{"SalTblSetFlagsAnyRows",ANY,(uint8_t)-1,any},
		// 0x01AF
		{"SalTblDoDeletes",ANY,(uint8_t)-1,any},
		// 0x01B0
		{"SalEditPasteLink",ANY,(uint8_t)-1,any},
		// 0x01B1
		{"SalReportSetDateTimeV",ANY,(uint8_t)-1,any},
		// 0x01B2
		{"SalReportSetNumberVar",ANY,(uint8_t)-1,any},
		// 0x01B3
		{"SalReportSetObjectVar",ANY,(uint8_t)-1,any},
		// 0x01B4
		{"SalDDEStartSession",ANY,(uint8_t)-1,any},
		// 0x01B5
		{"SalDDEStopSession",ANY,(uint8_t)-1,any},
		// 0x01B6
		{"SalDDERequest",ANY,(uint8_t)-1,any},
		// 0x01B7
		{"SalDDESendExecute",ANY,(uint8_t)-1,any},
		// 0x01B8
		{"SalDDEStartServer",ANY,(uint8_t)-1,any},
		// 0x01B9
		{"SalDDEStopServer",ANY,(uint8_t)-1,any},
		// 0x01BA
		{"SalDDESendToClient",ANY,(uint8_t)-1,any},
		// 0x01BB
		{"SalReportSetStringVar",ANY,(uint8_t)-1,any},
		// 0x01BC
		{"RunBaseClassMsg",ANY,(uint8_t)-1,any},
		// 0x01BD
		{"SalGetVersion",ANY,(uint8_t)-1,any},
		// 0x01BE
		{"SqlSetInMessage",ANY,(uint8_t)-1,any},
		// 0x01BF
		{"SqlSetOutMessage",ANY,(uint8_t)-1,any},
		// 0x01C0
		{"SqlPrepareAndExecute",ANY,(uint8_t)-1,any},
		// 0x01C1
		{"SalPicGetString",ANY,(uint8_t)-1,any},
		// 0x01C2
		{"SalEditCanPasteLink",ANY,(uint8_t)-1,any},
		// 0x01C3
		{"SalEditCanPasteSpecia",ANY,(uint8_t)-1,any},
		// 0x01C4
		{"SalEditCanInsertObjec",ANY,(uint8_t)-1,any},
		// 0x01C5
		{"SalOLEAnyActive",ANY,(uint8_t)-1,any},
		// 0x01C6
		{"SalEditCanPasteFrom",ANY,(uint8_t)-1,any},
		// 0x01C7
		{"SalEditPasteFrom",ANY,(uint8_t)-1,any},
		// 0x01C8
		{"SalOLEAnyLinked",ANY,(uint8_t)-1,any},
		// 0x01C9
		{"SalOLEDoVerb",ANY,(uint8_t)-1,any},
		// 0x01CA
		{"SalOLEFileInsert",ANY,(uint8_t)-1,any},
		// 0x01CB
		{"SalOLEGetServers",ANY,(uint8_t)-1,any},
		// 0x01CC
		{"SalEditCopyTo",ANY,(uint8_t)-1,any},
		// 0x01CD
		{"SalEditCanCopyTo",ANY,(uint8_t)-1,any},
		// 0x01CE
		{"SalOLEGetVerbs",ANY,(uint8_t)-1,any},
		// 0x01CF
		{"SalOLELinkProperties",ANY,(uint8_t)-1,any},
		// 0x01D0
		{"SalDlgOpenFile",ANY,(uint8_t)-1,any},
		// 0x01D1
		{"SalDlgChooseFont",ANY,(uint8_t)-1,any},
		// 0x01D2
		{"SalNumberToStrX",ANY,(uint8_t)-1,any},
		// 0x01D3
		{"SalStrLeftX",ANY,(uint8_t)-1,any},
		// 0x01D4
		{"SalStrLowerX",ANY,(uint8_t)-1,any},
		// 0x01D5
		{"SalStrMidX",ANY,(uint8_t)-1,any},
		// 0x01D6
		{"SalStrProperX",ANY,(uint8_t)-1,any},
		// 0x01D7
		{"SalStrRepeatX",ANY,(uint8_t)-1,any},
		// 0x01D8
		{"SalStrReplaceX",ANY,(uint8_t)-1,any},
		// 0x01D9
		{"SalStrRightX",ANY,(uint8_t)-1,any},
		// 0x01DA
		{"SalStrTrimX",ANY,(uint8_t)-1,any},
		// 0x01DB
		{"SalStrUpperX",ANY,(uint8_t)-1,any},
		// 0x01DC
		{"SqlGetErrorTextX",ANY,(uint8_t)-1,any},
		// 0x01DD
		{"SalOutlineItemTextX",ANY,(uint8_t)-1,any},
		// 0x01DE
		{"SalOutlineItemTitleX",ANY,(uint8_t)-1,any},
		// 0x01DF
		{"SalOutlineCreateDesig",ANY,(uint8_t)-1,any},
		// 0x01E0
		{"SalOutlineSetFormFlag",ANY,(uint8_t)-1,any},
		// 0x01E1
		{"SalOutlineGetFormFlag",ANY,(uint8_t)-1,any},
		// 0x01E2
		{"SalOutlineSetDrawTool",ANY,(uint8_t)-1,any},
		// 0x01E3
		{"SalOutlineGetDrawTool",ANY,(uint8_t)-1,any},
		// 0x01E4
		{"SalOutlineCanAlignWin",ANY,(uint8_t)-1,any},
		// 0x01E5
		{"SalOutlineAlignWindow",ANY,(uint8_t)-1,any},
		// 0x01E6
		{"SalOutlineCanMoveToFr",ANY,(uint8_t)-1,any},
		// 0x01E7
		{"SalOutlineCanMoveToBa",ANY,(uint8_t)-1,any},
		// 0x01E8
		{"SalOutlineMoveToFront",ANY,(uint8_t)-1,any},
		// 0x01E9
		{"SalOutlineMoveToBack",ANY,(uint8_t)-1,any},
		// 0x01EA
		{"SalOutlineOrderTabs",ANY,(uint8_t)-1,any},
		// 0x01EB
		{"SalOutlineDontCustomi",ANY,(uint8_t)-1,any},
		// 0x01EC
		{"SalOutlineSetCustomCm",ANY,(uint8_t)-1,any},
		// 0x01ED
		{"SalOutlineClearCustom",ANY,(uint8_t)-1,any},
		// 0x01EE
		{"SalOutlineItemOfWindo",ANY,(uint8_t)-1,any},
		// 0x01EF
		{"SalOutlineOutlineOfWi",ANY,(uint8_t)-1,any},
		// 0x01F0
		{"SalOutlineWindowOfIte",ANY,(uint8_t)-1,any},
		// 0x01F1
		{"SalOutlineLockDrawToo",ANY,(uint8_t)-1,any},
		// 0x01F2
		{"SalOutlineIsWindowIte",ANY,(uint8_t)-1,any},
		// 0x01F3
		{"SalOutlineIsItemMarke",ANY,(uint8_t)-1,any},
		// 0x01F4
		{"SalOutlineChangeSelec",ANY,(uint8_t)-1,any},
		// 0x01F5
		{"SalOutlineIsDrawToolL",ANY,(uint8_t)-1,any},
		// 0x01F6
		{"SalOutlineCustomizeIt",ANY,(uint8_t)-1,any},
		// 0x01F7
		{"SalOutlineItemChangeU",ANY,(uint8_t)-1,any},
		// 0x01F8
		{"SalOutlineWindowItemO",ANY,(uint8_t)-1,any},
		// 0x01F9
		{"SalOutlineItemTypeTex",ANY,(uint8_t)-1,any},
		// 0x01FA
		{"SalOutlineSetTypeData",ANY,(uint8_t)-1,any},
		// 0x01FB
		{"SalOutlineCreateItem",ANY,(uint8_t)-1,any},
		// 0x01FC
		{"SalOutlineFirstMarked",ANY,(uint8_t)-1,any},
		// 0x01FD
		{"SalOutlineNextMarked",ANY,(uint8_t)-1,any},
		// 0x01FE
		{"SalDDEGetExecuteStrin",ANY,(uint8_t)-1,any},
		// 0x01FF
		{"SalListQueryTextX",ANY,(uint8_t)-1,any},
		// 0x0200
		{"SalDropFilesQueryPoin",ANY,(uint8_t)-1,any},
		// 0x0201
		{"SalDropFilesQueryFile",ANY,(uint8_t)-1,any},
		// 0x0202
		{"SalMDITile",ANY,(uint8_t)-1,any},
		// 0x0203
		{"SalMDIArrangeIcons",ANY,(uint8_t)-1,any},
		// 0x0204
		{"SalMDICascade",ANY,(uint8_t)-1,any},
		// 0x0205
		{"SalStatusSetText",ANY,(uint8_t)-1,any},
		// 0x0206
		{"SalTblCreateColumn",ANY,(uint8_t)-1,any},
		// 0x0207
		{"SalTblGetColumnText",ANY,(uint8_t)-1,any},
		// 0x0208
		{"SalTblSetColumnText",ANY,(uint8_t)-1,any},
		// 0x0209
		{"SalOutlineGetDTData",ANY,(uint8_t)-1,any},
		// 0x020A
		{"SqlContextClear",ANY,(uint8_t)-1,any},
		// 0x020B
		{"SqlContextSet",ANY,(uint8_t)-1,any},
		// 0x020C
		{"SqlImmediateContext",ANY,(uint8_t)-1,any},
		// 0x020D
		{"SalGetProfileString",ANY,(uint8_t)-1,any},
		// 0x020E
		{"SalSetDLLDataMode",ANY,(uint8_t)-1,any},
		// 0x020F
		{"SalAccessSWVariable",ANY,(uint8_t)-1,any},
		// 0x0210
		{"SalWriteSWString",ANY,(uint8_t)-1,any},
		// 0x0211
		{"SalReadSWString",ANY,(uint8_t)-1,any},
		// 0x0212
		{"SalReportTableCreate",ANY,(uint8_t)-1,any},
		// 0x0213
		{"SalReportTablePrint",ANY,(uint8_t)-1,any},
		// 0x0214
		{"SalReportTableView",ANY,(uint8_t)-1,any},
		// 0x0215
		{"SalReportSetPrintPara",ANY,(uint8_t)-1,any},
		// 0x0216
		{"SqlErrorText",ANY,(uint8_t)-1,any},
		// 0x0217
		{"SqlExecutionPlan",ANY,(uint8_t)-1,any},
		// 0x0218
		{"SalOLEServerInsert",ANY,(uint8_t)-1,any},
		// 0x0219
		{"SalLoadAppAndWait",ANY,(uint8_t)-1,any},
		// 0x021A
		{"SalTblColumnAverage",ANY,(uint8_t)-1,any},
		// 0x021B
		{"SalTblColumnSum",ANY,(uint8_t)-1,any},
		// 0x021C
		{"SalTrackPopupMenu",ANY,(uint8_t)-1,any},
		// 0x021D
		{"SalStatusSetVisible",ANY,(uint8_t)-1,any},
		// 0x021E
		{"SalTBarSetVisible",ANY,(uint8_t)-1,any},
		// 0x021F
		{"SalStatusGetText",ANY,(uint8_t)-1,any},
		// 0x0220
		{"SalTblSortRows",ANY,(uint8_t)-1,any},
		// 0x0221
		{"SalTblDestroyColumns",ANY,(uint8_t)-1,any},
		// 0x0222
		{"SalCreateWindowFromStr",ANY,(uint8_t)-1,any},
		// 0x0223
		{"SalFmtGetInputMask",ANY,(uint8_t)-1,any},
		// 0x0224
		{"SalFmtSetInputMask",ANY,(uint8_t)-1,any},
		// 0x0225
		{"SalFmtIsValidInputMas",ANY,(uint8_t)-1,any},
		// 0x0226
		{"SalFmtUnmaskInput",ANY,(uint8_t)-1,any},
		// 0x0227
		{"SalStrCompress",ANY,(uint8_t)-1,any},
		// 0x0228
		{"SalStrUncompress",ANY,(uint8_t)-1,any},
		// 0x0229
		{"SalFileGetDateTime",ANY,(uint8_t)-1,any},
		// 0x022A
		{"SalFileSetDateTime",ANY,(uint8_t)-1,any},
		// 0x022B
		{"SalSetProfileString",ANY,(uint8_t)-1,any},
		// 0x022C
		{"SalGetProfileInt",ANY,(uint8_t)-1,any},
		// 0x022D
		{"SalDisableWindowAndLa",ANY,(uint8_t)-1,any},
		// 0x022E
		{"SalEnableWindowAndLab",ANY,(uint8_t)-1,any},
		// 0x022F
		{"SalGetWindowLabel",ANY,(uint8_t)-1,any},
		// 0x0230
		{"SalModalDialogFromStr",ANY,(uint8_t)-1,any},
		// 0x0231
		{"SalOutlineBlockNotifi",ANY,(uint8_t)-1,any},
		// 0x0232
		{"SalOLEUpdateActive",ANY,(uint8_t)-1,any},
		// 0x0233
		{"SalOutlineSetDTData",ANY,(uint8_t)-1,any},
		// 0x0234
		{"SalOutlineSetItemClas",ANY,(uint8_t)-1,any},
		// 0x0235
		{"ObjectIsValid",ANY,(uint8_t)-1,any},
		// 0x0236
		{"NULL",ANY,(uint8_t)-1,any},
		// 0x0237
		{"NULL",ANY,(uint8_t)-1,any},
		// 0x0238
		{"SalCursorSet",ANY,(uint8_t)-1,any},
		// 0x0239
		{"SalShowWindowAndLabel",ANY,(uint8_t)-1,any},
		// 0x023A
		{"SalHideWindowAndLabel",ANY,(uint8_t)-1,any},
		// 0x023B
		{"SalCurrentLineNumber",ANY,(uint8_t)-1,any},
		// 0x023C
		{"SalFlashWindow",ANY,(uint8_t)-1,any},
		// 0x023D
		{"SalReportPrintToFile",ANY,(uint8_t)-1,any},
		// 0x023E
		{"NULL",ANY,(uint8_t)-1,any},
		// 0x023F
		{"SalTblSetRow",ANY,(uint8_t)-1,any},
		// 0x0240
		{"SalTblSetView",ANY,(uint8_t)-1,any},
		// 0x0241
		{"SalTblQueryView",ANY,(uint8_t)-1,any},
		// 0x0242
		{"SalPicSet",ANY,(uint8_t)-1,any},
		// 0x0243
		{"SalGetWindowLabelText",ANY,(uint8_t)-1,any},
		// 0x0244
		{"SalSetWindowLabelText",ANY,(uint8_t)-1,any},
		// 0x0245
		{"SalOutlineCopyItem",ANY,(uint8_t)-1,any},
		// 0x0246
		{"SalOutlineGetAttribut",ANY,(uint8_t)-1,any},
		// 0x0247
		{"NULL",ANY,(uint8_t)-1,any},
		// 0x0248
		{"SalFmtKeepMask",ANY,(uint8_t)-1,any},
		// 0x0249
		{"SalResId",ANY,(uint8_t)-1,any},
		// 0x024A
		{"SalOutlineIsClassChil",ANY,(uint8_t)-1,any},
		// 0x024B
		{"SqlPLSQLExecute",ANY,(uint8_t)-1,any},
		// 0x024C
		{"SqlPLSQLCommand",ANY,(uint8_t)-1,any},
		// 0x024D
		{"RunBaseClassChildMsg",ANY,(uint8_t)-1,any},
		// 0x024E
		{"SalHStringRef",ANY,(uint8_t)-1,any},
		// 0x024F
		{"SalHStringUnRef",ANY,(uint8_t)-1,any},
		// 0x0250
		{"SalArrayCreate",ANY,(uint8_t)-1,any},
		// 0x0251
		{"SalArrayDestroy",ANY,(uint8_t)-1,any},
		// 0x0252
		{"SalFireEvent",ANY,(uint8_t)-1,any},
		// 0x0253
		{"SetBlobVariant",ANY,(uint8_t)-1,any},
		// 0x0254
		{"GetBlobVariant",ANY,(uint8_t)-1,any},
		// 0x0255
		{"NULL",ANY,(uint8_t)-1,any},
		// 0x0256
		{"NULL",ANY,(uint8_t)-1,any},
		// 0x0257
		{"NULL",ANY,(uint8_t)-1,any},
		// 0x0258
		{"NULL",ANY,(uint8_t)-1,any},
		// 0x0259
		{"NULL",ANY,(uint8_t)-1,any},
		// 0x025A
		{"NULL",ANY,(uint8_t)-1,any},
		// 0x025B
		{"SalOutlineRefreshIncl",ANY,(uint8_t)-1,any},
		// 0x025C
		{"SalValidateSet",ANY,(uint8_t)-1,any},
		// 0x025D
		{"NULL",ANY,(uint8_t)-1,any},
		// 0x025E
		{"NULL",ANY,(uint8_t)-1,any},
		// 0x025F
		{"SqlGetError",ANY,(uint8_t)-1,any},
		// 0x0260
		{"SalOutlineInfo",ANY,(uint8_t)-1,any},
		// 0x0261
		{"SalOutlineSaveAsText",ANY,(uint8_t)-1,any},
		// 0x0262
		{"SalDataQuerySources",ANY,(uint8_t)-1,any},
		// 0x0263
		{"SalDataQueryFields",ANY,(uint8_t)-1,any},
		// 0x0264
		{"SalDataGetSourceWindo",ANY,(uint8_t)-1,any},
		// 0x0265
		{"SalDataGetFieldWindow",ANY,(uint8_t)-1,any},
		// 0x0266
		{"SalDataQueryFieldExte",ANY,(uint8_t)-1,any},
		// 0x0267
		{"SalDataGetFieldData",ANY,(uint8_t)-1,any},
		// 0x0268
		{"SalWindowSetProperty",ANY,(uint8_t)-1,any},
		// 0x0269
		{"SalWindowGetProperty",ANY,(uint8_t)-1,any},
		// 0x026A
		{"HSCreateDesignHeap",ANY,(uint8_t)-1,any},
		// 0x026B
		{"HSDestroyDesignHeap",ANY,(uint8_t)-1,any},
		// 0x026C
		{"SalOutlineSetAppChang",ANY,(uint8_t)-1,any},
		// 0x026D
		{"SalOutlineSetAppUncom",ANY,(uint8_t)-1,any},
		// 0x026E
		{"SalOutlineItemLineCou",ANY,(uint8_t)-1,any},
		// 0x026F
		{"SalOutlineWindowOfIte",ANY,(uint8_t)-1,any},
		// 0x0270
		{"SalOutlineItemOfWindo",ANY,(uint8_t)-1,any},
		// 0x0271
		{"SalOutlinePropertyCha",ANY,(uint8_t)-1,any},
		// 0x0272
		{"SalOutlineEnumSymbols",ANY,(uint8_t)-1,any},
		// 0x0273
		{"SalOutlineGetFunParam",ANY,(uint8_t)-1,any},
		// 0x0274
		{"SqlConnectUsingCursor",ANY,(uint8_t)-1,any},
		// 0x0275
		{"SqlGetSqlHandle",ANY,(uint8_t)-1,any},
		// 0x0276
		{"SqlDisconnectWithoutC",ANY,(uint8_t)-1,any},
		// 0x0277
		{"SqlConnectTransaction",ANY,(uint8_t)-1,any},
		// 0x0278
		{"NULL",ANY,(uint8_t)-1,any},
		// 0x0279
		{"NULL",ANY,(uint8_t)-1,any},
		// 0x027A
		{"NULL",ANY,(uint8_t)-1,any},
		// 0x027B
		{"NULL",ANY,(uint8_t)-1,any},
		// 0x027C
		{"NULL",ANY,(uint8_t)-1,any},
		// 0x027D
		{"SqlSetLongBindDatatyp",ANY,(uint8_t)-1,any},
		// 0x027E
		{"SalBIDIDlgChooseFonts",ANY,(uint8_t)-1,any},
		// 0x027F
		{"SalArraySetUpperBound",ANY,(uint8_t)-1,any},
		// 0x0280
		{"SalArrayGetLowerBound",ANY,(uint8_t)-1,any},
		// 0x0281
		{"SalArrayGetUpperBound",ANY,(uint8_t)-1,any},
		// 0x0282
		{"SalArrayDimCount",ANY,(uint8_t)-1,any},
		// 0x0283
		{"SalArrayIsEmpty",ANY,(uint8_t)-1,any},
		// 0x0284
		{"SalWindowClassName",ANY,(uint8_t)-1,any},
		// 0x0285
		{"SalWindowIsDerivedFro",ANY,(uint8_t)-1,any},
		// 0x0286
		{"SalDisableAllWindows",ANY,(uint8_t)-1,any},
		// 0x0287
		{"SalEnableAllWindows",ANY,(uint8_t)-1,any},
		// 0x0288
		{"ArrayGetDataType",ANY,(uint8_t)-1,any},
		// 0x0289
		{"SalParseStatement",ANY,(uint8_t)-1,any},
		// 0x028A
		{"ArraySetMDBounds",ANY,(uint8_t)-1,any},
		// 0x028B
		{"ArrayIndex",ANY,(uint8_t)-1,any},
		// 0x028C
		{"SalDialogOpenExisting",ANY,(uint8_t)-1,any},
		// 0x028D
		{"SalOutlineFindTemplat",ANY,(uint8_t)-1,any},
		// 0x028E
		{"SalOutlineIsTemplateO",ANY,(uint8_t)-1,any},
		// 0x028F
		{"SqlContextSetToForm",ANY,(uint8_t)-1,any},
		// 0x0290
		{"SalShowToolBoxWindow",ANY,(uint8_t)-1,any},
		// 0x0291
		{"SalQOConnect",ANY,(uint8_t)-1,any},
		// 0x0292
		{"SalQOGetConnectInfo",ANY,(uint8_t)-1,any},
		// 0x0293
		{"NULL",ANY,(uint8_t)-1,any},
		// 0x0294
		{"NULL",ANY,(uint8_t)-1,any},
		// 0x0295
		{"SalAutoNameObject",ANY,(uint8_t)-1,any},
		// 0x0296
		{"SqlHandleSetParameter",ANY,(uint8_t)-1,any},
		// 0x0297
		{"SalLogResources",ANY,(uint8_t)-1,any},
		// 0x0298
		{"SalGetCurrentDesignWi",ANY,(uint8_t)-1,any},
		// 0x0299
		{"ClsUdvRefLock",ANY,(uint8_t)-1,any},
		// 0x029A
		{"HSNumStringsInUse",ANY,(uint8_t)-1,any},
		// 0x029B
		{"SalOutlineClassSize",ANY,(uint8_t)-1,any},
		// 0x029C
		{"ArrayUDVAddress",ANY,(uint8_t)-1,any},
		// 0x029D
		{"ClsUdvRefOfCurUdv",ANY,(uint8_t)-1,any},
		// 0x029E
		{"SalOutlineItemRemoveP",ANY,(uint8_t)-1,any},
		// 0x029F
		{"SalWindowRemoveProper",ANY,(uint8_t)-1,any},
		// 0x02A0
		{"SalOutlineHighlightIt",ANY,(uint8_t)-1,any},
		// 0x02A1
		{"SqlVarSetup",ANY,(uint8_t)-1,any},
		// 0x02A2
		{"SalQOLoadCatalogTable",ANY,(uint8_t)-1,any},
		// 0x02A3
		{"SalQOReleaseTableDefs",ANY,(uint8_t)-1,any},
		// 0x02A4
		{"SalQOGetTableInfoFrom",ANY,(uint8_t)-1,any},
		// 0x02A5
		{"SalQOLoadTableColumns",ANY,(uint8_t)-1,any},
		// 0x02A6
		{"SalQOGetColumnInfoFro",ANY,(uint8_t)-1,any},
		// 0x02A7
		{"SalQOReleaseColumnDef",ANY,(uint8_t)-1,any},
		// 0x02A8
		{"SalOutlineBaseClassPr",ANY,(uint8_t)-1,any},
		// 0x02A9
		{"SalOutlineItemSetBlob",ANY,(uint8_t)-1,any},
		// 0x02AA
		{"SalOutlineItemGetBlob",ANY,(uint8_t)-1,any},
		// 0x02AB
		{"SalOutlineUnlockBlob",ANY,(uint8_t)-1,any},
		// 0x02AC
		{"SalStrGetIdentifierIn",ANY,(uint8_t)-1,any},
		// 0x02AD
		{"SalStrGetIdentifier",ANY,(uint8_t)-1,any},
		// 0x02AE
		{"SalStaticFirst",ANY,(uint8_t)-1,any},
		// 0x02AF
		{"SalStaticNext",ANY,(uint8_t)-1,any},
		// 0x02B0
		{"SalStaticGetItem",ANY,(uint8_t)-1,any},
		// 0x02B1
		{"SalStaticHide",ANY,(uint8_t)-1,any},
		// 0x02B2
		{"SalStaticShow",ANY,(uint8_t)-1,any},
		// 0x02B3
		{"SalStaticIsVisible",ANY,(uint8_t)-1,any},
		// 0x02B4
		{"SalOutlineCloseDesign",ANY,(uint8_t)-1,any},
		// 0x02B5
		{"SalStaticSetLoc",ANY,(uint8_t)-1,any},
		// 0x02B6
		{"SalStaticGetLoc",ANY,(uint8_t)-1,any},
		// 0x02B7
		{"SalStaticGetSize",ANY,(uint8_t)-1,any},
		// 0x02B8
		{"SalStaticSetSize",ANY,(uint8_t)-1,any},
		// 0x02B9
		{"SalStaticGetLabel",ANY,(uint8_t)-1,any},
		// 0x02BA
		{"SalQODisplayConnectEr",ANY,(uint8_t)-1,any},
		// 0x02BB
		{"SalOutlineCanInsert",ANY,(uint8_t)-1,any},
		// 0x02BC
		{"SalOutlineItemToTagge",ANY,(uint8_t)-1,any},
		// 0x02BD
		{"SalOutlineClassBaseOf",ANY,(uint8_t)-1,any},
		// 0x02BE
		{"SalOutlineVarOffset",ANY,(uint8_t)-1,any},
		// 0x02BF
		{"SalOutlineIsImportedF",ANY,(uint8_t)-1,any},
		// 0x02C0
		{"SalOutlineItemToLibHI",ANY,(uint8_t)-1,any},
		// 0x02C1
		{"SalSegmentSysGlobals",ANY,(uint8_t)-1,any},
		// 0x02C2
		{"SalSegmentUserGlobals",ANY,(uint8_t)-1,any},
		// 0x02C3
		{"SalDynalibGlobalVarAd",ANY,(uint8_t)-1,any},
		// 0x02C4
		{"SalSegmentClassInstan",ANY,(uint8_t)-1,any},
		// 0x02C5
		{"SalSegmentClassStatic",ANY,(uint8_t)-1,any},
		// 0x02C6
		{"SalArrayCreateUdv",ANY,(uint8_t)-1,any},
		// 0x02C7
		{"SalOutlineIsCompiled",ANY,(uint8_t)-1,any},
		// 0x02C8
		{"SalOutlineGetNotifyIt",ANY,(uint8_t)-1,any},
		// 0x02C9
		{"SalOutlineAddNotifyWi",ANY,(uint8_t)-1,any},
		// 0x02CA
		{"SalOutlineRemoveNotif",ANY,(uint8_t)-1,any},
		// 0x02CB
		{"SalOutlineQueryUserMo",ANY,(uint8_t)-1,any},
		// 0x02CC
		{"SalOutlineIsClassObje",ANY,(uint8_t)-1,any},
		// 0x02CD
		{"SalTblQueryColumnCell",ANY,(uint8_t)-1,any},
		// 0x02CE
		{"SalTblDefineDropDownL",ANY,(uint8_t)-1,any},
		// 0x02CF
		{"SalTblQueryDropDownLi",ANY,(uint8_t)-1,any},
		// 0x02D0
		{"SalTblDefinePopupEdit",ANY,(uint8_t)-1,any},
		// 0x02D1
		{"SalTblQueryPopupEditC",ANY,(uint8_t)-1,any},
		// 0x02D2
		{"SalTblDefineCheckBoxC",ANY,(uint8_t)-1,any},
		// 0x02D3
		{"SalTblQueryCheckBoxCo",ANY,(uint8_t)-1,any},
		// 0x02D4
		{"SalTblQueryLinesPerRo",ANY,(uint8_t)-1,any},
		// 0x02D5
		{"SalTblSetLinesPerRow",ANY,(uint8_t)-1,any},
		// 0x02D6
		{"SalOutlineMergeInclud",ANY,(uint8_t)-1,any},
		// 0x02D7
		{"SalLoadAppAndProcessM",ANY,(uint8_t)-1,any},
		// 0x02D8
		{"SalCreateWindowEx",ANY,(uint8_t)-1,any},
		// 0x02D9
		{"SalCreateWindowExFrom",ANY,(uint8_t)-1,any},
		// 0x02DA
		{"SalOutlineShowDesignW",ANY,(uint8_t)-1,any},
		// 0x02DB
		{"SalCDKGetChildTypeByN",ANY,(uint8_t)-1,any},
		// 0x02DC
		{"SalOutlineGetAppChang",ANY,(uint8_t)-1,any},
		// 0x02DD
		{"SalCDKGetValidChildre",ANY,(uint8_t)-1,any},
		// 0x02DE
		{"SalCDKGetChildByName",ANY,(uint8_t)-1,any},
		// 0x02DF
		{"SalCDKGetName",ANY,(uint8_t)-1,any},
		// 0x02E0
		{"SqlGetLastStatement",ANY,(uint8_t)-1,any},
		// 0x02E1
		{"SalCDKParseTitle",ANY,(uint8_t)-1,any},
		// 0x02E2
		{"SalOutlineReportError",ANY,(uint8_t)-1,any},
		// 0x02E3
		{"SalOutlineInheritFrom",ANY,(uint8_t)-1,any},
		// 0x02E4
		{"SalOutlineItemGetProp",ANY,(uint8_t)-1,any},
		// 0x02E5
		{"SalOutlineSelectNewIt",ANY,(uint8_t)-1,any},
		// 0x02E6
		{"SalOutlineIsUserWindo",ANY,(uint8_t)-1,any},
		// 0x02E7
		{"SalUseRegistry",ANY,(uint8_t)-1,any},
		// 0x02E8
		{"SalSetDDMErrorFun",ANY,(uint8_t)-1,any},
		// 0x02E9
		{"SalGetRegistryString",ANY,(uint8_t)-1,any},
		// 0x02EA
		{"SalSetRegistryString",ANY,(uint8_t)-1,any},
		// 0x02EB
		{"SalGetBuildSettings",ANY,(uint8_t)-1,any},
		// 0x02EC
		{"SalSetBuildSettings",ANY,(uint8_t)-1,any},
		// 0x02ED
		{"SalOutlineNotify",ANY,(uint8_t)-1,any},
		// 0x02EE
		{"SalOutlineDoUICommand",ANY,(uint8_t)-1,any},
		// 0x02EF
		{"SalOutlineCanDoUIComm",ANY,(uint8_t)-1,any},
		// 0x02F0
		{"SalOutlineGetOneUISel",ANY,(uint8_t)-1,any},
		// 0x02F1
		{"SalIdleRegisterWindow",ANY,(uint8_t)-1,any},
		// 0x02F2
		{"SalIdleUnregisterWind",ANY,(uint8_t)-1,any},
		// 0x02F3
		{"SalIdleKick",ANY,(uint8_t)-1,any},
		// 0x02F4
		{"SalContextMenuSetPopu",ANY,(uint8_t)-1,any},
		// 0x02F5
		{"SalTblObjectsFromPoin",ANY,(uint8_t)-1,any},
		// 0x02F6
		{"SalProfileRegisterWin",ANY,(uint8_t)-1,any},
		// 0x02F7
		{"SalProfileUnregisterW",ANY,(uint8_t)-1,any},
		// 0x02F8
		{"SalPicSetHandle",ANY,(uint8_t)-1,any},
		// 0x02F9
		{"SalOutlineCreateClass",ANY,(uint8_t)-1,any},
		// 0x02FA
		{"SalOutlineOutlineOfUI",ANY,(uint8_t)-1,any},
		// 0x02FB
		{"SalOutlineUIFrameOfOu",ANY,(uint8_t)-1,any},
		// 0x02FC
		{"SalOutlineGetFirstUIS",ANY,(uint8_t)-1,any},
		// 0x02FD
		{"SalOutlineGetNextUISe",ANY,(uint8_t)-1,any},
		// 0x02FE
		{"SalOutlineEnableDesig",ANY,(uint8_t)-1,any},
		// 0x02FF
		{"SalOutlineActivateUIV",ANY,(uint8_t)-1,any},
		// 0x0300
		{"SalOutlineIsUIViewAct",ANY,(uint8_t)-1,any},
		// 0x0301
		{"SalOutlineGetFileName",ANY,(uint8_t)-1,any},
		// 0x0302
		{"SalOutlineEditGetText",ANY,(uint8_t)-1,any},
		// 0x0303
		{"SalOutlineEditGetItem",ANY,(uint8_t)-1,any},
		// 0x0304
		{"SalOutlineEditSetText",ANY,(uint8_t)-1,any},
		// 0x0305
		{"SalOutlineGetIncludin",ANY,(uint8_t)-1,any},
		// 0x0306
		{"SalOutlineGetUIViewIn",ANY,(uint8_t)-1,any},
		// 0x0307
		{"SalOutlineFirstDispla",ANY,(uint8_t)-1,any},
		// 0x0308
		{"SalOutlineNextDisplay",ANY,(uint8_t)-1,any},
		// 0x0309
		{"SalOutlineClassNameOf",ANY,(uint8_t)-1,any},
		// 0x030A
		{"SalResourceGet",ANY,(uint8_t)-1,any},
		// 0x030B
		{"SalResourceSet",ANY,(uint8_t)-1,any},
		// 0x030C
		{"OraPLSQLPrepare",ANY,(uint8_t)-1,any},
		// 0x030D
		{"OraPLSQLExecute",ANY,(uint8_t)-1,any},
		// 0x030E
		{"OraPLSQLStringBindTyp",ANY,(uint8_t)-1,any},
		// 0x030F
		{"SqlOraPLSQLPrepare",ANY,(uint8_t)-1,any},
		// 0x0310
		{"SqlOraPLSQLExecute",ANY,(uint8_t)-1,any},
		// 0x0311
		{"SqlOraPLSQLStringBind",ANY,(uint8_t)-1,any},
		// 0x0312
		{"SalPicGetImage",ANY,(uint8_t)-1,any},
		// 0x0313
		{"SalPicSetImage",ANY,(uint8_t)-1,any},
		// 0x0314
		{"SqlCreateSession",ANY,(uint8_t)-1,any},
		// 0x0315
		{"SqlCreateStatement",ANY,(uint8_t)-1,any},
		// 0x0316
		{"SqlFreeSession",ANY,(uint8_t)-1,any},
		// 0x0317
		{"SqlGetSessionErrorInf",ANY,(uint8_t)-1,any},
		// 0x0318
		{"SqlGetSessionHandle",ANY,(uint8_t)-1,any},
		// 0x0319
		{"SqlGetSessionParamete",ANY,(uint8_t)-1,any},
		// 0x031A
		{"SqlRollbackSession",ANY,(uint8_t)-1,any},
		// 0x031B
		{"SqlSetSessionParamete",ANY,(uint8_t)-1,any},
		// 0x031C
		{"SqlCommitSession",ANY,(uint8_t)-1,any},
		// 0x031D
		{"SqlGetStatementErrorI",ANY,(uint8_t)-1,any},
		// 0x031E
		{"SqlGetCmdOrRowsetPtr",ANY,(uint8_t)-1,any},
		// 0x031F
		{"SqlGetDSOrSessionPtr",ANY,(uint8_t)-1,any},
		// 0x0320
		{"GetLastError",ANY,(uint8_t)-1,any},
		// 0x0321
		{"ActiveXTypeVariant",ANY,(uint8_t)-1,any},
		// 0x0322
		{"SalTypeVariant",ANY,(uint8_t)-1,any},
		// 0x0323
		{"AsActiveXVariant",ANY,(uint8_t)-1,any},
		// 0x0324
		{"SetBooleanVariant",ANY,(uint8_t)-1,any},
		// 0x0325
		{"SetNumberVariant",ANY,(uint8_t)-1,any},
		// 0x0326
		{"SetStringVariant",ANY,(uint8_t)-1,any},
		// 0x0327
		{"SetDateVariant",ANY,(uint8_t)-1,any},
		// 0x0328
		{"SetObject",ANY,(uint8_t)-1,any},
		// 0x0329
		{"GetBooleanVariant",ANY,(uint8_t)-1,any},
		// 0x032A
		{"GetNumberVariant",ANY,(uint8_t)-1,any},
		// 0x032B
		{"GetStringVariant",ANY,(uint8_t)-1,any},
		// 0x032C
		{"GetDateVariant",ANY,(uint8_t)-1,any},
		// 0x032D
		{"GetObjectVariant",ANY,(uint8_t)-1,any},
		// 0x032E
		{"MakeOptionalVariant",ANY,(uint8_t)-1,any},
		// 0x032F
		{"CoClassCreateObject",ANY,(uint8_t)-1,any},
		// 0x0330
		{"ObjectAttach",ANY,(uint8_t)-1,any},
		// 0x0331
		{"ObjectInvoke",ANY,(uint8_t)-1,any},
		// 0x0332
		{"ObjectPushBoolean",ANY,(uint8_t)-1,any},
		// 0x0333
		{"ObjectPushNumber",ANY,(uint8_t)-1,any},
		// 0x0334
		{"ObjectPushString",ANY,(uint8_t)-1,any},
		// 0x0335
		{"ObjectPushDate",ANY,(uint8_t)-1,any},
		// 0x0336
		{"ObjectPushObject",ANY,(uint8_t)-1,any},
		// 0x0337
		{"ObjectPushVariant",ANY,(uint8_t)-1,any},
		// 0x0338
		{"ObjectPushBooleanBy",ANY,(uint8_t)-1,any},
		// 0x0339
		{"ObjectPushNumberByR",ANY,(uint8_t)-1,any},
		// 0x033A
		{"ObjectPushStringByR",ANY,(uint8_t)-1,any},
		// 0x033B
		{"ObjectPushDateByRef",ANY,(uint8_t)-1,any},
		// 0x033C
		{"ObjectPushObjectByR",ANY,(uint8_t)-1,any},
		// 0x033D
		{"ObjectPushVariantBy",ANY,(uint8_t)-1,any},
		// 0x033E
		{"ObjectPopBoolean",ANY,(uint8_t)-1,any},
		// 0x033F
		{"ObjectPopNumber",ANY,(uint8_t)-1,any},
		// 0x0340
		{"ObjectPopString",ANY,(uint8_t)-1,any},
		// 0x0341
		{"ObjectPopDate",ANY,(uint8_t)-1,any},
		// 0x0342
		{"ObjectPopObject",ANY,(uint8_t)-1,any},
		// 0x0343
		{"ObjectPopVariant",ANY,(uint8_t)-1,any},
		// 0x0344
		{"ObjectFlushArgs",ANY,(uint8_t)-1,any},
		// 0x0345
		{"ObjectCreateObject",ANY,(uint8_t)-1,any},
		// 0x0346
		{"ObjectCreateObjectE",ANY,(uint8_t)-1,any},
		// 0x0347
		{"SafeArrayPutBoolean",ANY,(uint8_t)-1,any},
		// 0x0348
		{"GetSafeArrayVariant",ANY,(uint8_t)-1,any},
		// 0x0349
		{"SetSafeArray",ANY,(uint8_t)-1,any},
		// 0x034A
		{"ObjectPushSafeArray",ANY,(uint8_t)-1,any},
		// 0x034B
		{"ObjectPushSafeArray",ANY,(uint8_t)-1,any},
		// 0x034C
		{"ObjectPopSafeArray",ANY,(uint8_t)-1,any},
		// 0x034D
		{"SafeArrayGetBoolean",ANY,(uint8_t)-1,any},
		// 0x034E
		{"SalMTSGetObjectContex",ANY,(uint8_t)-1,any},
		// 0x034F
		{"ObjectDetach",ANY,(uint8_t)-1,any},
		// 0x0350
		{"SalMTSCreateInstance",ANY,(uint8_t)-1,any},
		// 0x0351
		{"SalMTSSetComplete",ANY,(uint8_t)-1,any},
		// 0x0352
		{"SalMTSSetAbort",ANY,(uint8_t)-1,any},
		// 0x0353
		{"SalMTSEnableCommit",ANY,(uint8_t)-1,any},
		// 0x0354
		{"SalMTSDisableCommit",ANY,(uint8_t)-1,any},
		// 0x0355
		{"SalMTSIsInTransaction",ANY,(uint8_t)-1,any},
		// 0x0356
		{"SalMTSIsSecurityEnabl",ANY,(uint8_t)-1,any},
		// 0x0357
		{"SalMTSIsCallerInRole",ANY,(uint8_t)-1,any},
		// 0x0358
		{"EnumNext",ANY,(uint8_t)-1,any},
		// 0x0359
		{"EnumSkip",ANY,(uint8_t)-1,any},
		// 0x035A
		{"EnumReset",ANY,(uint8_t)-1,any},
		// 0x035B
		{"EnumIsCollection",ANY,(uint8_t)-1,any},
		// 0x035C
		{"EnumCount",ANY,(uint8_t)-1,any},
		// 0x035D
		{"ObjectInvokeID",ANY,(uint8_t)-1,any},
		// 0x035E
		{"CoClassGetInterface",ANY,(uint8_t)-1,any},
		// 0x035F
		{"CoClassRelease",ANY,(uint8_t)-1,any},
		// 0x0360
		{"SalObjGetType",ANY,(uint8_t)-1,any},
		// 0x0361
		{"SalObjIsNull",ANY,(uint8_t)-1,any},
		// 0x0362
		{"SalObjCreateFromStrin",ANY,(uint8_t)-1,any},
		// 0x0363
		{"SalObjIsValidClassNam",ANY,(uint8_t)-1,any},
		// 0x0364
		{"SalObjIsDerived",ANY,(uint8_t)-1,any},
		// 0x0365
		{"NULL",ANY,(uint8_t)-1,any},
		// 0x0366
		{"SalActiveXAutoErrorMo",ANY,(uint8_t)-1,any},
		// 0x0367
		{"SalActiveXCreate",ANY,(uint8_t)-1,any},
		// 0x0368
		{"SalActiveXGetActiveOb",ANY,(uint8_t)-1,any},
		// 0x0369
		{"SalActiveXGetObject",ANY,(uint8_t)-1,any},
		// 0x036A
		{"SalActiveXDoVerb",ANY,(uint8_t)-1,any},
		// 0x036B
		{"SalActiveXClose",ANY,(uint8_t)-1,any},
		// 0x036C
		{"SalActiveXInsertObjec",ANY,(uint8_t)-1,any},
		// 0x036D
		{"SalActiveXOLEType",ANY,(uint8_t)-1,any},
		// 0x036E
		{"SalActiveXGetData",ANY,(uint8_t)-1,any},
		// 0x036F
		{"SalActiveXCreateFromD",ANY,(uint8_t)-1,any},
		// 0x0370
		{"SalActiveXDelete",ANY,(uint8_t)-1,any},
		// 0x0371
		{"SalActiveXCreateFromF",ANY,(uint8_t)-1,any},
		// 0x0372
		{"CoClassCreateObject",ANY,(uint8_t)-1,any},
		// 0x0373
		{"SafeArrayCreateMD",ANY,(uint8_t)-1,any},
		// 0x0374
		{"SafeArrayGetLowerBo",ANY,(uint8_t)-1,any},
		// 0x0375
		{"SafeArrayGetUpperBo",ANY,(uint8_t)-1,any},
		// 0x0376
		{"SafeArrayGetNumberM",ANY,(uint8_t)-1,any},
		// 0x0377
		{"SafeArrayPutNumberM",ANY,(uint8_t)-1,any},
		// 0x0378
		{"SafeArrayGetDateMD",ANY,(uint8_t)-1,any},
		// 0x0379
		{"SafeArrayPutDateMD",ANY,(uint8_t)-1,any},
		// 0x037A
		{"SafeArrayGetObjectM",ANY,(uint8_t)-1,any},
		// 0x037B
		{"SafeArrayPutObjectM",ANY,(uint8_t)-1,any},
		// 0x037C
		{"SafeArrayGetStringM",ANY,(uint8_t)-1,any},
		// 0x037D
		{"SafeArrayPutStringM",ANY,(uint8_t)-1,any},
		// 0x037E
		{"SafeArrayGetVariant",ANY,(uint8_t)-1,any},
		// 0x037F
		{"SafeArrayPutVariant",ANY,(uint8_t)-1,any},
		// 0x0380
		{"SalSetErrorInfo",ANY,(uint8_t)-1,any},
		// 0x0381
		{"SqlPrepareSP",ANY,(uint8_t)-1,any},
		// 0x0382
		{"SqlGetNextSPResultSet",ANY,(uint8_t)-1,any},
		// 0x0383
		{"SqlCloseAllSPResultSe",ANY,(uint8_t)-1,any},
		// 0x0384
		{"SalWindowGetDockSetti",ANY,(uint8_t)-1,any},
		// 0x0385
		{"SalDlgGetDockStatus",ANY,(uint8_t)-1,any},
		// 0x0386
		{"SalDlgSetDockStatus",ANY,(uint8_t)-1,any},
		// 0x0387
		{"SalActiveXGetProgID",ANY,(uint8_t)-1,any},
		// 0x0388
		{"SalActiveXGetFileName",ANY,(uint8_t)-1,any},
		// 0x0389
		{"SalUseEventLog",ANY,(uint8_t)-1,any},
		// 0x038A
		{"SalStartTrace",ANY,(uint8_t)-1,any},
		// 0x038B
		{"SalTrace",ANY,(uint8_t)-1,any},
		// 0x038C
		{"SalEndTrace",ANY,(uint8_t)-1,any},
		// 0x038D
		{"SalComCleanupMode",ANY,(uint8_t)-1,any},
		// 0x038E
		{"SalTblWriteXMLandSche",ANY,(uint8_t)-1,any},
		// 0x038F
		{"SalTblSetColumnXMLAtt",ANY,(uint8_t)-1,any},
		// 0x0390
		{"SalTblCreateColumnEx",ANY,(uint8_t)-1,any},
		// 0x0391
		{"SalTblPopulateFromXML",ANY,(uint8_t)-1,any},
		// 0x0392
		{"SalTblWriteXMLandSche",ANY,(uint8_t)-1,any},
		// 0x0393
		{"SalTblSetFromXMLSchem",ANY,(uint8_t)-1,any},
		// 0x0394
		{"SalReportGetFileInfo",ANY,(uint8_t)-1,any},
		// 0x0395
		{"SqlGetCommandText",ANY,(uint8_t)-1,any},
		// 0x0396
		{"SalReportResetPages",ANY,(uint8_t)-1,any},
		// 0x0397
		{"XML_Document_LoadFr",ANY,(uint8_t)-1,any},
		// 0x0398
		{"XML_Document_LoadFr",ANY,(uint8_t)-1,any},
		// 0x0399
		{"XML_Node_nodeName",ANY,(uint8_t)-1,any},
		// 0x039A
		{"XML_Node_appendChil",ANY,(uint8_t)-1,any},
		// 0x039B
		{"XML_Node_cloneNode",ANY,(uint8_t)-1,any},
		// 0x039C
		{"XML_Node_firstChild",ANY,(uint8_t)-1,any},
		// 0x039D
		{"XML_Node_hasChildNo",ANY,(uint8_t)-1,any},
		// 0x039E
		{"XML_Node_insertBefo",ANY,(uint8_t)-1,any},
		// 0x039F
		{"XML_Node_lastChild",ANY,(uint8_t)-1,any},
		// 0x03A0
		{"XML_Node_nextSiblin",ANY,(uint8_t)-1,any},
		// 0x03A1
		{"XML_Node_nodeType",ANY,(uint8_t)-1,any},
		// 0x03A2
		{"XML_Node_nodeValue",ANY,(uint8_t)-1,any},
		// 0x03A3
		{"XML_Node_ownerDocum",ANY,(uint8_t)-1,any},
		// 0x03A4
		{"XML_Node_parentNode",ANY,(uint8_t)-1,any},
		// 0x03A5
		{"XML_Node_previousSi",ANY,(uint8_t)-1,any},
		// 0x03A6
		{"XML_Node_removeChil",ANY,(uint8_t)-1,any},
		// 0x03A7
		{"XML_Node_replaceChi",ANY,(uint8_t)-1,any},
		// 0x03A8
		{"XML_Node_childNodes",ANY,(uint8_t)-1,any},
		// 0x03A9
		{"XML_Node_attributes",ANY,(uint8_t)-1,any},
		// 0x03AA
		{"XML_Element_getAttr",ANY,(uint8_t)-1,any},
		// 0x03AB
		{"XML_Element_getAttr",ANY,(uint8_t)-1,any},
		// 0x03AC
		{"XML_Element_getElem",ANY,(uint8_t)-1,any},
		// 0x03AD
		{"XML_Element_removeA",ANY,(uint8_t)-1,any},
		// 0x03AE
		{"XML_Element_setAttr",ANY,(uint8_t)-1,any},
		// 0x03AF
		{"XML_Element_removeA",ANY,(uint8_t)-1,any},
		// 0x03B0
		{"XML_Element_setAttr",ANY,(uint8_t)-1,any},
		// 0x03B1
		{"XML_Document_create",ANY,(uint8_t)-1,any},
		// 0x03B2
		{"XML_Document_create",ANY,(uint8_t)-1,any},
		// 0x03B3
		{"XML_Document_create",ANY,(uint8_t)-1,any},
		// 0x03B4
		{"XML_Document_create",ANY,(uint8_t)-1,any},
		// 0x03B5
		{"XML_Document_create",ANY,(uint8_t)-1,any},
		// 0x03B6
		{"XML_Document_create",ANY,(uint8_t)-1,any},
		// 0x03B7
		{"XML_Document_create",ANY,(uint8_t)-1,any},
		// 0x03B8
		{"XML_Document_create",ANY,(uint8_t)-1,any},
		// 0x03B9
		{"XML_Document_docume",ANY,(uint8_t)-1,any},
		// 0x03BA
		{"XML_Document_docume",ANY,(uint8_t)-1,any},
		// 0x03BB
		{"XML_Document_setOut",ANY,(uint8_t)-1,any},
		// 0x03BC
		{"XML_Document_setFea",ANY,(uint8_t)-1,any},
		// 0x03BD
		{"XML_Node_changeType",ANY,(uint8_t)-1,any},
		// 0x03BE
		{"XML_CDATA_getCDATAb",ANY,(uint8_t)-1,any},
		// 0x03BF
		{"XML_CDATA_setCDATAb",ANY,(uint8_t)-1,any},
		// 0x03C0
		{"XML_Node_writeToStr",ANY,(uint8_t)-1,any},
		// 0x03C1
		{"XML_Document_writeT",ANY,(uint8_t)-1,any},
		// 0x03C2
		{"XML_CharacterData_s",ANY,(uint8_t)-1,any},
		// 0x03C3
		{"XML_CharacterData_g",ANY,(uint8_t)-1,any},
		// 0x03C4
		{"XML_CharacterData_s",ANY,(uint8_t)-1,any},
		// 0x03C5
		{"XML_CharacterData_a",ANY,(uint8_t)-1,any},
		// 0x03C6
		{"XML_CharacterData_i",ANY,(uint8_t)-1,any},
		// 0x03C7
		{"XML_CharacterData_d",ANY,(uint8_t)-1,any},
		// 0x03C8
		{"XML_CharacterData_r",ANY,(uint8_t)-1,any},
		// 0x03C9
		{"XML_Entity_getPubli",ANY,(uint8_t)-1,any},
		// 0x03CA
		{"XML_Entity_getSyste",ANY,(uint8_t)-1,any},
		// 0x03CB
		{"XML_Entity_getNotat",ANY,(uint8_t)-1,any},
		// 0x03CC
		{"XML_DocumentType_ge",ANY,(uint8_t)-1,any},
		// 0x03CD
		{"XML_DocumentType_ge",ANY,(uint8_t)-1,any},
		// 0x03CE
		{"XML_DocumentType_ge",ANY,(uint8_t)-1,any},
		// 0x03CF
		{"XML_Attr_getOwnerEl",ANY,(uint8_t)-1,any},
		// 0x03D0
		{"XML_Attr_getSpecifi",ANY,(uint8_t)-1,any},
		// 0x03D1
		{"XML_ProcessingInstr",ANY,(uint8_t)-1,any},
		// 0x03D2
		{"XML_CharacterData_g",ANY,(uint8_t)-1,any},
		// 0x03D3
		{"XML_CDATA_getCDATAb",ANY,(uint8_t)-1,any},
		// 0x03D4
		{"XML_Text_isIgnorabl",ANY,(uint8_t)-1,any},
		// 0x03D5
		{"XML_Text_splitText",ANY,(uint8_t)-1,any},
		// 0x03D6
		{"XML_Document_getEle",ANY,(uint8_t)-1,any},
		// 0x03D7
		{"XML_Document_create",ANY,(uint8_t)-1,any},
		// 0x03D8
		{"XML_Node_setNodeVal",ANY,(uint8_t)-1,any},
		// 0x03D9
		{"XML_Document_getEnc",ANY,(uint8_t)-1,any},
		// 0x03DA
		{"XML_Document_create",ANY,(uint8_t)-1,any},
		// 0x03DB
		{"XML_Document_releas",ANY,(uint8_t)-1,any},
		// 0x03DC
		{"XML_Document_getLas",ANY,(uint8_t)-1,any},
		// 0x03DD
		{"XML_Document_getURI",ANY,(uint8_t)-1,any},
		// 0x03DE
		{"XML_Document_getFea",ANY,(uint8_t)-1,any},
		// 0x03DF
		{"XML_Element_getTagN",ANY,(uint8_t)-1,any},
		// 0x03E0
		{"XML_Document_schema",ANY,(uint8_t)-1,any},
		// 0x03E1
		{"XML_Document_schema",ANY,(uint8_t)-1,any},
		// 0x03E2
		{"XML_Node_getTextCon",ANY,(uint8_t)-1,any},
		// 0x03E3
		{"XML_Node_setTextCon",ANY,(uint8_t)-1,any},
		// 0x03E4
		{"XML_Node_getLocalNa",ANY,(uint8_t)-1,any},
		// 0x03E5
		{"XML_Node_getPrefix",ANY,(uint8_t)-1,any},
		// 0x03E6
		{"XML_Node_getNamespa",ANY,(uint8_t)-1,any},
		// 0x03E7
		{"XML_Node_isDefaultN",ANY,(uint8_t)-1,any},
		// 0x03E8
		{"XML_Node_SqlSelectF",ANY,(uint8_t)-1,any},
		// 0x03E9
		{"XML_Node_SqlSchemaF",ANY,(uint8_t)-1,any},
		// 0x03EA
		{"XML_Node_hasAttribu",ANY,(uint8_t)-1,any},
		// 0x03EB
		{"SalReportSetPrinterTr",ANY,(uint8_t)-1,any},
		// 0x03EC
		{"SalReportSetPrinterSe",ANY,(uint8_t)-1,any},
		// 0x03ED
		{"SalReportGetPrinterSe",ANY,(uint8_t)-1,any},
		// 0x03EE
		{"SalEventLogSetName",ANY,(uint8_t)-1,any},
		// 0x03EF
		{"SalReportGetPrinterTr",ANY,(uint8_t)-1,any},
		// 0x03F0
		{"SalXMLGetLastError",ANY,(uint8_t)-1,any},
		// 0x03F1
		{"SalXMLSerializeUDV",ANY,(uint8_t)-1,any},
		// 0x03F2
		{"SalXMLDeserializeUDV",ANY,(uint8_t)-1,any},
		// 0x03F3
		{"XML_Node_release",ANY,(uint8_t)-1,any},
		// 0x03F4
		{"XML_Element_hasAttr",ANY,(uint8_t)-1,any},
		// 0x03F5
		{"HTTP_Send",ANY,(uint8_t)-1,any},
		// 0x03F6
		{"HTTP_SetHTTPHeader",ANY,(uint8_t)-1,any},
		// 0x03F7
		{"HTTP_GetResponseTex",ANY,(uint8_t)-1,any},
		// 0x03F8
		{"HTTP_GetResponseXML",ANY,(uint8_t)-1,any},
		// 0x03F9
		{"HTTP_GetResponseHea",ANY,(uint8_t)-1,any},
		// 0x03FA
		{"HTTP_GetAllResponse",ANY,(uint8_t)-1,any},
		// 0x03FB
		{"HTTP_Open",ANY,(uint8_t)-1,any},
		// 0x03FC
		{"HTTP_SendXML",ANY,(uint8_t)-1,any},
		// 0x03FD
		{"HTTP_GetLastError",ANY,(uint8_t)-1,any},
		// 0x03FE
		{"HTTP_SetTimeOut",ANY,(uint8_t)-1,any},
		// 0x03FF
		{"SqlCloseResultSet",ANY,(uint8_t)-1,any},
		// 0x0400
		{"SalThemeSet",ANY,(uint8_t)-1,any},
		// 0x0401
		{"SalThemeGet",ANY,(uint8_t)-1,any},
		// 0x0402
		{"SalSetDateTime",ANY,(uint8_t)-1,any},
		// 0x0403
		{"SalGetDateTime",ANY,(uint8_t)-1,any},
		// 0x0404
		{"SalStrToMultiByte",ANY,(uint8_t)-1,any},
		// 0x0405
		{"SalStrToWideChar",ANY,(uint8_t)-1,any},
		// 0x0406
		{"SalOutlineItemSetProp",ANY,(uint8_t)-1,any},
		// 0x0407
		{"SalTabHidePage",ANY,(uint8_t)-1,any},
		// 0x0408
		{"SalTabShowPage",ANY,(uint8_t)-1,any},
		// 0x0409
		{"SalWindowSetPropertyB",ANY,(uint8_t)-1,any},
		// 0x040A
		{"SalGetMenu",ANY,(uint8_t)-1,any},
		// 0x040B
		{"SalMenuUpdate",ANY,(uint8_t)-1,any},
		// 0x040C
		{"SalSetBufferLength",ANY,(uint8_t)-1,any},
		// 0x040D
		{"SalGetBufferLength",ANY,(uint8_t)-1,any},
		// 0x040E
		{"SalGridSetCellType",ANY,(uint8_t)-1,any},
		// 0x040F
		{"SalGridSetCellProp",ANY,(uint8_t)-1,any},
		// 0x0410
		{"SalOutlineLoadSuppres",ANY,(uint8_t)-1,any},
		// 0x0411
		{"SalPicSetBinary",ANY,(uint8_t)-1,any},
		// 0x0412
		{"SalPicGetBinary",ANY,(uint8_t)-1,any},
		// 0x0413
		{"SalHBinaryToNumber",ANY,(uint8_t)-1,any},
		// 0x0414
		{"SalNumberToHBinary",ANY,(uint8_t)-1,any},
		// 0x0415
		{"SalTabPageCount",ANY,(uint8_t)-1,any},
		// 0x0416
		{"SalTabAddPage",ANY,(uint8_t)-1,any},
		// 0x0417
		{"SalTabRenamePage",ANY,(uint8_t)-1,any},
		// 0x0418
		{"SalTabRemovePage",ANY,(uint8_t)-1,any},
		// 0x0419
		{"SalTabAssociateChild",ANY,(uint8_t)-1,any},
		// 0x041A
		{"SalTabDisassociateChi",ANY,(uint8_t)-1,any},
		// 0x041B
		{"SalTabSetActivePage",ANY,(uint8_t)-1,any},
		// 0x041C
		{"SalTabEnablePage",ANY,(uint8_t)-1,any},
		// 0x041D
		{"SalTabDisablePage",ANY,(uint8_t)-1,any},
		// 0x041E
		{"SalTabGetPageTitle",ANY,(uint8_t)-1,any},
		// 0x041F
		{"SalTabGetPageIndex",ANY,(uint8_t)-1,any},
		// 0x0420
		{"SalGridPrintPreview",ANY,(uint8_t)-1,any},
		// 0x0421
		{"SalGridPrint",ANY,(uint8_t)-1,any},
		// 0x0422
		{"SalRTFTextCopy",ANY,(uint8_t)-1,any},
		// 0x0423
		{"SalRTFTextPaste",ANY,(uint8_t)-1,any},
		// 0x0424
		{"SalRTFTextFind",ANY,(uint8_t)-1,any},
		// 0x0425
		{"SalRTFTextFindNext",ANY,(uint8_t)-1,any},
		// 0x0426
		{"SalRTFTextGetAlignmen",ANY,(uint8_t)-1,any},
		// 0x0427
		{"SalRTFTextGetSpacing",ANY,(uint8_t)-1,any},
		// 0x0428
		{"SalRTFTextGetColor",ANY,(uint8_t)-1,any},
		// 0x0429
		{"SalRTFTextSetColor",ANY,(uint8_t)-1,any},
		// 0x042A
		{"SalRTFTextGetStyle",ANY,(uint8_t)-1,any},
		// 0x042B
		{"SalRTFTextSetStyle",ANY,(uint8_t)-1,any},
		// 0x042C
		{"SalRTFTextGetSelected",ANY,(uint8_t)-1,any},
		// 0x042D
		{"SalRTFTextSelect",ANY,(uint8_t)-1,any},
		// 0x042E
		{"SalRTFTextSelectAll",ANY,(uint8_t)-1,any},
		// 0x042F
		{"SalRTFTextReplace",ANY,(uint8_t)-1,any},
		// 0x0430
		{"SalRTFParagraphSetAli",ANY,(uint8_t)-1,any},
		// 0x0431
		{"SalRTFParagraphGetSet",ANY,(uint8_t)-1,any},
		// 0x0432
		{"SalRTFParagraphSetSet",ANY,(uint8_t)-1,any},
		// 0x0433
		{"SalRTFParagraphSetSpa",ANY,(uint8_t)-1,any},
		// 0x0434
		{"SalRTFDocumentInsert",ANY,(uint8_t)-1,any},
		// 0x0435
		{"SalRTFDocumentLineCou",ANY,(uint8_t)-1,any},
		// 0x0436
		{"SalRTFDocumentLineLen",ANY,(uint8_t)-1,any},
		// 0x0437
		{"SalRTFDocumentPageCou",ANY,(uint8_t)-1,any},
		// 0x0438
		{"SalRTFDocumentGetPosi",ANY,(uint8_t)-1,any},
		// 0x0439
		{"SalGridGetColumnType",ANY,(uint8_t)-1,any},
		// 0x043A
		{"SalRTFDocumentPicture",ANY,(uint8_t)-1,any},
		// 0x043B
		{"SalRTFDocumentPreview",ANY,(uint8_t)-1,any},
		// 0x043C
		{"SalRTFDocumentPrint",ANY,(uint8_t)-1,any},
		// 0x043D
		{"SalRTFDocumentSave",ANY,(uint8_t)-1,any},
		// 0x043E
		{"SalRTFCtrlIsPreview",ANY,(uint8_t)-1,any},
		// 0x043F
		{"SalReportPrintToFileE",ANY,(uint8_t)-1,any},
		// 0x0440
		{"SalPrtGetPrinterTrays",ANY,(uint8_t)-1,any},
		// 0x0441
		{"SalGridGetCellProp",ANY,(uint8_t)-1,any},
		// 0x0442
		{"SalGridGetCellType",ANY,(uint8_t)-1,any},
		// 0x0443
		{"SalGridSetColumnType",ANY,(uint8_t)-1,any},
		// 0x0444
		{"SqlSetDSOrSessionPtr",ANY,(uint8_t)-1,any},
		// 0x0445
		{"SalGetTypeEx",ANY,(uint8_t)-1,any},
		// 0x0446
		{"SalTabGetActivePage",ANY,(uint8_t)-1,any},
		// 0x0447
		{"SalSetActiveRibbonPag",ANY,(uint8_t)-1,any},
		// 0x0448
		{"SalTabUpdate",ANY,(uint8_t)-1,any},
		// 0x0449
		{"SalCharToMultiByte",ANY,(uint8_t)-1,any},
		// 0x044A
		{"SalCharToWideChar",ANY,(uint8_t)-1,any},
		// 0x044B
		{"SalGridSetCellPicture",ANY,(uint8_t)-1,any},
		// 0x044C
		{"SalHtmlHelp",ANY,(uint8_t)-1,any},
		// 0x044D
		{"SalBtnSetProperties",ANY,(uint8_t)-1,any},
		// 0x044E
		{"SalBtnSetImageAlign",ANY,(uint8_t)-1,any},
		// 0x044F
		{"SalBtnSetTextAlign",ANY,(uint8_t)-1,any},
		// 0x0450
		{"SalBtnSetTextImageRel",ANY,(uint8_t)-1,any},
		// 0x0451
		{"SalBtnGetProperties",ANY,(uint8_t)-1,any},
		// 0x0452
		{"SalBtnGetImageAlign",ANY,(uint8_t)-1,any},
		// 0x0453
		{"SalBtnGetTextAlign",ANY,(uint8_t)-1,any},
		// 0x0454
		{"SalBtnGetTextImageRel",ANY,(uint8_t)-1,any},
		// 0x0455
		{"SalReportGetRichTextV",ANY,(uint8_t)-1,any},
		// 0x0456
		{"SalReportSetRichTextV",ANY,(uint8_t)-1,any},
		// 0x0457
		{"SalOutlineSaveConvert",ANY,(uint8_t)-1,any},
		// 0x0458
		{"SalRTFTableInsert",ANY,(uint8_t)-1,any},
		// 0x0459
		{"SalGridSortRowsMultiC",ANY,(uint8_t)-1,any},
		// 0x045A
		{"SqlWriteConnectionStr",ANY,(uint8_t)-1,any},
		// 0x045B
		{"SqlGetConnectionStrin",ANY,(uint8_t)-1,any},
		// 0x045C
		{"SqlDeleteConnectionSt",ANY,(uint8_t)-1,any},
		// 0x045D
		{"SqlListConnections",ANY,(uint8_t)-1,any},
		// 0x045E
		{"SqlFindIniFile",ANY,(uint8_t)-1,any},
		// 0x045F
		{"SalSetTooltip",ANY,(uint8_t)-1,any},
		// 0x0460
		{"SalGetTooltip",ANY,(uint8_t)-1,any},
		// 0x0461
		{"SalGetActiveRibbonPag",ANY,(uint8_t)-1,any},
		// 0x0462
		{"SalFileOpenCP",ANY,(uint8_t)-1,any},
		// 0x0463
		{"SalDlgSetDockSlide",ANY,(uint8_t)-1,any},
		// 0x0464
		{"SalDlgGetDockSlide",ANY,(uint8_t)-1,any},
		// 0x0465
		{"SalWindowWriteDockSta",ANY,(uint8_t)-1,any},
		// 0x0466
		{"SalWindowApplyDockSta",ANY,(uint8_t)-1,any},
		// 0x0467
		{"SalDlgSetDockStatusEx",ANY,(uint8_t)-1,any},
		// 0x0468
		{"SalRTFTextSetFont",ANY,(uint8_t)-1,any},
		// 0x0469
		{"SalRTFShowToolBar",ANY,(uint8_t)-1,any},
		// 0x046A
		{"SalRTFShowToolBarButt",ANY,(uint8_t)-1,any},
		// 0x046B
		{"SalDlgSetDockTabAt",ANY,(uint8_t)-1,any},
		// 0x046C
		{"SalTblCreateColumnFro",ANY,(uint8_t)-1,any},
		// 0x046D
		{"SalTreeInsertItem",ANY,(uint8_t)-1,any},
		// 0x046E
		{"SalTreeSetSelectedIte",ANY,(uint8_t)-1,any},
		// 0x046F
		{"SalTreeExpandItem",ANY,(uint8_t)-1,any},
		// 0x0470
		{"SalTreeCollapseItem",ANY,(uint8_t)-1,any},
		// 0x0471
		{"SalTreeEditItem",ANY,(uint8_t)-1,any},
		// 0x0472
		{"SalTreeSetItemEditabl",ANY,(uint8_t)-1,any},
		// 0x0473
		{"SalTreeDeleteItem",ANY,(uint8_t)-1,any},
		// 0x0474
		{"SalTreeItemCount",ANY,(uint8_t)-1,any},
		// 0x0475
		{"SalTreeGetFirstItem",ANY,(uint8_t)-1,any},
		// 0x0476
		{"SalTreeGetNextItem",ANY,(uint8_t)-1,any},
		// 0x0477
		{"SalTreeGetPrevItem",ANY,(uint8_t)-1,any},
		// 0x0478
		{"SalTreeGetItemText",ANY,(uint8_t)-1,any},
		// 0x0479
		{"SalTreeGetSelectedIte",ANY,(uint8_t)-1,any},
		// 0x047A
		{"SalTreeFindItemByTitl",ANY,(uint8_t)-1,any},
		// 0x047B
		{"SalTreeGetItemParent",ANY,(uint8_t)-1,any},
		// 0x047C
		{"SalTreeItemIsExpanded",ANY,(uint8_t)-1,any},
		// 0x047D
		{"SalTreeItemIsSelected",ANY,(uint8_t)-1,any},
		// 0x047E
		{"SalTreeSetItemImage",ANY,(uint8_t)-1,any},
		// 0x047F
		{"SalTreeGetItemTooltip",ANY,(uint8_t)-1,any},
		// 0x0480
		{"SalTreeSetItemTooltip",ANY,(uint8_t)-1,any},
		// 0x0481
		{"SalTreeGetItemData",ANY,(uint8_t)-1,any},
		// 0x0482
		{"SalTreeSetItemData",ANY,(uint8_t)-1,any},
		// 0x0483
		{"SalTreeGetDropItem",ANY,(uint8_t)-1,any},
		// 0x0484
		{"SalTreeSetItemTextCol",ANY,(uint8_t)-1,any},
		// 0x0485
		{"SalTreeSetItemFontEnh",ANY,(uint8_t)-1,any},
		// 0x0486
		{"SalTreeEnableItem",ANY,(uint8_t)-1,any},
		// 0x0487
		{"SalTreeSetItemChecked",ANY,(uint8_t)-1,any},
		// 0x0488
		{"SalTreeItemIsChecked",ANY,(uint8_t)-1,any},
		// 0x0489
		{"SalTreeItemHasCheckbo",ANY,(uint8_t)-1,any},
		// 0x048A
		{"SalTreeShowItemCheckb",ANY,(uint8_t)-1,any},
		// 0x048B
		{"SalTreeSetItemText",ANY,(uint8_t)-1,any},
		// 0x048C
		{"SalNavPaneIsEnabled",ANY,(uint8_t)-1,any},
		// 0x048D
		{"SalNavEnablePane",ANY,(uint8_t)-1,any},
		// 0x048E
		{"SalNavGetPaneTitle",ANY,(uint8_t)-1,any},
		// 0x048F
		{"SalNavSetPaneTitle",ANY,(uint8_t)-1,any},
		// 0x0490
		{"SalNavGetPaneIndex",ANY,(uint8_t)-1,any},
		// 0x0491
		{"SalNavAddPane",ANY,(uint8_t)-1,any},
		// 0x0492
		{"SalNavRemovePane",ANY,(uint8_t)-1,any},
		// 0x0493
		{"SalNavGetActivePane",ANY,(uint8_t)-1,any},
		// 0x0494
		{"SalNavSetActivePane",ANY,(uint8_t)-1,any},
		// 0x0495
		{"SalNavLoadState",ANY,(uint8_t)-1,any},
		// 0x0496
		{"SalNavResetState",ANY,(uint8_t)-1,any},
		// 0x0497
		{"SalNavSaveState",ANY,(uint8_t)-1,any},
		// 0x0498
		{"SalNavAssociateChild",ANY,(uint8_t)-1,any},
		// 0x0499
		{"SalNavDisassociateChi",ANY,(uint8_t)-1,any},
		// 0x049A
		{"SalNavGroupIsExpanded",ANY,(uint8_t)-1,any},
		// 0x049B
		{"SalNavExpandGroup",ANY,(uint8_t)-1,any},
		// 0x049C
		{"SalGridDataExport",ANY,(uint8_t)-1,any},
		// 0x049D
		{"SalTabSetTooltip",ANY,(uint8_t)-1,any},
		// 0x049E
		{"SalTabGetTooltip",ANY,(uint8_t)-1,any},
		// 0x049F
		{"SalTabSetPageTitle",ANY,(uint8_t)-1,any},
		// 0x04A0
		{"SalTabHideStrip",ANY,(uint8_t)-1,any},
		// 0x04A1
		{"SalTabShowStrip",ANY,(uint8_t)-1,any},
		// 0x04A2
		{"SalTabAttachWindow",ANY,(uint8_t)-1,any},
		// 0x04A3
		{"SalTabDetachWindow",ANY,(uint8_t)-1,any},
		// 0x04A4
		{"SalTabGetPageWindow",ANY,(uint8_t)-1,any},
		// 0x04A5
		{"SalGridGetHeader",ANY,(uint8_t)-1,any},
		// 0x04A6
		{"SalGridGetFooter",ANY,(uint8_t)-1,any},
		// 0x04A7
		{"SalGridSetHeader",ANY,(uint8_t)-1,any},
		// 0x04A8
		{"SalGridSetFooter",ANY,(uint8_t)-1,any},
		// 0x04A9
		{"SalCreateToolbar",ANY,(uint8_t)-1,any},
		// 0x04AA
		{"SalGridDataImport",ANY,(uint8_t)-1,any},
		// 0x04AB
		{"SalWPFInvokeMethod",ANY,(uint8_t)-1,any},
		// 0x04AC
		{"SalWPFGetBoolProperty",ANY,(uint8_t)-1,any},
		// 0x04AD
		{"SalWPFSetBoolProperty",ANY,(uint8_t)-1,any},
		// 0x04AE
		{"SalWPFGetDateProperty",ANY,(uint8_t)-1,any},
		// 0x04AF
		{"SalWPFSetDateProperty",ANY,(uint8_t)-1,any},
		// 0x04B0
		{"SalWPFGetNumericPrope",ANY,(uint8_t)-1,any},
		// 0x04B1
		{"SalWPFSetNumericPrope",ANY,(uint8_t)-1,any},
		// 0x04B2
		{"SalWPFGetStrProperty",ANY,(uint8_t)-1,any},
		// 0x04B3
		{"SalWPFSetStrProperty",ANY,(uint8_t)-1,any},
		// 0x04B4
		{"SalNavSetPaneIcon",ANY,(uint8_t)-1,any},
		// 0x04B5
		{"SalNavGetPaneIcon",ANY,(uint8_t)-1,any},
		// 0x04B6
		{"SalGridSetAltRowBackC",ANY,(uint8_t)-1,any},
		// 0x04B7
		{"SalNetCompileAndEvalu",ANY,(uint8_t)-1,any},
		// 0x04B8
		{"SalDateWeekNumber",ANY,(uint8_t)-1,any},
		// 0x04B9
		{"SalTreeReset",ANY,(uint8_t)-1,any},
		// 0x04BA
		{"SalTreeItemFromPoint",ANY,(uint8_t)-1,any},
		// 0x04BB
		{"SalIsDotNet",ANY,(uint8_t)-1,any},
		// 0x04BC
		{"SalNavAddGroup",ANY,(uint8_t)-1,any},
		// 0x04BD
		{"SalGridSummaryBar",ANY,(uint8_t)-1,any},
		// 0x04BE
		{"SalGridSetSummaryColu",ANY,(uint8_t)-1,any},
		// 0x04BF
		{"SalTblColumnMinMax",ANY,(uint8_t)-1,any},
		// 0x04C0
		{"SalTblColumnAverageDa",ANY,(uint8_t)-1,any},
		// 0x04C1
		{"SalTblColumnMinMaxDat",ANY,(uint8_t)-1,any},
		// 0x04C2
		{"SalGridSetSummaryColu",ANY,(uint8_t)-1,any},
		// 0x04C3
		{"SalNumberToCharASCII",ANY,(uint8_t)-1,any},
		// 0x04C4
		{"SalStrLopASCII",ANY,(uint8_t)-1,any},
		// 0x04C5
		{"SalStrFirstCASCII",ANY,(uint8_t)-1,any},
		// 0x04C6
		{"SalTblDefineRadioButt",ANY,(uint8_t)-1,any},
		// 0x04C7
		{"SalRibbonMaximize",ANY,(uint8_t)-1,any},
		// 0x04C8
		{"SalRibbonMinimize",ANY,(uint8_t)-1,any},
		// 0x04C9
		{"SalGridSetRowHeight",ANY,(uint8_t)-1,any},
		// 0x04CA
		{"SalTabGetPageName",ANY,(uint8_t)-1,any},
		// 0x04CB
		{"SalTabAddPageEx",ANY,(uint8_t)-1,any},
		// 0x04CC
		{"SalDictionaryPromote",ANY,(uint8_t)-1,any},
		// 0x04CD
		{"SalThrowSoapFault",ANY,(uint8_t)-1,any},
		// 0x04CE
		{"SalTreeSetItemImageFr",ANY,(uint8_t)-1,any},
		// 0x04CF
		{"SalNavAddPaneEx",ANY,(uint8_t)-1,any},
		// 0x04D0
		{"SalNavSetPaneIconFrom",ANY,(uint8_t)-1,any},
		// 0x04D1
		{"SalWSSetCredentials",ANY,(uint8_t)-1,any},
		// 0x04D2
		{"SalDictionaryLookupSt",ANY,(uint8_t)-1,any},
		// 0x04D3
		{"SqlConnectDotNet",ANY,(uint8_t)-1,any},
		// 0x04D4
		{"SalTblColumnCountNotN",ANY,(uint8_t)-1,any},
		// 0x04D5
		{"SalGridSummaryBarRefr",ANY,(uint8_t)-1,any},
		// 0x04D6
		{"SalTreeMoveDownItem",ANY,(uint8_t)-1,any},
		// 0x04D7
		{"SalTreeMoveUpItem",ANY,(uint8_t)-1,any},
		// 0x04D8
		{"SalTreePromoteItem",ANY,(uint8_t)-1,any},
		// 0x04D9
		{"SalTreeDemoteItem",ANY,(uint8_t)-1,any},
		// 0x04DA
		{"SalTreeDragDropItem",ANY,(uint8_t)-1,any},
		// 0x04DB
		{"SalSetLanguageID",ANY,(uint8_t)-1,any},
		// 0x04DC
		{"SalGridSetSummaryColu",ANY,(uint8_t)-1,any},
		// 0x04DD
		{"SalGridDataExportEx",ANY,(uint8_t)-1,any},
		// 0x04DE
		{"SalTBGetDockStatus",ANY,(uint8_t)-1,any},
		// 0x04DF
		{"SalTBSetDockStatus",ANY,(uint8_t)-1,any},
		// 0x04E0
		{"SalSetPaintMode",ANY,(uint8_t)-1,any},
		// 0x04E1
		{"SalGetLastException",ANY,(uint8_t)-1,any},
		// 0x04E2
		{"SalTreeFindItemByData",ANY,(uint8_t)-1,any},
		// 0x04E3
		{"SalActiveXSaveFile",ANY,(uint8_t)-1,any},
		// 0x04E4
		{"SalTreeMoveItem",ANY,(uint8_t)-1,any},
		// 0x04E5
		{"SalStringToBinary",ANY,(uint8_t)-1,any},
		// 0x04E6
		{"SalBinaryToString",ANY,(uint8_t)-1,any},
		// 0x04E7
		{"SalDateToUTCTime",ANY,(uint8_t)-1,any},
		// 0x04E8
		{"SalDateToLocalTime",ANY,(uint8_t)-1,any},
		// 0x04E9
		{"SalDictionaryLoad",ANY,(uint8_t)-1,any},
		// 0x04EA
		{"SalTblSetCellBackColo",ANY,(uint8_t)-1,any},
		// 0x04EB
		{"SalIsValidDateTimeExa",ANY,(uint8_t)-1,any},
		// 0x04EC
		{"SalPicPaintAsBkgd",ANY,(uint8_t)-1,any},
		// 0x04ED
		{"SalDlgOpenFileMulti",ANY,(uint8_t)-1,any},
		// 0x04EE
		{"SalTreeSetItemImageFr",ANY,(uint8_t)-1,any},
		// 0x04EF
		{"SalEnableFastChars",ANY,(uint8_t)-1,any},
		// 0x04F0
		{"SalGridWriteState",ANY,(uint8_t)-1,any},
		// 0x04F1
		{"SalGridApplyState",ANY,(uint8_t)-1,any},
		// 0x04F2
		{"SalRibbonGetState",ANY,(uint8_t)-1,any},
		// 0x04F3
		{"SalTabSetPageIcon",ANY,(uint8_t)-1,any},
		// 0x04F4
		{"SalMeterGetRange",ANY,(uint8_t)-1,any},
		// 0x04F5
		{"SalMeterSetRange",ANY,(uint8_t)-1,any},
		// 0x04F6
		{"SalMeterGetFromColor",ANY,(uint8_t)-1,any},
		// 0x04F7
		{"SalMeterSetFromColor",ANY,(uint8_t)-1,any},
		// 0x04F8
		{"SalMeterGetToColor",ANY,(uint8_t)-1,any},
		// 0x04F9
		{"SalMeterSetToColor",ANY,(uint8_t)-1,any},
		// 0x04FA
		{"SalMeterGetStepSize",ANY,(uint8_t)-1,any},
		// 0x04FB
		{"SalMeterSetStepSize",ANY,(uint8_t)-1,any},
		// 0x04FC
		{"SalMeterGetSmooth",ANY,(uint8_t)-1,any},
		// 0x04FD
		{"SalMeterSetSmooth",ANY,(uint8_t)-1,any},
		// 0x04FE
		{"SalMeterGetVertical",ANY,(uint8_t)-1,any},
		// 0x04FF
		{"SalMeterSetVertical",ANY,(uint8_t)-1,any},
		// 0x0500
		{"SalMeterStepUp",ANY,(uint8_t)-1,any},
		// 0x0501
		{"SalMeterStepDown",ANY,(uint8_t)-1,any},
		// 0x0502
		{"SqlDbPipeSetRequestHe",ANY,(uint8_t)-1,any},
		// 0x0503
		{"SqlDbPipeFetchRespons",ANY,(uint8_t)-1,any},
		// 0x0504
		{"SalTBEnableItem",ANY,(uint8_t)-1,any},
		// 0x0505
		{"SalTBDisableItem",ANY,(uint8_t)-1,any},
		// 0x0506
		{"SalTBSetItemText",ANY,(uint8_t)-1,any},
		// 0x0507
		{"SalTBSetItemTooltip",ANY,(uint8_t)-1,any},
		// 0x0508
		{"SalRibbonSetItemText",ANY,(uint8_t)-1,any},
		// 0x0509
		{"SalRibbonGetItemText",ANY,(uint8_t)-1,any},
		// 0x050A
		{"SalGetEnvironment",ANY,(uint8_t)-1,any},
		// 0x050B
		{"SalTBGetItemCount",ANY,(uint8_t)-1,any},
		// 0x050C
		{"SalTBSetItemColor",ANY,(uint8_t)-1,any},
		// 0x050D
		{"SalWSSetEndpointAddre",ANY,(uint8_t)-1,any},
		// 0x050E
		{"SalGetLastExceptionFi",ANY,(uint8_t)-1,any},
		// 0x050F
		{"SalRibbonSetItemCapti",ANY,(uint8_t)-1,any},
		// 0x0510
		{"SalRibbonGetItemCapti",ANY,(uint8_t)-1,any},
		// 0x0511
		{"SalRibbonSetItemEnabl",ANY,(uint8_t)-1,any},
		// 0x0512
		{"SalRibbonGetItemEnabl",ANY,(uint8_t)-1,any},
		// 0x0513
		{"SalRibbonSetItemCheck",ANY,(uint8_t)-1,any},
		// 0x0514
		{"SalRibbonGetItemCheck",ANY,(uint8_t)-1,any},
		// 0x0515
		{"SalRibbonClearList",ANY,(uint8_t)-1,any},
		// 0x0516
		{"SalRibbonAddListValue",ANY,(uint8_t)-1,any},
		// 0x0517
		{"SalTBAddItem",ANY,(uint8_t)-1,any},
		// 0x0518
		{"SalTabAddPageNoSelect",ANY,(uint8_t)-1,any},
		// 0x0519
		{"SalTBDeleteItem",ANY,(uint8_t)-1,any},
		// 0x051A
		{"SalTBHideItem",ANY,(uint8_t)-1,any},
		// 0x051B
		{"SalTBShowItem",ANY,(uint8_t)-1,any},
		// 0x051C
		{"SalOutlineItemTypeTex",ANY,(uint8_t)-1,any},
		// 0x051D
		{"SqlConnectDbPipe",ANY,(uint8_t)-1,any},
		// 0x051E
		{"SalListSetDropdownWid",ANY,(uint8_t)-1,any},
		// 0x051F
		{"SqlDbPipeGetErrorInfo",ANY,(uint8_t)-1,any},
		// 0x0520
		{"SalSetMenuColor",ANY,(uint8_t)-1,any},
		// 0x0521
		{"SalPMKVerify",ANY,(uint8_t)-1,any},
		// 0x0522
		{"SalRibbonAddItem",ANY,(uint8_t)-1,any},
		// 0x0523
		{"SalRibbonDeleteItem",ANY,(uint8_t)-1,any},
		// 0x0524
		{"SalRibbonSetItemVisib",ANY,(uint8_t)-1,any},
		// 0x0525
		{"SalRibbonSetItemSize",ANY,(uint8_t)-1,any},
		// 0x0526
		{"SalRibbonSetItemImage",ANY,(uint8_t)-1,any},
		// 0x0527
		{"SalRibbonPopulate",ANY,(uint8_t)-1,any},
		// 0x0528
		{"SalFieldSetSelect",ANY,(uint8_t)-1,any},
		// 0x0529
		{"SalCalShowWeeks",ANY,(uint8_t)-1,any},
		// 0x052A
		{"SalCalGetSelectedDate",ANY,(uint8_t)-1,any},
		// 0x052B
		{"SalCalMarkDays",ANY,(uint8_t)-1,any},
		// 0x052C
		{"SalGridGetSummaryColu",ANY,(uint8_t)-1,any},
		// 0x052D
		{"SalGridSetSummaryColu",ANY,(uint8_t)-1,any},
		// 0x052E
		{"SalGridGetSummaryColu",ANY,(uint8_t)-1,any},
		// 0x052F
		{"SalRibbonSetItemToolt",ANY,(uint8_t)-1,any},
		// 0x0530
		{"SalRibbonSetItemAccel",ANY,(uint8_t)-1,any},
		// 0x0531
		{"SalMenuSetText",ANY,(uint8_t)-1,any},
		// 0x0532
		{"SalMenuSetFont",ANY,(uint8_t)-1,any},
		// 0x0533
		{"SalMenuSetCheck",ANY,(uint8_t)-1,any},
		// 0x0534
		{"SalMenuSetEnabled",ANY,(uint8_t)-1,any},
		// 0x0535
		{"SalMenuGetText",ANY,(uint8_t)-1,any},
		// 0x0536
		{"SalMenuGetFontSetting",ANY,(uint8_t)-1,any},
		// 0x0537
		{"SalMenuGetCheck",ANY,(uint8_t)-1,any},
		// 0x0538
		{"SalMenuGetEnabled",ANY,(uint8_t)-1,any},
		// 0x0539
		{"SalMenuInsert",ANY,(uint8_t)-1,any},
		// 0x053A
		{"SalMenuInsertEx",ANY,(uint8_t)-1,any},
		// 0x053B
		{"SalMenuGetCount",ANY,(uint8_t)-1,any},
		// 0x053C
		{"SalMenuGetNameByPosit",ANY,(uint8_t)-1,any},
		// 0x053D
		{"SalMenuDelete",ANY,(uint8_t)-1,any},
		// 0x053E
		{"SalMenuGetItemName",ANY,(uint8_t)-1,any},
		// 0x053F
		{"SalMenuGetHandle",ANY,(uint8_t)-1,any},
		// 0x0540
		{"SalMenuGetMDIPersistM",ANY,(uint8_t)-1,any},
		// 0x0541
		{"SalMenuSetPicture",ANY,(uint8_t)-1,any},
		// 0x0542
		{"SalWebReportCreate",ANY,(uint8_t)-1,any},
		// 0x0543
		{"SalWebReportCreateToF",ANY,(uint8_t)-1,any},
		// 0x0544
		{"SalStatusCreateProgre",ANY,(uint8_t)-1,any},
		// 0x0545
		{"SalStatusSetPaneImage",ANY,(uint8_t)-1,any},
		// 0x0546
		{"SalStatusAddPane",ANY,(uint8_t)-1,any},
		// 0x0547
		{"SalStatusSetPaneText",ANY,(uint8_t)-1,any},
		// 0x0548
		{"SalStatusSetPaneVisib",ANY,(uint8_t)-1,any},
		// 0x0549
		{"SalStatusSetPaneToolt",ANY,(uint8_t)-1,any},
		// 0x054A
		{"SalBackgroundWorkerSt",ANY,(uint8_t)-1,any},
		// 0x054B
		{"SalJSONDeserializeUDV",ANY,(uint8_t)-1,any},
		// 0x054C
		{"SalBackgroundWorkerRe",ANY,(uint8_t)-1,any},
		// 0x054D
		{"SalBackgroundWorkerIs",ANY,(uint8_t)-1,any},
		// 0x054E
		{"SalBackgroundWorkerCa",ANY,(uint8_t)-1,any},
		// 0x054F
		{"SalBackgroundWorkerIs",ANY,(uint8_t)-1,any},
		// 0x0550
		{"SalRibbonSetItemTrans",ANY,(uint8_t)-1,any},
		// 0x0551
		{"SalTabSetPageTranspar",ANY,(uint8_t)-1,any},
		// 0x0552
		{"SalNavSetPaneTranspar",ANY,(uint8_t)-1,any},
		// 0x0553
		{"SalMeterShowPercent",ANY,(uint8_t)-1,any},
		// 0x0554
		{"SalMeterSetTextColor",ANY,(uint8_t)-1,any},
		// 0x0555
		{"SalJSONSerializeUDV",ANY,(uint8_t)-1,any},
		// 0x0556
		{"SalSetLibraryPath",ANY,(uint8_t)-1,any},
		// 0x0557
		{"SalGridSetSummaryColu",ANY,(uint8_t)-1,any},
		// 0x0558
		{"SalWebGetAppURL",ANY,(uint8_t)-1,any},
		// 0x0559
		{"SalWebGetConnectionSt",ANY,(uint8_t)-1,any},
		// 0x055A
		{"SalWebGetAppSetting",ANY,(uint8_t)-1,any},
		// 0x055B
		{"SalSetHintText",ANY,(uint8_t)-1,any},
		// 0x055C
		{"SalGetHintText",ANY,(uint8_t)-1,any},
		// 0x055D
		{"SalSetIMEMode",ANY,(uint8_t)-1,any},
		// 0x055E
		{"SalOutlineLoadMigrate",ANY,(uint8_t)-1,any},
		// 0x055F
		{"SalMenuSetAnimate",ANY,(uint8_t)-1,any},
		// 0x0560
		{"SalTblDestroyEdit",ANY,(uint8_t)-1,any},
		// 0x0561
		{"SalIsX64",ANY,(uint8_t)-1,any},
		// 0x0562
		{"SalOutlineCopyItemPro",ANY,(uint8_t)-1,any},
		// 0x0563
		{"SalSetTooltipImage",ANY,(uint8_t)-1,any},
		// 0x0564
		{"SalFileGetStrEx",ANY,(uint8_t)-1,any},
		// 0x0565
		{"SalRTFSetMargin",ANY,(uint8_t)-1,any},
		// 0x0566
		{"SalRTFGetMargin",ANY,(uint8_t)-1,any},
		// 0x0567
		{"SalThemeSetXMLPathNam",ANY,(uint8_t)-1,any},
		// 0x0568
		{"SalThemeGetXMLPathNam",ANY,(uint8_t)-1,any},
		// 0x0569
		{"SalBackgroundWorkerAn",ANY,(uint8_t)-1,any},
		// 0x056A
		{"SalBackgroundWorkerTe",ANY,(uint8_t)-1,any},
		// 0x056B
		{"SalGridColumnSummaryD",ANY,(uint8_t)-1,any},
		// 0x056C
		{"SalDateReturn",ANY,(uint8_t)-1,any},
		// 0x056D
		{"SalCenterWindowEx",ANY,(uint8_t)-1,any},
		// 0x056E
		{"SalNavGetExpandedCoun",ANY,(uint8_t)-1,any},
		// 0x056F
		{"SalNavSetExpandedCoun",ANY,(uint8_t)-1,any},
		// 0x0570
		{"SalStrCharLength",ANY,(uint8_t)-1,any},
		// 0x0571
		{"SalRibbonGetItemField",ANY,(uint8_t)-1,any},
		// 0x0572
		{"SalRibbonSetItemField",ANY,(uint8_t)-1,any},
		// 0x0573
		{"SqlConnectEx",ANY,(uint8_t)-1,any},
		// 0x0574
		{"SalRegexMatch",ANY,(uint8_t)-1,any},
		// 0x0575
		{"SalRegexSearch",ANY,(uint8_t)-1,any},
		// 0x0576
		{"SalRegexReplace",ANY,(uint8_t)-1,any},
		// 0x0577
		{"SalRegexReplaceAll",ANY,(uint8_t)-1,any},
		// 0x0578
		{"SalNotifyAddIcon",ANY,(uint8_t)-1,any},
		// 0x0579
		{"SalNotifyUpdateIcon",ANY,(uint8_t)-1,any},
		// 0x057A
		{"SalNotifyShowBalloon",ANY,(uint8_t)-1,any},
		// 0x057B
		{"SalNotifyDeleteIcon",ANY,(uint8_t)-1,any},
		// 0x057C
		{"SalJSONDeserializeUDV",ANY,(uint8_t)-1,any},
		// 0x057D
		{"SalJSONSerializeUDVEx",ANY,(uint8_t)-1,any},
		// 0x057E
		{"SalProfileStart",ANY,(uint8_t)-1,any},
		// 0x057F
		{"SalProfileSuspend",ANY,(uint8_t)-1,any},
		// 0x0580
		{"SalProfileContinue",ANY,(uint8_t)-1,any},
		// 0x0581
		{"SalProfileStop",ANY,(uint8_t)-1,any},
		// 0x0582
		{"SalGridIsRowExcludedB",ANY,(uint8_t)-1,any},
		// 0x0583
		{"SalGridBackColorSet",ANY,(uint8_t)-1,any},
		// 0x0584
		{"SalGridBackColorGet",ANY,(uint8_t)-1,any},
		// 0x0585
		{"SalGridTextColorSet",ANY,(uint8_t)-1,any},
		// 0x0586
		{"SalGridTextColorGet",ANY,(uint8_t)-1,any},
		// 0x0587
		{"SalTabAttachWindowAsC",ANY,(uint8_t)-1,any},
		// 0x0588
		{"SalTabIsWindowActivat",ANY,(uint8_t)-1,any},
		// 0x0589
		{"SalStrEncrypt",ANY,(uint8_t)-1,any},
		// 0x058A
		{"SalStrDecrypt",ANY,(uint8_t)-1,any},
		// 0x058B
		{"SalStrCompressEx",ANY,(uint8_t)-1,any},
		// 0x058C
		{"SalStrUncompressEx",ANY,(uint8_t)-1,any},
		// 0x058D
		{"SalNavSetGroupTitle",ANY,(uint8_t)-1,any},
		// 0x058E
		{"SalProfileGetInfo",ANY,(uint8_t)-1,any},
};

#endif /* SAL_FUNCTIONS_HPP_ */
