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

#include "sal_functions.hpp"

enum datatype any [] = { ANY };

// TODO: update datatypes
struct func_header INT_LOCALS[NUM_INT_LOCALS] = {
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
		// 0x000a
		{"SqlEnableFetchBackward",ANY,(uint8_t)-1,any},
		// 0x000b
		{"SqlError",ANY,(uint8_t)-1,any},
		// 0x000c
		{"SqlGetErrorText",ANY,(uint8_t)-1,any},
		// 0x000d
		{"SqlConnect",ANY,(uint8_t)-1,any},
		// 0x000e
		{"SqlGetErrorPosition",ANY,(uint8_t)-1,any},
		// 0x000f
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
		// 0x001a
		{"SalPostMsg",ANY,(uint8_t)-1,any},
		// 0x001b
		{"SalIsWindowVisible",ANY,(uint8_t)-1,any},
		// 0x001c
		{"SalCreateWindow",ANY,(uint8_t)-1,any},
		// 0x001d
		{"SalDestroyWindowExternal",ANY,(uint8_t)-1,any},
		// 0x001e
		{"SalClearField",ANY,(uint8_t)-1,any},
		// 0x001f
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
		// 0x002a
		{"SalQueryFieldEdit",ANY,(uint8_t)-1,any},
		// 0x002b
		{"SqlExtractArgs",ANY,(uint8_t)-1,any},
		// 0x002c
		{"SalLog",ANY,(uint8_t)-1,any},
		// 0x002d
		{"HSUnlock",ANY,(uint8_t)-1,any},
		// 0x002e
		{"SalModalDialog",ANY,(uint8_t)-1,any},
		// 0x002f
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
		// 0x003a
		{"SalListAdd",ANY,(uint8_t)-1,any},
		// 0x003b
		{"SalListClear",ANY,(uint8_t)-1,any},
		// 0x003c
		{"SalListDelete",ANY,(uint8_t)-1,any},
		// 0x003d
		{"SalListInsert",ANY,(uint8_t)-1,any},
		// 0x003e
		{"SalListQueryCount",ANY,(uint8_t)-1,any},
		// 0x003f
		{"SalListQuerySelection",ANY,(uint8_t)-1,any},
		// 0x0040
		{"SalListQueryState",ANY,(uint8_t)-1,any},
		// 0x0041
		{"SalListQueryText",ANY,(uint8_t)-1,any},
		// 0x0042
		{"SalListQueryTextLength",ANY,(uint8_t)-1,any},
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
		// 0x004a
		{"SalTblQueryContext",ANY,(uint8_t)-1,any},
		// 0x004b
		{"SalTblQueryScroll",ANY,(uint8_t)-1,any},
		// 0x004c
		{"SalTblQueryVisibleRange",ANY,(uint8_t)-1,any},
		// 0x004d
		{"SalTblScroll",ANY,(uint8_t)-1,any},
		// 0x004e
		{"SalTblSetContext",ANY,(uint8_t)-1,any},
		// 0x004f
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
		// 0x005a
		{"SalTblDeleteRow",ANY,(uint8_t)-1,any},
		// 0x005b
		{"SalTblPaintRows",ANY,(uint8_t)-1,any},
		// 0x005c
		{"SalFileTell",ANY,(uint8_t)-1,any},
		// 0x005d
		{"SqlClearImmediate",ANY,(uint8_t)-1,any},
		// 0x005e
		{"SalNumberMod",ANY,(uint8_t)-1,any},
		// 0x005f
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
		// 0x006a
		{"SalLogNumber",ANY,(uint8_t)-1,any},
		// 0x006b
		{"SalFileClose",ANY,(uint8_t)-1,any},
		// 0x006c
		{"SalFileOpen",ANY,(uint8_t)-1,any},
		// 0x006d
		{"SalFileGetChar",ANY,(uint8_t)-1,any},
		// 0x006e
		{"SalFileGetStr",ANY,(uint8_t)-1,any},
		// 0x006f
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
		// 0x007a
		{"SalDateMonth",ANY,(uint8_t)-1,any},
		// 0x007b
		{"SalDateMonthBegin",ANY,(uint8_t)-1,any},
		// 0x007c
		{"SalDateQuarter",ANY,(uint8_t)-1,any},
		// 0x007d
		{"SalDateQuarterBegin",ANY,(uint8_t)-1,any},
		// 0x007e
		{"SalDateSecond",ANY,(uint8_t)-1,any},
		// 0x007f
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
		// 0x008a
		{"SalStrLower",ANY,(uint8_t)-1,any},
		// 0x008b
		{"SalStrMid",ANY,(uint8_t)-1,any},
		// 0x008c
		{"SalStrProper",ANY,(uint8_t)-1,any},
		// 0x008d
		{"SalStrRepeat",ANY,(uint8_t)-1,any},
		// 0x008e
		{"SalStrReplace",ANY,(uint8_t)-1,any},
		// 0x008f
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
		// 0x009a
		{"SalDDEFindAtom",ANY,(uint8_t)-1,any},
		// 0x009b
		{"SalDDEGetAtomName",ANY,(uint8_t)-1,any},
		// 0x009c
		{"SalDDEAlloc",ANY,(uint8_t)-1,any},
		// 0x009d
		{"SalDDEFree",ANY,(uint8_t)-1,any},
		// 0x009e
		{"SalDDESend",ANY,(uint8_t)-1,any},
		// 0x009f
		{"SalDDEPost",ANY,(uint8_t)-1,any},
		// 0x00a0
		{"SalDDEExtract",ANY,(uint8_t)-1,any},
		// 0x00a1
		{"SalDDESetOptions",ANY,(uint8_t)-1,any},
		// 0x00a2
		{"SalDDESetDataText",ANY,(uint8_t)-1,any},
		// 0x00a3
		{"SalDDESetCmd",ANY,(uint8_t)-1,any},
		// 0x00a4
		{"SalDDEExtractOptions",ANY,(uint8_t)-1,any},
		// 0x00a5
		{"SalDDEExtractDataText",ANY,(uint8_t)-1,any},
		// 0x00a6
		{"SalDDEExtractCmd",ANY,(uint8_t)-1,any},
		// 0x00a7
		{"SalDDESendAll",ANY,(uint8_t)-1,any},
		// 0x00a8
		{"SalBringWindowToTop",ANY,(uint8_t)-1,any},
		// 0x00a9
		{"SalCompileAndEvaluate",ANY,(uint8_t)-1,any},
		// 0x00aa
		{"SalMessageBeep",ANY,(uint8_t)-1,any},
		// 0x00ab
		{"SalContextBreak",ANY,(uint8_t)-1,any},
		// 0x00ac
		{"SalContextCurrent",ANY,(uint8_t)-1,any},
		// 0x00ad
		{"SalStrLop",ANY,(uint8_t)-1,any},
		// 0x00ae
		{"SalScrollSetRange",ANY,(uint8_t)-1,any},
		// 0x00af
		{"SalSetFocus",ANY,(uint8_t)-1,any},
		// 0x00b0
		{"SalGetFocus",ANY,(uint8_t)-1,any},
		// 0x00b1
		{"SalPicGetDescription",ANY,(uint8_t)-1,any},
		// 0x00b2
		{"SalDlgChooseColor",ANY,(uint8_t)-1,any},
		// 0x00b3
		{"SalLoadApp",ANY,(uint8_t)-1,any},
		// 0x00b4
		{"SalFmtGetFormat",ANY,(uint8_t)-1,any},
		// 0x00b5
		{"SalFmtGetParmInt",ANY,(uint8_t)-1,any},
		// 0x00b6
		{"SalFmtGetParmStr",ANY,(uint8_t)-1,any},
		// 0x00b7
		{"SalFmtGetProfile",ANY,(uint8_t)-1,any},
		// 0x00b8
		{"SalFmtIsValidField",ANY,(uint8_t)-1,any},
		// 0x00b9
		{"SalFmtSetFormat",ANY,(uint8_t)-1,any},
		// 0x00ba
		{"SalFmtSetParmInt",ANY,(uint8_t)-1,any},
		// 0x00bb
		{"SalFmtSetParmStr",ANY,(uint8_t)-1,any},
		// 0x00bc
		{"SalFmtSetProfile",ANY,(uint8_t)-1,any},
		// 0x00bd
		{"SalFmtValidateField",ANY,(uint8_t)-1,any},
		// 0x00be
		{"SalFmtCopyProfile",ANY,(uint8_t)-1,any},
		// 0x00bf
		{"SalFmtFieldToStr",ANY,(uint8_t)-1,any},
		// 0x00c0
		{"SalPrtPrintForm",ANY,(uint8_t)-1,any},
		// 0x00c1
		{"SalPrtGetParmNum",ANY,(uint8_t)-1,any},
		// 0x00c2
		{"SalPrtSetParmNum",ANY,(uint8_t)-1,any},
		// 0x00c3
		{"SalPrtSetParmDefaults",ANY,(uint8_t)-1,any},
		// 0x00c4
		{"SalFmtStrToField",ANY,(uint8_t)-1,any},
		// 0x00c5
		{"SqlGetCursor",ANY,(uint8_t)-1,any},
		// 0x00c6
		{"SalGetItemName",ANY,(uint8_t)-1,any},
		// 0x00c7
		{"@SalDebug",ANY,(uint8_t)-1,any},
		// 0x00c8
		{"SalFormGetParmNum",ANY,(uint8_t)-1,any},
		// 0x00c9
		{"SqlSystem",ANY,(uint8_t)-1,any},
		// 0x00ca
		{"SqlSetResultSet",ANY,(uint8_t)-1,any},
		// 0x00cb
		{"SalTimerSet",ANY,(uint8_t)-1,any},
		// 0x00cc
		{"SalTimerKill",ANY,(uint8_t)-1,any},
		// 0x00cd
		{"SalGetDataType",ANY,(uint8_t)-1,any},
		// 0x00ce
		{"SalGetMaxDataLength",ANY,(uint8_t)-1,any},
		// 0x00cf
		{"SalGetType",ANY,(uint8_t)-1,any},
		// 0x00d0
		{"SalTblGetColumnTitle",ANY,(uint8_t)-1,any},
		// 0x00d1
		{"SalTblSetColumnTitle",ANY,(uint8_t)-1,any},
		// 0x00d2
		{"SalWindowHandleToNumber",ANY,(uint8_t)-1,any},
		// 0x00d3
		{"SalNumberToWindowHandle",ANY,(uint8_t)-1,any},
		// 0x00d4
		{"SqlSetLockTimeout",ANY,(uint8_t)-1,any},
		// 0x00d5
		{"SqlGetResultSetCount",ANY,(uint8_t)-1,any},
		// 0x00d6
		{"SqlGetModifiedRows",ANY,(uint8_t)-1,any},
		// 0x00d7
		{"SalNumRand",ANY,(uint8_t)-1,any},
		// 0x00d8
		{"SalNumSRand",ANY,(uint8_t)-1,any},
		// 0x00d9
		{"SalSendValidateMsg",ANY,(uint8_t)-1,any},
		// 0x00da
		{"SalSendMsgToChildren",ANY,(uint8_t)-1,any},
		// 0x00db
		{"SalPause",ANY,(uint8_t)-1,any},
		// 0x00dc
		{"SalTblSetColumnWidth",ANY,(uint8_t)-1,any},
		// 0x00dd
		{"SalTblQueryColumnWidth",ANY,(uint8_t)-1,any},
		// 0x00de
		{"SalOutlineGetItemType",ANY,(uint8_t)-1,any},
		// 0x00df
		{"SalOutlineGetItemText",ANY,(uint8_t)-1,any},
		// 0x00e0
		{"SalSetMaxDataLength",ANY,(uint8_t)-1,any},
		// 0x00e1
		{"SalResLoad",ANY,(uint8_t)-1,any},
		// 0x00e2
		{"SalAppFind",ANY,(uint8_t)-1,any},
		// 0x00e3
		{"SalStrIsValidIdentifierName",ANY,(uint8_t)-1,any},
		// 0x00e4
		{"SalChangeLineCountLock",ANY,(uint8_t)-1,any},
		// 0x00e5
		{"SalChangeLineCountNotify",ANY,(uint8_t)-1,any},
		// 0x00e6
		{"SalIsOutlineSecondary",ANY,(uint8_t)-1,any},
		// 0x00e7
		{"SalChangeLineCountUnlock",ANY,(uint8_t)-1,any},
		// 0x00e8
		{"SalItemGetLineNumber",ANY,(uint8_t)-1,any},
		// 0x00e9
		{"SalOutlineItemSetProperty",ANY,(uint8_t)-1,any},
		// 0x00ea
		{"SalOutlineItemGetProperty",ANY,(uint8_t)-1,any},
		// 0x00eb
		{"SalOutlineSetOutlineHook",ANY,(uint8_t)-1,any},
		// 0x00ec
		{"SalOutlineShare",ANY,(uint8_t)-1,any},
		// 0x00ed
		{"SalFindWindow",ANY,(uint8_t)-1,any},
		// 0x00ee
		{"SalOutlineEnumWindowProps",ANY,(uint8_t)-1,any},
		// 0x00ef
		{"SalOutlineEnumItemProps",ANY,(uint8_t)-1,any},
		// 0x00f0
		{"SalEditInsertObject",ANY,(uint8_t)-1,any},
		// 0x00f1
		{"SqlStore",ANY,(uint8_t)-1,any},
		// 0x00f2
		{"SqlRetrieve",ANY,(uint8_t)-1,any},
		// 0x00f3
		{"SqlDirectoryByName",ANY,(uint8_t)-1,any},
		// 0x00f4
		{"SqlGetParameter",ANY,(uint8_t)-1,any},
		// 0x00f5
		{"SqlSetParameter",ANY,(uint8_t)-1,any},
		// 0x00f6
		{"SalReportView",ANY,(uint8_t)-1,any},
		// 0x00f7
		{"SalReportPrint",ANY,(uint8_t)-1,any},
		// 0x00f8
		{"SalReportClose",ANY,(uint8_t)-1,any},
		// 0x00f9
		{"SalReportCmd",ANY,(uint8_t)-1,any},
		// 0x00fa
		{"SqlDropStoredCmd",ANY,(uint8_t)-1,any},
		// 0x00fb
		{"SalWinHelp",ANY,(uint8_t)-1,any},
		// 0x00fc
		{"SalReportReset",ANY,(uint8_t)-1,any},
		// 0x00fd
		{"SalAppEnable",ANY,(uint8_t)-1,any},
		// 0x00fe
		{"SalAppDisable",ANY,(uint8_t)-1,any},
		// 0x00ff
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
		{"@ArrayGet",ANY,(uint8_t)-1,any},
		// 0x0105
		{"@ArrayPut",ANY,(uint8_t)-1,any},
		// 0x0106
		{"SalInitLPHSTRINGParam",ANY,(uint8_t)-1,any},
		// 0x0107
		{"SalReportCreate",ANY,(uint8_t)-1,any},
		// 0x0108
		{"SqlCommit",ANY,(uint8_t)-1,any},
		// 0x0109
		{"SalNumberToChar",ANY,(uint8_t)-1,any},
		// 0x010a
		{"SalPrtExtractRect",ANY,(uint8_t)-1,any},
		// 0x010b
		{"SalYieldEnable",ANY,(uint8_t)-1,any},
		// 0x010c
		{"SalYieldQueryState",ANY,(uint8_t)-1,any},
		// 0x010d
		{"SqlGetParameterAll",ANY,(uint8_t)-1,any},
		// 0x010e
		{"SqlSetParameterAll",ANY,(uint8_t)-1,any},
		// 0x010f
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
		{"@RunBaseClassMsg",ANY,(uint8_t)-1,any},
		// 0x011a
		{"SalOutlineSave",ANY,(uint8_t)-1,any},
		// 0x011b
		{"SalReportDlgOptions",ANY,(uint8_t)-1,any},
		// 0x011c
		{"SalStrLeftB",ANY,(uint8_t)-1,any},
		// 0x011d
		{"SalStringLengthB",ANY,(uint8_t)-1,any},
		// 0x011e
		{"SalStrMidB",ANY,(uint8_t)-1,any},
		// 0x011f
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
		// 0x012a
		{"SalStrFull",ANY,(uint8_t)-1,any},
		// 0x012b
		{"SalStrHalf",ANY,(uint8_t)-1,any},
		// 0x012c
		{"SalStrFirstC",ANY,(uint8_t)-1,any},
		// 0x012d
		{"SalFileGetC",ANY,(uint8_t)-1,any},
		// 0x012e
		{"SalFilePutC",ANY,(uint8_t)-1,any},
		// 0x012f
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
		{"SalFileGetCurrentDirectory",ANY,(uint8_t)-1,any},
		// 0x0136
		{"SalFileSetCurrentDirectory",ANY,(uint8_t)-1,any},
		// 0x0137
		{"SalFileCopy",ANY,(uint8_t)-1,any},
		// 0x0138
		{"SalFileCreateDirectory",ANY,(uint8_t)-1,any},
		// 0x0139
		{"SalFileRemoveDirectory",ANY,(uint8_t)-1,any},
		// 0x013a
		{"SalEditCopyString",ANY,(uint8_t)-1,any},
		// 0x013b
		{"SalEditPasteString",ANY,(uint8_t)-1,any},
		// 0x013c
		{"SalTblAnyRows",ANY,(uint8_t)-1,any},
		// 0x013d
		{"SalTblCopyRows",ANY,(uint8_t)-1,any},
		// 0x013e
		{"SalListPopulate",ANY,(uint8_t)-1,any},
		// 0x013f
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
		// 0x014a
		{"SalOutlinePreviousSibling",ANY,(uint8_t)-1,any},
		// 0x014b
		{"SalOutlineChildOfType",ANY,(uint8_t)-1,any},
		// 0x014c
		{"SalIsButtonChecked",ANY,(uint8_t)-1,any},
		// 0x014d
		{"SalDropFilesAcceptFiles",ANY,(uint8_t)-1,any},
		// 0x014e
		{"SalEditPasteSpecial",ANY,(uint8_t)-1,any},
		// 0x014f
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
		{"SalDragDropDisableDrop",ANY,(uint8_t)-1,any},
		// 0x0157
		{"SalDragDropStart",ANY,(uint8_t)-1,any},
		// 0x0158
		{"SalDragDropStop",ANY,(uint8_t)-1,any},
		// 0x0159
		{"SalCursorClear",ANY,(uint8_t)-1,any},
		// 0x015a
		{"SalMapEnterToTab",ANY,(uint8_t)-1,any},
		// 0x015b
		{"SalPicClear",ANY,(uint8_t)-1,any},
		// 0x015c
		{"SalPicSetFile",ANY,(uint8_t)-1,any},
		// 0x015d
		{"SalPicSetFit",ANY,(uint8_t)-1,any},
		// 0x015e
		{"SalPicSetString",ANY,(uint8_t)-1,any},
		// 0x015f
		{"SalYieldStartMessages",ANY,(uint8_t)-1,any},
		// 0x0160
		{"SalYieldStopMessages",ANY,(uint8_t)-1,any},
		// 0x0161
		{"SalStrTokenize",ANY,(uint8_t)-1,any},
		// 0x0162
		{"SalListGetMultiSelect",ANY,(uint8_t)-1,any},
		// 0x0163
		{"SalListQueryMultiCount",ANY,(uint8_t)-1,any},
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
		// 0x016a
		{"SalIsWindowEnabled",ANY,(uint8_t)-1,any},
		// 0x016b
		{"SalReportGetDateTimeVar",ANY,(uint8_t)-1,any},
		// 0x016c
		{"SalUpdateWindow",ANY,(uint8_t)-1,any},
		// 0x016d
		{"SalMoveWindow",ANY,(uint8_t)-1,any},
		// 0x016e
		{"SalOutlineFirstChild",ANY,(uint8_t)-1,any},
		// 0x016f
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
		// 0x017a
		{"SalNumberSinH",ANY,(uint8_t)-1,any},
		// 0x017b
		{"SalNumberCos",ANY,(uint8_t)-1,any},
		// 0x017c
		{"SalNumberArcCos",ANY,(uint8_t)-1,any},
		// 0x017d
		{"SalNumberCosH",ANY,(uint8_t)-1,any},
		// 0x017e
		{"SalNumberAbs",ANY,(uint8_t)-1,any},
		// 0x017f
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
		// 0x018a
		{"SalHStringToNumber",ANY,(uint8_t)-1,any},
		// 0x018b
		{"SalNumberToHString",ANY,(uint8_t)-1,any},
		// 0x018c
		{"SalNumberPi",ANY,(uint8_t)-1,any},
		// 0x018d
		{"SalNumberExponent",ANY,(uint8_t)-1,any},
		// 0x018e
		{"SalNumberMin",ANY,(uint8_t)-1,any},
		// 0x018f
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
		// 0x019a
		{"SalTblQueryTableFlags",ANY,(uint8_t)-1,any},
		// 0x019b
		{"SalTblQueryColumnFlags",ANY,(uint8_t)-1,any},
		// 0x019c
		{"SalTblDefineRowHeader",ANY,(uint8_t)-1,any},
		// 0x019d
		{"SalTblQueryRowHeader",ANY,(uint8_t)-1,any},
		// 0x019e
		{"SalTblDefineSplitWindow",ANY,(uint8_t)-1,any},
		// 0x019f
		{"SalTblQuerySplitWindow",ANY,(uint8_t)-1,any},
		// 0x01a0
		{"SalTblSetLockedColumns",ANY,(uint8_t)-1,any},
		// 0x01a1
		{"SalTblQueryLockedColumns",ANY,(uint8_t)-1,any},
		// 0x01a2
		{"SalTblQueryColumnID",ANY,(uint8_t)-1,any},
		// 0x01a3
		{"SalTblSetCellTextColor",ANY,(uint8_t)-1,any},
		// 0x01a4
		{"SalTblSetColumnFlags",ANY,(uint8_t)-1,any},
		// 0x01a5
		{"SalOutlineGetItemFlags",ANY,(uint8_t)-1,any},
		// 0x01a6
		{"SalOutlineSetItemFlags",ANY,(uint8_t)-1,any},
		// 0x01a7
		{"SalOutlineNextLikeItem",ANY,(uint8_t)-1,any},
		// 0x01a8
		{"SalReportGetNumberVar",ANY,(uint8_t)-1,any},
		// 0x01a9
		{"SalOutlineSetData",ANY,(uint8_t)-1,any},
		// 0x01aa
		{"SalOutlineDeleteItem",ANY,(uint8_t)-1,any},
		// 0x01ab
		{"SalOutlineItemIsIncluded",ANY,(uint8_t)-1,any},
		// 0x01ac
		{"SalReportGetObjectVar",ANY,(uint8_t)-1,any},
		// 0x01ad
		{"SalReportGetStringVar",ANY,(uint8_t)-1,any},
		// 0x01ae
		{"SalTblSetFlagsAnyRows",ANY,(uint8_t)-1,any},
		// 0x01af
		{"SalTblDoDeletes",ANY,(uint8_t)-1,any},
		// 0x01b0
		{"SalEditPasteLink",ANY,(uint8_t)-1,any},
		// 0x01b1
		{"SalReportSetDateTimeVar",ANY,(uint8_t)-1,any},
		// 0x01b2
		{"SalReportSetNumberVar",ANY,(uint8_t)-1,any},
		// 0x01b3
		{"SalReportSetObjectVar",ANY,(uint8_t)-1,any},
		// 0x01b4
		{"SalDDEStartSession",ANY,(uint8_t)-1,any},
		// 0x01b5
		{"SalDDEStopSession",ANY,(uint8_t)-1,any},
		// 0x01b6
		{"SalDDERequest",ANY,(uint8_t)-1,any},
		// 0x01b7
		{"SalDDESendExecute",ANY,(uint8_t)-1,any},
		// 0x01b8
		{"SalDDEStartServer",ANY,(uint8_t)-1,any},
		// 0x01b9
		{"SalDDEStopServer",ANY,(uint8_t)-1,any},
		// 0x01ba
		{"SalDDESendToClient",ANY,(uint8_t)-1,any},
		// 0x01bb
		{"SalReportSetStringVar",ANY,(uint8_t)-1,any},
		// 0x01bc
		{"@RunBaseClassMsg",ANY,(uint8_t)-1,any},
		// 0x01bd
		{"SalGetVersion",ANY,(uint8_t)-1,any},
		// 0x01be
		{"SqlSetInMessage",ANY,(uint8_t)-1,any},
		// 0x01bf
		{"SqlSetOutMessage",ANY,(uint8_t)-1,any},
		// 0x01c0
		{"SqlPrepareAndExecute",ANY,(uint8_t)-1,any},
		// 0x01c1
		{"SalPicGetString",ANY,(uint8_t)-1,any},
		// 0x01c2
		{"SalEditCanPasteLink",ANY,(uint8_t)-1,any},
		// 0x01c3
		{"SalEditCanPasteSpecial",ANY,(uint8_t)-1,any},
		// 0x01c4
		{"SalEditCanInsertObject",ANY,(uint8_t)-1,any},
		// 0x01c5
		{"SalOLEAnyActive",ANY,(uint8_t)-1,any},
		// 0x01c6
		{"SalEditCanPasteFrom",ANY,(uint8_t)-1,any},
		// 0x01c7
		{"SalEditPasteFrom",ANY,(uint8_t)-1,any},
		// 0x01c8
		{"SalOLEAnyLinked",ANY,(uint8_t)-1,any},
		// 0x01c9
		{"SalOLEDoVerb",ANY,(uint8_t)-1,any},
		// 0x01ca
		{"SalOLEFileInsert",ANY,(uint8_t)-1,any},
		// 0x01cb
		{"SalOLEGetServers",ANY,(uint8_t)-1,any},
		// 0x01cc
		{"SalEditCopyTo",ANY,(uint8_t)-1,any},
		// 0x01cd
		{"SalEditCanCopyTo",ANY,(uint8_t)-1,any},
		// 0x01ce
		{"SalOLEGetVerbs",ANY,(uint8_t)-1,any},
		// 0x01cf
		{"SalOLELinkProperties",ANY,(uint8_t)-1,any},
		// 0x01d0
		{"SalDlgOpenFile",ANY,(uint8_t)-1,any},
		// 0x01d1
		{"SalDlgChooseFont",ANY,(uint8_t)-1,any},
		// 0x01d2
		{"SalNumberToStrX",ANY,(uint8_t)-1,any},
		// 0x01d3
		{"SalStrLeftX",ANY,(uint8_t)-1,any},
		// 0x01d4
		{"SalStrLowerX",ANY,(uint8_t)-1,any},
		// 0x01d5
		{"SalStrMidX",ANY,(uint8_t)-1,any},
		// 0x01d6
		{"SalStrProperX",ANY,(uint8_t)-1,any},
		// 0x01d7
		{"SalStrRepeatX",ANY,(uint8_t)-1,any},
		// 0x01d8
		{"SalStrReplaceX",ANY,(uint8_t)-1,any},
		// 0x01d9
		{"SalStrRightX",ANY,(uint8_t)-1,any},
		// 0x01da
		{"SalStrTrimX",ANY,(uint8_t)-1,any},
		// 0x01db
		{"SalStrUpperX",ANY,(uint8_t)-1,any},
		// 0x01dc
		{"SqlGetErrorTextX",ANY,(uint8_t)-1,any},
		// 0x01dd
		{"SalOutlineItemTextX",ANY,(uint8_t)-1,any},
		// 0x01de
		{"SalOutlineItemTitleX",ANY,(uint8_t)-1,any},
		// 0x01df
		{"SalOutlineCreateDesignWindow",ANY,(uint8_t)-1,any},
		// 0x01e0
		{"SalOutlineSetFormFlags",ANY,(uint8_t)-1,any},
		// 0x01e1
		{"SalOutlineGetFormFlags",ANY,(uint8_t)-1,any},
		// 0x01e2
		{"SalOutlineSetDrawTool",ANY,(uint8_t)-1,any},
		// 0x01e3
		{"SalOutlineGetDrawTool",ANY,(uint8_t)-1,any},
		// 0x01e4
		{"SalOutlineCanAlignWindows",ANY,(uint8_t)-1,any},
		// 0x01e5
		{"SalOutlineAlignWindows",ANY,(uint8_t)-1,any},
		// 0x01e6
		{"SalOutlineCanMoveToFront",ANY,(uint8_t)-1,any},
		// 0x01e7
		{"SalOutlineCanMoveToBack",ANY,(uint8_t)-1,any},
		// 0x01e8
		{"SalOutlineMoveToFront",ANY,(uint8_t)-1,any},
		// 0x01e9
		{"SalOutlineMoveToBack",ANY,(uint8_t)-1,any},
		// 0x01ea
		{"SalOutlineOrderTabs",ANY,(uint8_t)-1,any},
		// 0x01eb
		{"SalOutlineDontCustomizeType",ANY,(uint8_t)-1,any},
		// 0x01ec
		{"SalOutlineSetCustomCmd",ANY,(uint8_t)-1,any},
		// 0x01ed
		{"SalOutlineClearCustomCmds",ANY,(uint8_t)-1,any},
		// 0x01ee
		{"SalOutlineItemOfWindow",ANY,(uint8_t)-1,any},
		// 0x01ef
		{"SalOutlineOutlineOfWindow",ANY,(uint8_t)-1,any},
		// 0x01f0
		{"SalOutlineWindowOfItem",ANY,(uint8_t)-1,any},
		// 0x01f1
		{"SalOutlineLockDrawTool",ANY,(uint8_t)-1,any},
		// 0x01f2
		{"SalOutlineIsWindowItem",ANY,(uint8_t)-1,any},
		// 0x01f3
		{"SalOutlineIsItemMarked",ANY,(uint8_t)-1,any},
		// 0x01f4
		{"SalOutlineChangeSelect",ANY,(uint8_t)-1,any},
		// 0x01f5
		{"SalOutlineIsDrawToolLocked",ANY,(uint8_t)-1,any},
		// 0x01f6
		{"SalOutlineCustomizeItem",ANY,(uint8_t)-1,any},
		// 0x01f7
		{"SalOutlineItemChangeUpdate",ANY,(uint8_t)-1,any},
		// 0x01f8
		{"SalOutlineWindowItemOfItem",ANY,(uint8_t)-1,any},
		// 0x01f9
		{"SalOutlineItemTypeText",ANY,(uint8_t)-1,any},
		// 0x01fa
		{"SalOutlineSetTypeData",ANY,(uint8_t)-1,any},
		// 0x01fb
		{"SalOutlineCreateItem",ANY,(uint8_t)-1,any},
		// 0x01fc
		{"SalOutlineFirstMarked",ANY,(uint8_t)-1,any},
		// 0x01fd
		{"SalOutlineNextMarked",ANY,(uint8_t)-1,any},
		// 0x01fe
		{"SalDDEGetExecuteString",ANY,(uint8_t)-1,any},
		// 0x01ff
		{"SalListQueryTextX",ANY,(uint8_t)-1,any},
		// 0x0200
		{"SalDropFilesQueryPoint",ANY,(uint8_t)-1,any},
		// 0x0201
		{"SalDropFilesQueryFiles",ANY,(uint8_t)-1,any},
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
		// 0x020a
		{"SqlContextClear",ANY,(uint8_t)-1,any},
		// 0x020b
		{"SqlContextSet",ANY,(uint8_t)-1,any},
		// 0x020c
		{"SqlImmediateContext",ANY,(uint8_t)-1,any},
		// 0x020d
		{"SalGetProfileString",ANY,(uint8_t)-1,any},
		// 0x020e
		{"SalSetDLLDataMode",ANY,(uint8_t)-1,any},
		// 0x020f
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
		{"SalReportSetPrintParameter",ANY,(uint8_t)-1,any},
		// 0x0216
		{"SqlErrorText",ANY,(uint8_t)-1,any},
		// 0x0217
		{"SqlExecutionPlan",ANY,(uint8_t)-1,any},
		// 0x0218
		{"SalOLEServerInsert",ANY,(uint8_t)-1,any},
		// 0x0219
		{"SalLoadAppAndWait",ANY,(uint8_t)-1,any},
		// 0x021a
		{"SalTblColumnAverage",ANY,(uint8_t)-1,any},
		// 0x021b
		{"SalTblColumnSum",ANY,(uint8_t)-1,any},
		// 0x021c
		{"SalTrackPopupMenu",ANY,(uint8_t)-1,any},
		// 0x021d
		{"SalStatusSetVisible",ANY,(uint8_t)-1,any},
		// 0x021e
		{"SalTBarSetVisible",ANY,(uint8_t)-1,any},
		// 0x021f
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
		{"SalFmtIsValidInputMask",ANY,(uint8_t)-1,any},
		// 0x0226
		{"SalFmtUnmaskInput",ANY,(uint8_t)-1,any},
		// 0x0227
		{"SalStrCompress",ANY,(uint8_t)-1,any},
		// 0x0228
		{"SalStrUncompress",ANY,(uint8_t)-1,any},
		// 0x0229
		{"SalFileGetDateTime",ANY,(uint8_t)-1,any},
		// 0x022a
		{"SalFileSetDateTime",ANY,(uint8_t)-1,any},
		// 0x022b
		{"SalSetProfileString",ANY,(uint8_t)-1,any},
		// 0x022c
		{"SalGetProfileInt",ANY,(uint8_t)-1,any},
		// 0x022d
		{"SalDisableWindowAndLabel",ANY,(uint8_t)-1,any},
		// 0x022e
		{"SalEnableWindowAndLabel",ANY,(uint8_t)-1,any},
		// 0x022f
		{"SalGetWindowLabel",ANY,(uint8_t)-1,any},
		// 0x0230
		{"SalModalDialogFromStr",ANY,(uint8_t)-1,any},
		// 0x0231
		{"SalOutlineBlockNotifications",ANY,(uint8_t)-1,any},
		// 0x0232
		{"SalOLEUpdateActive",ANY,(uint8_t)-1,any},
		// 0x0233
		{"SalOutlineSetDTData",ANY,(uint8_t)-1,any},
		// 0x0234
		{"SalOutlineSetItemClassObject",ANY,(uint8_t)-1,any},
		// 0x0235
		{"__ObjectIsValid",ANY,(uint8_t)-1,any},
		// 0x0236
		{"NULL",ANY,(uint8_t)-1,any},
		// 0x0237
		{"NULL",ANY,(uint8_t)-1,any},
		// 0x0238
		{"SalCursorSet",ANY,(uint8_t)-1,any},
		// 0x0239
		{"SalShowWindowAndLabel",ANY,(uint8_t)-1,any},
		// 0x023a
		{"SalHideWindowAndLabel",ANY,(uint8_t)-1,any},
		// 0x023b
		{"SalCurrentLineNumber",ANY,(uint8_t)-1,any},
		// 0x023c
		{"SalFlashWindow",ANY,(uint8_t)-1,any},
		// 0x023d
		{"SalReportPrintToFile",ANY,(uint8_t)-1,any},
		// 0x023e
		{"NULL",ANY,(uint8_t)-1,any},
		// 0x023f
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
		{"SalOutlineGetAttributes",ANY,(uint8_t)-1,any},
		// 0x0247
		{"NULL",ANY,(uint8_t)-1,any},
		// 0x0248
		{"SalFmtKeepMask",ANY,(uint8_t)-1,any},
		// 0x0249
		{"SalResId",ANY,(uint8_t)-1,any},
		// 0x024a
		{"SalOutlineIsClassChildRef",ANY,(uint8_t)-1,any},
		// 0x024b
		{"SqlPLSQLExecute",ANY,(uint8_t)-1,any},
		// 0x024c
		{"SqlPLSQLCommand",ANY,(uint8_t)-1,any},
		// 0x024d
		{"@RunBaseClassChildMsg",ANY,(uint8_t)-1,any},
		// 0x024e
		{"SalHStringRef",ANY,(uint8_t)-1,any},
		// 0x024f
		{"SalHStringUnRef",ANY,(uint8_t)-1,any},
		// 0x0250
		{"SalArrayCreate",ANY,(uint8_t)-1,any},
		// 0x0251
		{"SalArrayDestroy",ANY,(uint8_t)-1,any},
		// 0x0252
		{"SalFireEvent",ANY,(uint8_t)-1,any},
		// 0x0253
		{"__SetBlobVariant",ANY,(uint8_t)-1,any},
		// 0x0254
		{"__GetBlobVariant",ANY,(uint8_t)-1,any},
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
		// 0x025a
		{"NULL",ANY,(uint8_t)-1,any},
		// 0x025b
		{"SalOutlineRefreshInclude",ANY,(uint8_t)-1,any},
		// 0x025c
		{"SalValidateSet",ANY,(uint8_t)-1,any},
		// 0x025d
		{"NULL",ANY,(uint8_t)-1,any},
		// 0x025e
		{"NULL",ANY,(uint8_t)-1,any},
		// 0x025f
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
		{"SalDataGetSourceWindow",ANY,(uint8_t)-1,any},
		// 0x0265
		{"SalDataGetFieldWindow",ANY,(uint8_t)-1,any},
		// 0x0266
		{"SalDataQueryFieldExtent",ANY,(uint8_t)-1,any},
		// 0x0267
		{"SalDataGetFieldData",ANY,(uint8_t)-1,any},
		// 0x0268
		{"SalWindowSetProperty",ANY,(uint8_t)-1,any},
		// 0x0269
		{"SalWindowGetProperty",ANY,(uint8_t)-1,any},
		// 0x026a
		{"HSCreateDesignHeap",ANY,(uint8_t)-1,any},
		// 0x026b
		{"HSDestroyDesignHeap",ANY,(uint8_t)-1,any},
		// 0x026c
		{"SalOutlineSetAppChanged",ANY,(uint8_t)-1,any},
		// 0x026d
		{"SalOutlineSetAppUncompiled",ANY,(uint8_t)-1,any},
		// 0x026e
		{"SalOutlineItemLineCount",ANY,(uint8_t)-1,any},
		// 0x026f
		{"SalOutlineWindowOfItemIndirect",ANY,(uint8_t)-1,any},
		// 0x0270
		{"SalOutlineItemOfWindowIndirect",ANY,(uint8_t)-1,any},
		// 0x0271
		{"SalOutlinePropertyChangeUpdate",ANY,(uint8_t)-1,any},
		// 0x0272
		{"SalOutlineEnumSymbols",ANY,(uint8_t)-1,any},
		// 0x0273
		{"SalOutlineGetFunParams",ANY,(uint8_t)-1,any},
		// 0x0274
		{"SqlConnectUsingCursor",ANY,(uint8_t)-1,any},
		// 0x0275
		{"SqlGetSqlHandle",ANY,(uint8_t)-1,any},
		// 0x0276
		{"SqlDisconnectWithoutCursor",ANY,(uint8_t)-1,any},
		// 0x0277
		{"SqlConnectTransaction",ANY,(uint8_t)-1,any},
		// 0x0278
		{"NULL",ANY,(uint8_t)-1,any},
		// 0x0279
		{"NULL",ANY,(uint8_t)-1,any},
		// 0x027a
		{"NULL",ANY,(uint8_t)-1,any},
		// 0x027b
		{"NULL",ANY,(uint8_t)-1,any},
		// 0x027c
		{"NULL",ANY,(uint8_t)-1,any},
		// 0x027d
		{"SqlSetLongBindDatatype",ANY,(uint8_t)-1,any},
		// 0x027e
		{"SalBIDIDlgChooseFontsIntern",ANY,(uint8_t)-1,any},
		// 0x027f
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
		{"SalWindowIsDerivedFromClass",ANY,(uint8_t)-1,any},
		// 0x0286
		{"SalDisableAllWindows",ANY,(uint8_t)-1,any},
		// 0x0287
		{"SalEnableAllWindows",ANY,(uint8_t)-1,any},
		// 0x0288
		{"@ArrayGetDataType",ANY,(uint8_t)-1,any},
		// 0x0289
		{"SalParseStatement",ANY,(uint8_t)-1,any},
		// 0x028a
		{"@ArraySetMDBounds",ANY,(uint8_t)-1,any},
		// 0x028b
		{"@ArrayIndex",ANY,(uint8_t)-1,any},
		// 0x028c
		{"SalDialogOpenExisting",ANY,(uint8_t)-1,any},
		// 0x028d
		{"SalOutlineFindTemplateOfClass",ANY,(uint8_t)-1,any},
		// 0x028e
		{"SalOutlineIsTemplateOfClass",ANY,(uint8_t)-1,any},
		// 0x028f
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
		{"SqlHandleSetParameters",ANY,(uint8_t)-1,any},
		// 0x0297
		{"SalLogResources",ANY,(uint8_t)-1,any},
		// 0x0298
		{"SalGetCurrentDesignWindow",ANY,(uint8_t)-1,any},
		// 0x0299
		{"@ClsUdvRefLock",ANY,(uint8_t)-1,any},
		// 0x029a
		{"HSNumStringsInUse",ANY,(uint8_t)-1,any},
		// 0x029b
		{"SalOutlineClassSize",ANY,(uint8_t)-1,any},
		// 0x029c
		{"@ArrayUDVAddress",ANY,(uint8_t)-1,any},
		// 0x029d
		{"@ClsUdvRefOfCurUdv",ANY,(uint8_t)-1,any},
		// 0x029e
		{"SalOutlineItemRemoveProperty",ANY,(uint8_t)-1,any},
		// 0x029f
		{"SalWindowRemoveProperty",ANY,(uint8_t)-1,any},
		// 0x02a0
		{"SalOutlineHighlightItem",ANY,(uint8_t)-1,any},
		// 0x02a1
		{"SqlVarSetup",ANY,(uint8_t)-1,any},
		// 0x02a2
		{"SalQOLoadCatalogTables",ANY,(uint8_t)-1,any},
		// 0x02a3
		{"SalQOReleaseTableDefs",ANY,(uint8_t)-1,any},
		// 0x02a4
		{"SalQOGetTableInfoFromIndex",ANY,(uint8_t)-1,any},
		// 0x02a5
		{"SalQOLoadTableColumns",ANY,(uint8_t)-1,any},
		// 0x02a6
		{"SalQOGetColumnInfoFromIndex",ANY,(uint8_t)-1,any},
		// 0x02a7
		{"SalQOReleaseColumnDefs",ANY,(uint8_t)-1,any},
		// 0x02a8
		{"SalOutlineBaseClassPropEditor",ANY,(uint8_t)-1,any},
		// 0x02a9
		{"SalOutlineItemSetBlob",ANY,(uint8_t)-1,any},
		// 0x02aa
		{"SalOutlineItemGetBlob",ANY,(uint8_t)-1,any},
		// 0x02ab
		{"SalOutlineUnlockBlob",ANY,(uint8_t)-1,any},
		// 0x02ac
		{"SalStrGetIdentifierInt",ANY,(uint8_t)-1,any},
		// 0x02ad
		{"SalStrGetIdentifier",ANY,(uint8_t)-1,any},
		// 0x02ae
		{"SalStaticFirst",ANY,(uint8_t)-1,any},
		// 0x02af
		{"SalStaticNext",ANY,(uint8_t)-1,any},
		// 0x02b0
		{"SalStaticGetItem",ANY,(uint8_t)-1,any},
		// 0x02b1
		{"SalStaticHide",ANY,(uint8_t)-1,any},
		// 0x02b2
		{"SalStaticShow",ANY,(uint8_t)-1,any},
		// 0x02b3
		{"SalStaticIsVisible",ANY,(uint8_t)-1,any},
		// 0x02b4
		{"SalOutlineCloseDesignEdits",ANY,(uint8_t)-1,any},
		// 0x02b5
		{"SalStaticSetLoc",ANY,(uint8_t)-1,any},
		// 0x02b6
		{"SalStaticGetLoc",ANY,(uint8_t)-1,any},
		// 0x02b7
		{"SalStaticGetSize",ANY,(uint8_t)-1,any},
		// 0x02b8
		{"SalStaticSetSize",ANY,(uint8_t)-1,any},
		// 0x02b9
		{"SalStaticGetLabel",ANY,(uint8_t)-1,any},
		// 0x02ba
		{"SalQODisplayConnectError",ANY,(uint8_t)-1,any},
		// 0x02bb
		{"SalOutlineCanInsert",ANY,(uint8_t)-1,any},
		// 0x02bc
		{"SalOutlineItemToTagged",ANY,(uint8_t)-1,any},
		// 0x02bd
		{"SalOutlineClassBaseOffset",ANY,(uint8_t)-1,any},
		// 0x02be
		{"SalOutlineVarOffset",ANY,(uint8_t)-1,any},
		// 0x02bf
		{"SalOutlineIsImportedFromDynalib",ANY,(uint8_t)-1,any},
		// 0x02c0
		{"SalOutlineItemToLibHItem",ANY,(uint8_t)-1,any},
		// 0x02c1
		{"SalSegmentSysGlobals",ANY,(uint8_t)-1,any},
		// 0x02c2
		{"SalSegmentUserGlobals",ANY,(uint8_t)-1,any},
		// 0x02c3
		{"SalDynalibGlobalVarAddr",ANY,(uint8_t)-1,any},
		// 0x02c4
		{"SalSegmentClassInstance",ANY,(uint8_t)-1,any},
		// 0x02c5
		{"SalSegmentClassStatic",ANY,(uint8_t)-1,any},
		// 0x02c6
		{"SalArrayCreateUdv",ANY,(uint8_t)-1,any},
		// 0x02c7
		{"SalOutlineIsCompiled",ANY,(uint8_t)-1,any},
		// 0x02c8
		{"SalOutlineGetNotifyItem",ANY,(uint8_t)-1,any},
		// 0x02c9
		{"SalOutlineAddNotifyWindow",ANY,(uint8_t)-1,any},
		// 0x02ca
		{"SalOutlineRemoveNotifyWindow",ANY,(uint8_t)-1,any},
		// 0x02cb
		{"SalOutlineQueryUserMode",ANY,(uint8_t)-1,any},
		// 0x02cc
		{"SalOutlineIsClassObject",ANY,(uint8_t)-1,any},
		// 0x02cd
		{"SalTblQueryColumnCellType",ANY,(uint8_t)-1,any},
		// 0x02ce
		{"SalTblDefineDropDownListColumn",ANY,(uint8_t)-1,any},
		// 0x02cf
		{"SalTblQueryDropDownListColumn",ANY,(uint8_t)-1,any},
		// 0x02d0
		{"SalTblDefinePopupEditColumn",ANY,(uint8_t)-1,any},
		// 0x02d1
		{"SalTblQueryPopupEditColumn",ANY,(uint8_t)-1,any},
		// 0x02d2
		{"SalTblDefineCheckBoxColumn",ANY,(uint8_t)-1,any},
		// 0x02d3
		{"SalTblQueryCheckBoxColumn",ANY,(uint8_t)-1,any},
		// 0x02d4
		{"SalTblQueryLinesPerRow",ANY,(uint8_t)-1,any},
		// 0x02d5
		{"SalTblSetLinesPerRow",ANY,(uint8_t)-1,any},
		// 0x02d6
		{"SalOutlineMergeIncludes",ANY,(uint8_t)-1,any},
		// 0x02d7
		{"SalLoadAppAndProcessMsgs",ANY,(uint8_t)-1,any},
		// 0x02d8
		{"SalCreateWindowEx",ANY,(uint8_t)-1,any},
		// 0x02d9
		{"SalCreateWindowExFromStr",ANY,(uint8_t)-1,any},
		// 0x02da
		{"SalOutlineShowDesignWindow",ANY,(uint8_t)-1,any},
		// 0x02db
		{"SalCDKGetChildTypeByName",ANY,(uint8_t)-1,any},
		// 0x02dc
		{"SalOutlineGetAppChanged",ANY,(uint8_t)-1,any},
		// 0x02dd
		{"SalCDKGetValidChildren",ANY,(uint8_t)-1,any},
		// 0x02de
		{"SalCDKGetChildByName",ANY,(uint8_t)-1,any},
		// 0x02df
		{"SalCDKGetName",ANY,(uint8_t)-1,any},
		// 0x02e0
		{"SqlGetLastStatement",ANY,(uint8_t)-1,any},
		// 0x02e1
		{"SalCDKParseTitle",ANY,(uint8_t)-1,any},
		// 0x02e2
		{"SalOutlineReportError",ANY,(uint8_t)-1,any},
		// 0x02e3
		{"SalOutlineInheritFromBaseClasses",ANY,(uint8_t)-1,any},
		// 0x02e4
		{"SalOutlineItemGetPropertyBuffer",ANY,(uint8_t)-1,any},
		// 0x02e5
		{"SalOutlineSelectNewItem",ANY,(uint8_t)-1,any},
		// 0x02e6
		{"SalOutlineIsUserWindow",ANY,(uint8_t)-1,any},
		// 0x02e7
		{"SalUseRegistry",ANY,(uint8_t)-1,any},
		// 0x02e8
		{"SalSetDDMErrorFun",ANY,(uint8_t)-1,any},
		// 0x02e9
		{"SalGetRegistryString",ANY,(uint8_t)-1,any},
		// 0x02ea
		{"SalSetRegistryString",ANY,(uint8_t)-1,any},
		// 0x02eb
		{"SalGetBuildSettings",ANY,(uint8_t)-1,any},
		// 0x02ec
		{"SalSetBuildSettings",ANY,(uint8_t)-1,any},
		// 0x02ed
		{"SalOutlineNotify",ANY,(uint8_t)-1,any},
		// 0x02ee
		{"SalOutlineDoUICommand",ANY,(uint8_t)-1,any},
		// 0x02ef
		{"SalOutlineCanDoUICommand",ANY,(uint8_t)-1,any},
		// 0x02f0
		{"SalOutlineGetOneUISelection",ANY,(uint8_t)-1,any},
		// 0x02f1
		{"SalIdleRegisterWindow",ANY,(uint8_t)-1,any},
		// 0x02f2
		{"SalIdleUnregisterWindow",ANY,(uint8_t)-1,any},
		// 0x02f3
		{"SalIdleKick",ANY,(uint8_t)-1,any},
		// 0x02f4
		{"SalContextMenuSetPopup",ANY,(uint8_t)-1,any},
		// 0x02f5
		{"SalTblObjectsFromPoint",ANY,(uint8_t)-1,any},
		// 0x02f6
		{"SalProfileRegisterWindow",ANY,(uint8_t)-1,any},
		// 0x02f7
		{"SalProfileUnregisterWindow",ANY,(uint8_t)-1,any},
		// 0x02f8
		{"SalPicSetHandle",ANY,(uint8_t)-1,any},
		// 0x02f9
		{"SalOutlineCreateClassFromObject",ANY,(uint8_t)-1,any},
		// 0x02fa
		{"SalOutlineOutlineOfUIFrame",ANY,(uint8_t)-1,any},
		// 0x02fb
		{"SalOutlineUIFrameOfOutline",ANY,(uint8_t)-1,any},
		// 0x02fc
		{"SalOutlineGetFirstUISelection",ANY,(uint8_t)-1,any},
		// 0x02fd
		{"SalOutlineGetNextUISelection",ANY,(uint8_t)-1,any},
		// 0x02fe
		{"SalOutlineEnableDesignScaling",ANY,(uint8_t)-1,any},
		// 0x02ff
		{"SalOutlineActivateUIView",ANY,(uint8_t)-1,any},
		// 0x0300
		{"SalOutlineIsUIViewActive",ANY,(uint8_t)-1,any},
		// 0x0301
		{"SalOutlineGetFileName",ANY,(uint8_t)-1,any},
		// 0x0302
		{"SalOutlineEditGetText",ANY,(uint8_t)-1,any},
		// 0x0303
		{"SalOutlineEditGetItem",ANY,(uint8_t)-1,any},
		// 0x0304
		{"SalOutlineEditSetText",ANY,(uint8_t)-1,any},
		// 0x0305
		{"SalOutlineGetIncludingItem",ANY,(uint8_t)-1,any},
		// 0x0306
		{"SalOutlineGetUIViewInfo",ANY,(uint8_t)-1,any},
		// 0x0307
		{"SalOutlineFirstDisplayedChild",ANY,(uint8_t)-1,any},
		// 0x0308
		{"SalOutlineNextDisplayedSibling",ANY,(uint8_t)-1,any},
		// 0x0309
		{"SalOutlineClassNameOfItem",ANY,(uint8_t)-1,any},
		// 0x030a
		{"SalResourceGet",ANY,(uint8_t)-1,any},
		// 0x030b
		{"SalResourceSet",ANY,(uint8_t)-1,any},
		// 0x030c
		{"OraPLSQLPrepare",ANY,(uint8_t)-1,any},
		// 0x030d
		{"OraPLSQLExecute",ANY,(uint8_t)-1,any},
		// 0x030e
		{"OraPLSQLStringBindType",ANY,(uint8_t)-1,any},
		// 0x030f
		{"SqlOraPLSQLPrepare",ANY,(uint8_t)-1,any},
		// 0x0310
		{"SqlOraPLSQLExecute",ANY,(uint8_t)-1,any},
		// 0x0311
		{"SqlOraPLSQLStringBindType",ANY,(uint8_t)-1,any},
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
		{"SqlGetSessionErrorInfo",ANY,(uint8_t)-1,any},
		// 0x0318
		{"SqlGetSessionHandle",ANY,(uint8_t)-1,any},
		// 0x0319
		{"SqlGetSessionParameter",ANY,(uint8_t)-1,any},
		// 0x031a
		{"SqlRollbackSession",ANY,(uint8_t)-1,any},
		// 0x031b
		{"SqlSetSessionParameter",ANY,(uint8_t)-1,any},
		// 0x031c
		{"SqlCommitSession",ANY,(uint8_t)-1,any},
		// 0x031d
		{"SqlGetStatementErrorInfo",ANY,(uint8_t)-1,any},
		// 0x031e
		{"SqlGetCmdOrRowsetPtr",ANY,(uint8_t)-1,any},
		// 0x031f
		{"SqlGetDSOrSessionPtr",ANY,(uint8_t)-1,any},
		// 0x0320
		{"__GetLastError",ANY,(uint8_t)-1,any},
		// 0x0321
		{"__ActiveXTypeVariant",ANY,(uint8_t)-1,any},
		// 0x0322
		{"__SalTypeVariant",ANY,(uint8_t)-1,any},
		// 0x0323
		{"__AsActiveXVariant",ANY,(uint8_t)-1,any},
		// 0x0324
		{"__SetBooleanVariant",ANY,(uint8_t)-1,any},
		// 0x0325
		{"__SetNumberVariant",ANY,(uint8_t)-1,any},
		// 0x0326
		{"__SetStringVariant",ANY,(uint8_t)-1,any},
		// 0x0327
		{"__SetDateVariant",ANY,(uint8_t)-1,any},
		// 0x0328
		{"__SetObject",ANY,(uint8_t)-1,any},
		// 0x0329
		{"__GetBooleanVariant",ANY,(uint8_t)-1,any},
		// 0x032a
		{"__GetNumberVariant",ANY,(uint8_t)-1,any},
		// 0x032b
		{"__GetStringVariant",ANY,(uint8_t)-1,any},
		// 0x032c
		{"__GetDateVariant",ANY,(uint8_t)-1,any},
		// 0x032d
		{"__GetObjectVariant",ANY,(uint8_t)-1,any},
		// 0x032e
		{"__MakeOptionalVariant",ANY,(uint8_t)-1,any},
		// 0x032f
		{"__CoClassCreateObjectEx",ANY,(uint8_t)-1,any},
		// 0x0330
		{"__ObjectAttach",ANY,(uint8_t)-1,any},
		// 0x0331
		{"__ObjectInvoke",ANY,(uint8_t)-1,any},
		// 0x0332
		{"__ObjectPushBoolean",ANY,(uint8_t)-1,any},
		// 0x0333
		{"__ObjectPushNumber",ANY,(uint8_t)-1,any},
		// 0x0334
		{"__ObjectPushString",ANY,(uint8_t)-1,any},
		// 0x0335
		{"__ObjectPushDate",ANY,(uint8_t)-1,any},
		// 0x0336
		{"__ObjectPushObject",ANY,(uint8_t)-1,any},
		// 0x0337
		{"__ObjectPushVariant",ANY,(uint8_t)-1,any},
		// 0x0338
		{"__ObjectPushBooleanByRef",ANY,(uint8_t)-1,any},
		// 0x0339
		{"__ObjectPushNumberByRef",ANY,(uint8_t)-1,any},
		// 0x033a
		{"__ObjectPushStringByRef",ANY,(uint8_t)-1,any},
		// 0x033b
		{"__ObjectPushDateByRef",ANY,(uint8_t)-1,any},
		// 0x033c
		{"__ObjectPushObjectByRef",ANY,(uint8_t)-1,any},
		// 0x033d
		{"__ObjectPushVariantByRef",ANY,(uint8_t)-1,any},
		// 0x033e
		{"__ObjectPopBoolean",ANY,(uint8_t)-1,any},
		// 0x033f
		{"__ObjectPopNumber",ANY,(uint8_t)-1,any},
		// 0x0340
		{"__ObjectPopString",ANY,(uint8_t)-1,any},
		// 0x0341
		{"__ObjectPopDate",ANY,(uint8_t)-1,any},
		// 0x0342
		{"__ObjectPopObject",ANY,(uint8_t)-1,any},
		// 0x0343
		{"__ObjectPopVariant",ANY,(uint8_t)-1,any},
		// 0x0344
		{"__ObjectFlushArgs",ANY,(uint8_t)-1,any},
		// 0x0345
		{"__ObjectCreateObject",ANY,(uint8_t)-1,any},
		// 0x0346
		{"__ObjectCreateObjectEx",ANY,(uint8_t)-1,any},
		// 0x0347
		{"__SafeArrayPutBooleanMD",ANY,(uint8_t)-1,any},
		// 0x0348
		{"__GetSafeArrayVariant",ANY,(uint8_t)-1,any},
		// 0x0349
		{"__SetSafeArray",ANY,(uint8_t)-1,any},
		// 0x034a
		{"__ObjectPushSafeArray",ANY,(uint8_t)-1,any},
		// 0x034b
		{"__ObjectPushSafeArrayByRef",ANY,(uint8_t)-1,any},
		// 0x034c
		{"__ObjectPopSafeArray",ANY,(uint8_t)-1,any},
		// 0x034d
		{"__SafeArrayGetBooleanMD",ANY,(uint8_t)-1,any},
		// 0x034e
		{"SalMTSGetObjectContext",ANY,(uint8_t)-1,any},
		// 0x034f
		{"__ObjectDetach",ANY,(uint8_t)-1,any},
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
		{"SalMTSIsSecurityEnabled",ANY,(uint8_t)-1,any},
		// 0x0357
		{"SalMTSIsCallerInRole",ANY,(uint8_t)-1,any},
		// 0x0358
		{"__EnumNext",ANY,(uint8_t)-1,any},
		// 0x0359
		{"__EnumSkip",ANY,(uint8_t)-1,any},
		// 0x035a
		{"__EnumReset",ANY,(uint8_t)-1,any},
		// 0x035b
		{"__EnumIsCollection",ANY,(uint8_t)-1,any},
		// 0x035c
		{"__EnumCount",ANY,(uint8_t)-1,any},
		// 0x035d
		{"__ObjectInvokeID",ANY,(uint8_t)-1,any},
		// 0x035e
		{"__CoClassGetInterface",ANY,(uint8_t)-1,any},
		// 0x035f
		{"__CoClassRelease",ANY,(uint8_t)-1,any},
		// 0x0360
		{"SalObjGetType",ANY,(uint8_t)-1,any},
		// 0x0361
		{"SalObjIsNull",ANY,(uint8_t)-1,any},
		// 0x0362
		{"SalObjCreateFromString",ANY,(uint8_t)-1,any},
		// 0x0363
		{"SalObjIsValidClassName",ANY,(uint8_t)-1,any},
		// 0x0364
		{"SalObjIsDerived",ANY,(uint8_t)-1,any},
		// 0x0365
		{"NULL",ANY,(uint8_t)-1,any},
		// 0x0366
		{"SalActiveXAutoErrorMode",ANY,(uint8_t)-1,any},
		// 0x0367
		{"SalActiveXCreate",ANY,(uint8_t)-1,any},
		// 0x0368
		{"SalActiveXGetActiveObject",ANY,(uint8_t)-1,any},
		// 0x0369
		{"SalActiveXGetObject",ANY,(uint8_t)-1,any},
		// 0x036a
		{"SalActiveXDoVerb",ANY,(uint8_t)-1,any},
		// 0x036b
		{"SalActiveXClose",ANY,(uint8_t)-1,any},
		// 0x036c
		{"SalActiveXInsertObjectDlg",ANY,(uint8_t)-1,any},
		// 0x036d
		{"SalActiveXOLEType",ANY,(uint8_t)-1,any},
		// 0x036e
		{"SalActiveXGetData",ANY,(uint8_t)-1,any},
		// 0x036f
		{"SalActiveXCreateFromData",ANY,(uint8_t)-1,any},
		// 0x0370
		{"SalActiveXDelete",ANY,(uint8_t)-1,any},
		// 0x0371
		{"SalActiveXCreateFromFile",ANY,(uint8_t)-1,any},
		// 0x0372
		{"__CoClassCreateObject",ANY,(uint8_t)-1,any},
		// 0x0373
		{"__SafeArrayCreateMD",ANY,(uint8_t)-1,any},
		// 0x0374
		{"__SafeArrayGetLowerBoundMD",ANY,(uint8_t)-1,any},
		// 0x0375
		{"__SafeArrayGetUpperBoundMD",ANY,(uint8_t)-1,any},
		// 0x0376
		{"__SafeArrayGetNumberMD",ANY,(uint8_t)-1,any},
		// 0x0377
		{"__SafeArrayPutNumberMD",ANY,(uint8_t)-1,any},
		// 0x0378
		{"__SafeArrayGetDateMD",ANY,(uint8_t)-1,any},
		// 0x0379
		{"__SafeArrayPutDateMD",ANY,(uint8_t)-1,any},
		// 0x037a
		{"__SafeArrayGetObjectMD",ANY,(uint8_t)-1,any},
		// 0x037b
		{"__SafeArrayPutObjectMD",ANY,(uint8_t)-1,any},
		// 0x037c
		{"__SafeArrayGetStringMD",ANY,(uint8_t)-1,any},
		// 0x037d
		{"__SafeArrayPutStringMD",ANY,(uint8_t)-1,any},
		// 0x037e
		{"__SafeArrayGetVariantMD",ANY,(uint8_t)-1,any},
		// 0x037f
		{"__SafeArrayPutVariantMD",ANY,(uint8_t)-1,any},
		// 0x0380
		{"SalSetErrorInfo",ANY,(uint8_t)-1,any},
		// 0x0381
		{"SqlPrepareSP",ANY,(uint8_t)-1,any},
		// 0x0382
		{"SqlGetNextSPResultSet",ANY,(uint8_t)-1,any},
		// 0x0383
		{"SqlCloseAllSPResultSets",ANY,(uint8_t)-1,any},
		// 0x0384
		{"SalWindowGetDockSetting",ANY,(uint8_t)-1,any},
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
		// 0x038a
		{"SalStartTrace",ANY,(uint8_t)-1,any},
		// 0x038b
		{"SalTrace",ANY,(uint8_t)-1,any},
		// 0x038c
		{"SalEndTrace",ANY,(uint8_t)-1,any},
		// 0x038d
		{"SalComCleanupMode",ANY,(uint8_t)-1,any},
		// 0x038e
		{"SalTblWriteXMLandSchema",ANY,(uint8_t)-1,any},
		// 0x038f
		{"SalTblSetColumnXMLAttributes",ANY,(uint8_t)-1,any},
		// 0x0390
		{"SalTblCreateColumnEx",ANY,(uint8_t)-1,any},
		// 0x0391
		{"SalTblPopulateFromXML",ANY,(uint8_t)-1,any},
		// 0x0392
		{"SalTblWriteXMLandSchemaEx",ANY,(uint8_t)-1,any},
		// 0x0393
		{"SalTblSetFromXMLSchema",ANY,(uint8_t)-1,any},
		// 0x0394
		{"SalReportGetFileInfo",ANY,(uint8_t)-1,any},
		// 0x0395
		{"SqlGetCommandText",ANY,(uint8_t)-1,any},
		// 0x0396
		{"SalReportResetPages",ANY,(uint8_t)-1,any},
		// 0x0397
		{"__XML_Document_LoadFromURI",ANY,(uint8_t)-1,any},
		// 0x0398
		{"__XML_Document_LoadFromString",ANY,(uint8_t)-1,any},
		// 0x0399
		{"__XML_Node_nodeName",ANY,(uint8_t)-1,any},
		// 0x039a
		{"__XML_Node_appendChild",ANY,(uint8_t)-1,any},
		// 0x039b
		{"__XML_Node_cloneNode",ANY,(uint8_t)-1,any},
		// 0x039c
		{"__XML_Node_firstChild",ANY,(uint8_t)-1,any},
		// 0x039d
		{"__XML_Node_hasChildNodes",ANY,(uint8_t)-1,any},
		// 0x039e
		{"__XML_Node_insertBefore",ANY,(uint8_t)-1,any},
		// 0x039f
		{"__XML_Node_lastChild",ANY,(uint8_t)-1,any},
		// 0x03a0
		{"__XML_Node_nextSibling",ANY,(uint8_t)-1,any},
		// 0x03a1
		{"__XML_Node_nodeType",ANY,(uint8_t)-1,any},
		// 0x03a2
		{"__XML_Node_nodeValue",ANY,(uint8_t)-1,any},
		// 0x03a3
		{"__XML_Node_ownerDocument",ANY,(uint8_t)-1,any},
		// 0x03a4
		{"__XML_Node_parentNode",ANY,(uint8_t)-1,any},
		// 0x03a5
		{"__XML_Node_previousSibling",ANY,(uint8_t)-1,any},
		// 0x03a6
		{"__XML_Node_removeChild",ANY,(uint8_t)-1,any},
		// 0x03a7
		{"__XML_Node_replaceChild",ANY,(uint8_t)-1,any},
		// 0x03a8
		{"__XML_Node_childNodes",ANY,(uint8_t)-1,any},
		// 0x03a9
		{"__XML_Node_attributes",ANY,(uint8_t)-1,any},
		// 0x03aa
		{"__XML_Element_getAttribute",ANY,(uint8_t)-1,any},
		// 0x03ab
		{"__XML_Element_getAttributeNode",ANY,(uint8_t)-1,any},
		// 0x03ac
		{"__XML_Element_getElementsByTagName",ANY,(uint8_t)-1,any},
		// 0x03ad
		{"__XML_Element_removeAttribute",ANY,(uint8_t)-1,any},
		// 0x03ae
		{"__XML_Element_setAttribute",ANY,(uint8_t)-1,any},
		// 0x03af
		{"__XML_Element_removeAttributeNode",ANY,(uint8_t)-1,any},
		// 0x03b0
		{"__XML_Element_setAttributeNode",ANY,(uint8_t)-1,any},
		// 0x03b1
		{"__XML_Document_createAttribute",ANY,(uint8_t)-1,any},
		// 0x03b2
		{"__XML_Document_createCDATASection",ANY,(uint8_t)-1,any},
		// 0x03b3
		{"__XML_Document_createComment",ANY,(uint8_t)-1,any},
		// 0x03b4
		{"__XML_Document_createDocumentFragment",ANY,(uint8_t)-1,any},
		// 0x03b5
		{"__XML_Document_createElement",ANY,(uint8_t)-1,any},
		// 0x03b6
		{"__XML_Document_createEntityReference",ANY,(uint8_t)-1,any},
		// 0x03b7
		{"__XML_Document_createProcessingInstruction",ANY,(uint8_t)-1,any},
		// 0x03b8
		{"__XML_Document_createTextNode",ANY,(uint8_t)-1,any},
		// 0x03b9
		{"__XML_Document_documentElement",ANY,(uint8_t)-1,any},
		// 0x03ba
		{"__XML_Document_documentType",ANY,(uint8_t)-1,any},
		// 0x03bb
		{"__XML_Document_setOutputEncoding",ANY,(uint8_t)-1,any},
		// 0x03bc
		{"__XML_Document_setFeature",ANY,(uint8_t)-1,any},
		// 0x03bd
		{"__XML_Node_changeType",ANY,(uint8_t)-1,any},
		// 0x03be
		{"__XML_CDATA_getCDATAbase64",ANY,(uint8_t)-1,any},
		// 0x03bf
		{"__XML_CDATA_setCDATAbase64",ANY,(uint8_t)-1,any},
		// 0x03c0
		{"__XML_Node_writeToString",ANY,(uint8_t)-1,any},
		// 0x03c1
		{"__XML_Document_writeToFile",ANY,(uint8_t)-1,any},
		// 0x03c2
		{"__XML_CharacterData_setData",ANY,(uint8_t)-1,any},
		// 0x03c3
		{"__XML_CharacterData_getData",ANY,(uint8_t)-1,any},
		// 0x03c4
		{"__XML_CharacterData_substringData",ANY,(uint8_t)-1,any},
		// 0x03c5
		{"__XML_CharacterData_appendData",ANY,(uint8_t)-1,any},
		// 0x03c6
		{"__XML_CharacterData_insertData",ANY,(uint8_t)-1,any},
		// 0x03c7
		{"__XML_CharacterData_deleteData",ANY,(uint8_t)-1,any},
		// 0x03c8
		{"__XML_CharacterData_replaceData",ANY,(uint8_t)-1,any},
		// 0x03c9
		{"__XML_Entity_getPublicId",ANY,(uint8_t)-1,any},
		// 0x03ca
		{"__XML_Entity_getSystemId",ANY,(uint8_t)-1,any},
		// 0x03cb
		{"__XML_Entity_getNotationName",ANY,(uint8_t)-1,any},
		// 0x03cc
		{"__XML_DocumentType_getEntities",ANY,(uint8_t)-1,any},
		// 0x03cd
		{"__XML_DocumentType_getNotations",ANY,(uint8_t)-1,any},
		// 0x03ce
		{"__XML_DocumentType_getInternalSubset",ANY,(uint8_t)-1,any},
		// 0x03cf
		{"__XML_Attr_getOwnerElement",ANY,(uint8_t)-1,any},
		// 0x03d0
		{"__XML_Attr_getSpecified",ANY,(uint8_t)-1,any},
		// 0x03d1
		{"__XML_ProcessingInstruction_getTarget",ANY,(uint8_t)-1,any},
		// 0x03d2
		{"__XML_CharacterData_getLength",ANY,(uint8_t)-1,any},
		// 0x03d3
		{"__XML_CDATA_getCDATAbase64Length",ANY,(uint8_t)-1,any},
		// 0x03d4
		{"__XML_Text_isIgnorableWhitespace",ANY,(uint8_t)-1,any},
		// 0x03d5
		{"__XML_Text_splitText",ANY,(uint8_t)-1,any},
		// 0x03d6
		{"__XML_Document_getElementById",ANY,(uint8_t)-1,any},
		// 0x03d7
		{"__XML_Document_createNewDoc",ANY,(uint8_t)-1,any},
		// 0x03d8
		{"__XML_Node_setNodeValue",ANY,(uint8_t)-1,any},
		// 0x03d9
		{"__XML_Document_getEncoding",ANY,(uint8_t)-1,any},
		// 0x03da
		{"__XML_Document_create",ANY,(uint8_t)-1,any},
		// 0x03db
		{"__XML_Document_release",ANY,(uint8_t)-1,any},
		// 0x03dc
		{"__XML_Document_getLastError",ANY,(uint8_t)-1,any},
		// 0x03dd
		{"__XML_Document_getURI",ANY,(uint8_t)-1,any},
		// 0x03de
		{"__XML_Document_getFeature",ANY,(uint8_t)-1,any},
		// 0x03df
		{"__XML_Element_getTagName",ANY,(uint8_t)-1,any},
		// 0x03e0
		{"__XML_Document_schemaDef",ANY,(uint8_t)-1,any},
		// 0x03e1
		{"__XML_Document_schemaDatatype",ANY,(uint8_t)-1,any},
		// 0x03e2
		{"__XML_Node_getTextContent",ANY,(uint8_t)-1,any},
		// 0x03e3
		{"__XML_Node_setTextContent",ANY,(uint8_t)-1,any},
		// 0x03e4
		{"__XML_Node_getLocalName",ANY,(uint8_t)-1,any},
		// 0x03e5
		{"__XML_Node_getPrefix",ANY,(uint8_t)-1,any},
		// 0x03e6
		{"__XML_Node_getNamespaceURI",ANY,(uint8_t)-1,any},
		// 0x03e7
		{"__XML_Node_isDefaultNamespace",ANY,(uint8_t)-1,any},
		// 0x03e8
		{"__XML_Node_SqlSelectForNode",ANY,(uint8_t)-1,any},
		// 0x03e9
		{"__XML_Node_SqlSchemaForNode",ANY,(uint8_t)-1,any},
		// 0x03ea
		{"__XML_Node_hasAttributes",ANY,(uint8_t)-1,any},
		// 0x03eb
		{"SalReportSetPrinterTray",ANY,(uint8_t)-1,any},
		// 0x03ec
		{"SalReportSetPrinterSettings",ANY,(uint8_t)-1,any},
		// 0x03ed
		{"SalReportGetPrinterSettings",ANY,(uint8_t)-1,any},
		// 0x03ee
		{"SalEventLogSetName",ANY,(uint8_t)-1,any},
		// 0x03ef
		{"SalReportGetPrinterTray",ANY,(uint8_t)-1,any},
		// 0x03f0
		{"SalXMLGetLastError",ANY,(uint8_t)-1,any},
		// 0x03f1
		{"SalXMLSerializeUDV",ANY,(uint8_t)-1,any},
		// 0x03f2
		{"SalXMLDeserializeUDV",ANY,(uint8_t)-1,any},
		// 0x03f3
		{"__XML_Node_release",ANY,(uint8_t)-1,any},
		// 0x03f4
		{"__XML_Element_hasAttribute",ANY,(uint8_t)-1,any},
		// 0x03f5
		{"__HTTP_Send",ANY,(uint8_t)-1,any},
		// 0x03f6
		{"__HTTP_SetHTTPHeader",ANY,(uint8_t)-1,any},
		// 0x03f7
		{"__HTTP_GetResponseText",ANY,(uint8_t)-1,any},
		// 0x03f8
		{"__HTTP_GetResponseXML",ANY,(uint8_t)-1,any},
		// 0x03f9
		{"__HTTP_GetResponseHeader",ANY,(uint8_t)-1,any},
		// 0x03fa
		{"__HTTP_GetAllResponseHeaders",ANY,(uint8_t)-1,any},
		// 0x03fb
		{"__HTTP_Open",ANY,(uint8_t)-1,any},
		// 0x03fc
		{"__HTTP_SendXML",ANY,(uint8_t)-1,any},
		// 0x03fd
		{"__HTTP_GetLastError",ANY,(uint8_t)-1,any},
		// 0x03fe
		{"__HTTP_SetTimeOut",ANY,(uint8_t)-1,any},
		// 0x03ff
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
		{"SalOutlineItemSetPropertyBuffer",ANY,(uint8_t)-1,any},
		// 0x0407
		{"SalTabHidePage",ANY,(uint8_t)-1,any},
		// 0x0408
		{"SalTabShowPage",ANY,(uint8_t)-1,any},
		// 0x0409
		{"SalWindowSetPropertyBuffer",ANY,(uint8_t)-1,any},
		// 0x040a
		{"SalGetMenu",ANY,(uint8_t)-1,any},
		// 0x040b
		{"SalMenuUpdate",ANY,(uint8_t)-1,any},
		// 0x040c
		{"SalSetBufferLength",ANY,(uint8_t)-1,any},
		// 0x040d
		{"SalGetBufferLength",ANY,(uint8_t)-1,any},
		// 0x040e
		{"SalGridSetCellType",ANY,(uint8_t)-1,any},
		// 0x040f
		{"SalGridSetCellProp",ANY,(uint8_t)-1,any},
		// 0x0410
		{"SalOutlineLoadSuppressIncludes",ANY,(uint8_t)-1,any},
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
		// 0x041a
		{"SalTabDisassociateChild",ANY,(uint8_t)-1,any},
		// 0x041b
		{"SalTabSetActivePage",ANY,(uint8_t)-1,any},
		// 0x041c
		{"SalTabEnablePage",ANY,(uint8_t)-1,any},
		// 0x041d
		{"SalTabDisablePage",ANY,(uint8_t)-1,any},
		// 0x041e
		{"SalTabGetPageTitle",ANY,(uint8_t)-1,any},
		// 0x041f
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
		{"SalRTFTextGetAlignment",ANY,(uint8_t)-1,any},
		// 0x0427
		{"SalRTFTextGetSpacing",ANY,(uint8_t)-1,any},
		// 0x0428
		{"SalRTFTextGetColor",ANY,(uint8_t)-1,any},
		// 0x0429
		{"SalRTFTextSetColor",ANY,(uint8_t)-1,any},
		// 0x042a
		{"SalRTFTextGetStyle",ANY,(uint8_t)-1,any},
		// 0x042b
		{"SalRTFTextSetStyle",ANY,(uint8_t)-1,any},
		// 0x042c
		{"SalRTFTextGetSelected",ANY,(uint8_t)-1,any},
		// 0x042d
		{"SalRTFTextSelect",ANY,(uint8_t)-1,any},
		// 0x042e
		{"SalRTFTextSelectAll",ANY,(uint8_t)-1,any},
		// 0x042f
		{"SalRTFTextReplace",ANY,(uint8_t)-1,any},
		// 0x0430
		{"SalRTFParagraphSetAlignment",ANY,(uint8_t)-1,any},
		// 0x0431
		{"SalRTFParagraphGetSetting",ANY,(uint8_t)-1,any},
		// 0x0432
		{"SalRTFParagraphSetSetting",ANY,(uint8_t)-1,any},
		// 0x0433
		{"SalRTFParagraphSetSpacing",ANY,(uint8_t)-1,any},
		// 0x0434
		{"SalRTFDocumentInsert",ANY,(uint8_t)-1,any},
		// 0x0435
		{"SalRTFDocumentLineCount",ANY,(uint8_t)-1,any},
		// 0x0436
		{"SalRTFDocumentLineLength",ANY,(uint8_t)-1,any},
		// 0x0437
		{"SalRTFDocumentPageCount",ANY,(uint8_t)-1,any},
		// 0x0438
		{"SalRTFDocumentGetPosition",ANY,(uint8_t)-1,any},
		// 0x0439
		{"SalGridGetColumnType",ANY,(uint8_t)-1,any},
		// 0x043a
		{"SalRTFDocumentPictureInsert",ANY,(uint8_t)-1,any},
		// 0x043b
		{"SalRTFDocumentPreview",ANY,(uint8_t)-1,any},
		// 0x043c
		{"SalRTFDocumentPrint",ANY,(uint8_t)-1,any},
		// 0x043d
		{"SalRTFDocumentSave",ANY,(uint8_t)-1,any},
		// 0x043e
		{"SalRTFCtrlIsPreview",ANY,(uint8_t)-1,any},
		// 0x043f
		{"SalReportPrintToFileEx",ANY,(uint8_t)-1,any},
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
		{"SalSetActiveRibbonPage",ANY,(uint8_t)-1,any},
		// 0x0448
		{"SalTabUpdate",ANY,(uint8_t)-1,any},
		// 0x0449
		{"SalCharToMultiByte",ANY,(uint8_t)-1,any},
		// 0x044a
		{"SalCharToWideChar",ANY,(uint8_t)-1,any},
		// 0x044b
		{"SalGridSetCellPicture",ANY,(uint8_t)-1,any},
		// 0x044c
		{"SalHtmlHelp",ANY,(uint8_t)-1,any},
		// 0x044d
		{"SalBtnSetProperties",ANY,(uint8_t)-1,any},
		// 0x044e
		{"SalBtnSetImageAlign",ANY,(uint8_t)-1,any},
		// 0x044f
		{"SalBtnSetTextAlign",ANY,(uint8_t)-1,any},
		// 0x0450
		{"SalBtnSetTextImageRelation",ANY,(uint8_t)-1,any},
		// 0x0451
		{"SalBtnGetProperties",ANY,(uint8_t)-1,any},
		// 0x0452
		{"SalBtnGetImageAlign",ANY,(uint8_t)-1,any},
		// 0x0453
		{"SalBtnGetTextAlign",ANY,(uint8_t)-1,any},
		// 0x0454
		{"SalBtnGetTextImageRelation",ANY,(uint8_t)-1,any},
		// 0x0455
		{"SalReportGetRichTextVar",ANY,(uint8_t)-1,any},
		// 0x0456
		{"SalReportSetRichTextVar",ANY,(uint8_t)-1,any},
		// 0x0457
		{"SalOutlineSaveConvertTables",ANY,(uint8_t)-1,any},
		// 0x0458
		{"SalRTFTableInsert",ANY,(uint8_t)-1,any},
		// 0x0459
		{"SalGridSortRowsMultiColumn",ANY,(uint8_t)-1,any},
		// 0x045a
		{"SqlWriteConnectionString",ANY,(uint8_t)-1,any},
		// 0x045b
		{"SqlGetConnectionStrings",ANY,(uint8_t)-1,any},
		// 0x045c
		{"SqlDeleteConnectionString",ANY,(uint8_t)-1,any},
		// 0x045d
		{"SqlListConnections",ANY,(uint8_t)-1,any},
		// 0x045e
		{"SqlFindIniFile",ANY,(uint8_t)-1,any},
		// 0x045f
		{"SalSetTooltip",ANY,(uint8_t)-1,any},
		// 0x0460
		{"SalGetTooltip",ANY,(uint8_t)-1,any},
		// 0x0461
		{"SalGetActiveRibbonPage",ANY,(uint8_t)-1,any},
		// 0x0462
		{"SalFileOpenCP",ANY,(uint8_t)-1,any},
		// 0x0463
		{"SalDlgSetDockSlide",ANY,(uint8_t)-1,any},
		// 0x0464
		{"SalDlgGetDockSlide",ANY,(uint8_t)-1,any},
		// 0x0465
		{"SalWindowWriteDockState",ANY,(uint8_t)-1,any},
		// 0x0466
		{"SalWindowApplyDockState",ANY,(uint8_t)-1,any},
		// 0x0467
		{"SalDlgSetDockStatusEx",ANY,(uint8_t)-1,any},
		// 0x0468
		{"SalRTFTextSetFont",ANY,(uint8_t)-1,any},
		// 0x0469
		{"SalRTFShowToolBar",ANY,(uint8_t)-1,any},
		// 0x046a
		{"SalRTFShowToolBarButton",ANY,(uint8_t)-1,any},
		// 0x046b
		{"SalDlgSetDockTabAt",ANY,(uint8_t)-1,any},
		// 0x046c
		{"SalTblCreateColumnFromClass",ANY,(uint8_t)-1,any},
		// 0x046d
		{"SalTreeInsertItem",ANY,(uint8_t)-1,any},
		// 0x046e
		{"SalTreeSetSelectedItem",ANY,(uint8_t)-1,any},
		// 0x046f
		{"SalTreeExpandItem",ANY,(uint8_t)-1,any},
		// 0x0470
		{"SalTreeCollapseItem",ANY,(uint8_t)-1,any},
		// 0x0471
		{"SalTreeEditItem",ANY,(uint8_t)-1,any},
		// 0x0472
		{"SalTreeSetItemEditable",ANY,(uint8_t)-1,any},
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
		{"SalTreeGetSelectedItem",ANY,(uint8_t)-1,any},
		// 0x047a
		{"SalTreeFindItemByTitle",ANY,(uint8_t)-1,any},
		// 0x047b
		{"SalTreeGetItemParent",ANY,(uint8_t)-1,any},
		// 0x047c
		{"SalTreeItemIsExpanded",ANY,(uint8_t)-1,any},
		// 0x047d
		{"SalTreeItemIsSelected",ANY,(uint8_t)-1,any},
		// 0x047e
		{"SalTreeSetItemImage",ANY,(uint8_t)-1,any},
		// 0x047f
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
		{"SalTreeSetItemTextColor",ANY,(uint8_t)-1,any},
		// 0x0485
		{"SalTreeSetItemFontEnh",ANY,(uint8_t)-1,any},
		// 0x0486
		{"SalTreeEnableItem",ANY,(uint8_t)-1,any},
		// 0x0487
		{"SalTreeSetItemChecked",ANY,(uint8_t)-1,any},
		// 0x0488
		{"SalTreeItemIsChecked",ANY,(uint8_t)-1,any},
		// 0x0489
		{"SalTreeItemHasCheckbox",ANY,(uint8_t)-1,any},
		// 0x048a
		{"SalTreeShowItemCheckbox",ANY,(uint8_t)-1,any},
		// 0x048b
		{"SalTreeSetItemText",ANY,(uint8_t)-1,any},
		// 0x048c
		{"SalNavPaneIsEnabled",ANY,(uint8_t)-1,any},
		// 0x048d
		{"SalNavEnablePane",ANY,(uint8_t)-1,any},
		// 0x048e
		{"SalNavGetPaneTitle",ANY,(uint8_t)-1,any},
		// 0x048f
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
		{"SalNavDisassociateChild",ANY,(uint8_t)-1,any},
		// 0x049a
		{"SalNavGroupIsExpanded",ANY,(uint8_t)-1,any},
		// 0x049b
		{"SalNavExpandGroup",ANY,(uint8_t)-1,any},
		// 0x049c
		{"SalGridDataExport",ANY,(uint8_t)-1,any},
		// 0x049d
		{"SalTabSetTooltip",ANY,(uint8_t)-1,any},
		// 0x049e
		{"SalTabGetTooltip",ANY,(uint8_t)-1,any},
		// 0x049f
		{"SalTabSetPageTitle",ANY,(uint8_t)-1,any},
		// 0x04a0
		{"SalTabHideStrip",ANY,(uint8_t)-1,any},
		// 0x04a1
		{"SalTabShowStrip",ANY,(uint8_t)-1,any},
		// 0x04a2
		{"SalTabAttachWindow",ANY,(uint8_t)-1,any},
		// 0x04a3
		{"SalTabDetachWindow",ANY,(uint8_t)-1,any},
		// 0x04a4
		{"SalTabGetPageWindow",ANY,(uint8_t)-1,any},
		// 0x04a5
		{"SalGridGetHeader",ANY,(uint8_t)-1,any},
		// 0x04a6
		{"SalGridGetFooter",ANY,(uint8_t)-1,any},
		// 0x04a7
		{"SalGridSetHeader",ANY,(uint8_t)-1,any},
		// 0x04a8
		{"SalGridSetFooter",ANY,(uint8_t)-1,any},
		// 0x04a9
		{"SalCreateToolbar",ANY,(uint8_t)-1,any},
		// 0x04aa
		{"SalGridDataImport",ANY,(uint8_t)-1,any},
		// 0x04ab
		{"SalWPFInvokeMethod",ANY,(uint8_t)-1,any},
		// 0x04ac
		{"SalWPFGetBoolProperty",ANY,(uint8_t)-1,any},
		// 0x04ad
		{"SalWPFSetBoolProperty",ANY,(uint8_t)-1,any},
		// 0x04ae
		{"SalWPFGetDateProperty",ANY,(uint8_t)-1,any},
		// 0x04af
		{"SalWPFSetDateProperty",ANY,(uint8_t)-1,any},
		// 0x04b0
		{"SalWPFGetNumericProperty",ANY,(uint8_t)-1,any},
		// 0x04b1
		{"SalWPFSetNumericProperty",ANY,(uint8_t)-1,any},
		// 0x04b2
		{"SalWPFGetStrProperty",ANY,(uint8_t)-1,any},
		// 0x04b3
		{"SalWPFSetStrProperty",ANY,(uint8_t)-1,any},
		// 0x04b4
		{"SalNavSetPaneIcon",ANY,(uint8_t)-1,any},
		// 0x04b5
		{"SalNavGetPaneIcon",ANY,(uint8_t)-1,any},
		// 0x04b6
		{"SalGridSetAltRowBackColors",ANY,(uint8_t)-1,any},
		// 0x04b7
		{"SalNetCompileAndEvaluate",ANY,(uint8_t)-1,any},
		// 0x04b8
		{"SalDateWeekNumber",ANY,(uint8_t)-1,any},
		// 0x04b9
		{"SalTreeReset",ANY,(uint8_t)-1,any},
		// 0x04ba
		{"SalTreeItemFromPoint",ANY,(uint8_t)-1,any},
		// 0x04bb
		{"SalIsDotNet",ANY,(uint8_t)-1,any},
		// 0x04bc
		{"SalNavAddGroup",ANY,(uint8_t)-1,any},
		// 0x04bd
		{"SalGridSummaryBar",ANY,(uint8_t)-1,any},
		// 0x04be
		{"SalGridSetSummaryColumn",ANY,(uint8_t)-1,any},
		// 0x04bf
		{"SalTblColumnMinMax",ANY,(uint8_t)-1,any},
		// 0x04c0
		{"SalTblColumnAverageDate",ANY,(uint8_t)-1,any},
		// 0x04c1
		{"SalTblColumnMinMaxDate",ANY,(uint8_t)-1,any},
		// 0x04c2
		{"SalGridSetSummaryColumnLabel",ANY,(uint8_t)-1,any},
		// 0x04c3
		{"SalNumberToCharASCII",ANY,(uint8_t)-1,any},
		// 0x04c4
		{"SalStrLopASCII",ANY,(uint8_t)-1,any},
		// 0x04c5
		{"SalStrFirstCASCII",ANY,(uint8_t)-1,any},
		// 0x04c6
		{"SalTblDefineRadioButtonColumn",ANY,(uint8_t)-1,any},
		// 0x04c7
		{"SalRibbonMaximize",ANY,(uint8_t)-1,any},
		// 0x04c8
		{"SalRibbonMinimize",ANY,(uint8_t)-1,any},
		// 0x04c9
		{"SalGridSetRowHeight",ANY,(uint8_t)-1,any},
		// 0x04ca
		{"SalTabGetPageName",ANY,(uint8_t)-1,any},
		// 0x04cb
		{"SalTabAddPageEx",ANY,(uint8_t)-1,any},
		// 0x04cc
		{"SalDictionaryPromote",ANY,(uint8_t)-1,any},
		// 0x04cd
		{"SalThrowSoapFault",ANY,(uint8_t)-1,any},
		// 0x04ce
		{"SalTreeSetItemImageFromResource",ANY,(uint8_t)-1,any},
		// 0x04cf
		{"SalNavAddPaneEx",ANY,(uint8_t)-1,any},
		// 0x04d0
		{"SalNavSetPaneIconFromResource",ANY,(uint8_t)-1,any},
		// 0x04d1
		{"SalWSSetCredentials",ANY,(uint8_t)-1,any},
		// 0x04d2
		{"SalDictionaryLookupString",ANY,(uint8_t)-1,any},
		// 0x04d3
		{"SqlConnectDotNet",ANY,(uint8_t)-1,any},
		// 0x04d4
		{"SalTblColumnCountNotNull",ANY,(uint8_t)-1,any},
		// 0x04d5
		{"SalGridSummaryBarRefresh",ANY,(uint8_t)-1,any},
		// 0x04d6
		{"SalTreeMoveDownItem",ANY,(uint8_t)-1,any},
		// 0x04d7
		{"SalTreeMoveUpItem",ANY,(uint8_t)-1,any},
		// 0x04d8
		{"SalTreePromoteItem",ANY,(uint8_t)-1,any},
		// 0x04d9
		{"SalTreeDemoteItem",ANY,(uint8_t)-1,any},
		// 0x04da
		{"SalTreeDragDropItem",ANY,(uint8_t)-1,any},
		// 0x04db
		{"SalSetLanguageID",ANY,(uint8_t)-1,any},
		// 0x04dc
		{"SalGridSetSummaryColumnValue",ANY,(uint8_t)-1,any},
		// 0x04dd
		{"SalGridDataExportEx",ANY,(uint8_t)-1,any},
		// 0x04de
		{"SalTBGetDockStatus",ANY,(uint8_t)-1,any},
		// 0x04df
		{"SalTBSetDockStatus",ANY,(uint8_t)-1,any},
		// 0x04e0
		{"SalSetPaintMode",ANY,(uint8_t)-1,any},
		// 0x04e1
		{"SalGetLastException",ANY,(uint8_t)-1,any},
		// 0x04e2
		{"SalTreeFindItemByData",ANY,(uint8_t)-1,any},
		// 0x04e3
		{"SalActiveXSaveFile",ANY,(uint8_t)-1,any},
		// 0x04e4
		{"SalTreeMoveItem",ANY,(uint8_t)-1,any},
		// 0x04e5
		{"SalStringToBinary",ANY,(uint8_t)-1,any},
		// 0x04e6
		{"SalBinaryToString",ANY,(uint8_t)-1,any},
		// 0x04e7
		{"SalDateToUTCTime",ANY,(uint8_t)-1,any},
		// 0x04e8
		{"SalDateToLocalTime",ANY,(uint8_t)-1,any},
		// 0x04e9
		{"SalDictionaryLoad",ANY,(uint8_t)-1,any},
		// 0x04ea
		{"SalTblSetCellBackColor",ANY,(uint8_t)-1,any},
		// 0x04eb
		{"SalIsValidDateTimeExact",ANY,(uint8_t)-1,any},
		// 0x04ec
		{"SalPicPaintAsBkgd",ANY,(uint8_t)-1,any},
		// 0x04ed
		{"SalDlgOpenFileMulti",ANY,(uint8_t)-1,any},
		// 0x04ee
		{"SalTreeSetItemImageFromBinary",ANY,(uint8_t)-1,any},
		// 0x04ef
		{"SalEnableFastChars",ANY,(uint8_t)-1,any},
		// 0x04f0
		{"SalGridWriteState",ANY,(uint8_t)-1,any},
		// 0x04f1
		{"SalGridApplyState",ANY,(uint8_t)-1,any},
		// 0x04f2
		{"SalRibbonGetState",ANY,(uint8_t)-1,any},
		// 0x04f3
		{"SalTabSetPageIcon",ANY,(uint8_t)-1,any},
		// 0x04f4
		{"SalMeterGetRange",ANY,(uint8_t)-1,any},
		// 0x04f5
		{"SalMeterSetRange",ANY,(uint8_t)-1,any},
		// 0x04f6
		{"SalMeterGetFromColor",ANY,(uint8_t)-1,any},
		// 0x04f7
		{"SalMeterSetFromColor",ANY,(uint8_t)-1,any},
		// 0x04f8
		{"SalMeterGetToColor",ANY,(uint8_t)-1,any},
		// 0x04f9
		{"SalMeterSetToColor",ANY,(uint8_t)-1,any},
		// 0x04fa
		{"SalMeterGetStepSize",ANY,(uint8_t)-1,any},
		// 0x04fb
		{"SalMeterSetStepSize",ANY,(uint8_t)-1,any},
		// 0x04fc
		{"SalMeterGetSmooth",ANY,(uint8_t)-1,any},
		// 0x04fd
		{"SalMeterSetSmooth",ANY,(uint8_t)-1,any},
		// 0x04fe
		{"SalMeterGetVertical",ANY,(uint8_t)-1,any},
		// 0x04ff
		{"SalMeterSetVertical",ANY,(uint8_t)-1,any},
		// 0x0500
		{"SalMeterStepUp",ANY,(uint8_t)-1,any},
		// 0x0501
		{"SalMeterStepDown",ANY,(uint8_t)-1,any},
		// 0x0502
		{"SqlDbPipeSetRequestHeader",ANY,(uint8_t)-1,any},
		// 0x0503
		{"SqlDbPipeFetchResponseHeader",ANY,(uint8_t)-1,any},
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
		// 0x050a
		{"SalGetEnvironment",ANY,(uint8_t)-1,any},
		// 0x050b
		{"SalTBGetItemCount",ANY,(uint8_t)-1,any},
		// 0x050c
		{"SalTBSetItemColor",ANY,(uint8_t)-1,any},
		// 0x050d
		{"SalWSSetEndpointAddress",ANY,(uint8_t)-1,any},
		// 0x050e
		{"SalGetLastExceptionField",ANY,(uint8_t)-1,any},
		// 0x050f
		{"SalRibbonSetItemCaption",ANY,(uint8_t)-1,any},
		// 0x0510
		{"SalRibbonGetItemCaption",ANY,(uint8_t)-1,any},
		// 0x0511
		{"SalRibbonSetItemEnabled",ANY,(uint8_t)-1,any},
		// 0x0512
		{"SalRibbonGetItemEnabled",ANY,(uint8_t)-1,any},
		// 0x0513
		{"SalRibbonSetItemChecked",ANY,(uint8_t)-1,any},
		// 0x0514
		{"SalRibbonGetItemChecked",ANY,(uint8_t)-1,any},
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
		// 0x051a
		{"SalTBHideItem",ANY,(uint8_t)-1,any},
		// 0x051b
		{"SalTBShowItem",ANY,(uint8_t)-1,any},
		// 0x051c
		{"SalOutlineItemTypeTextDisplay",ANY,(uint8_t)-1,any},
		// 0x051d
		{"SqlConnectDbPipe",ANY,(uint8_t)-1,any},
		// 0x051e
		{"SalListSetDropdownWidth",ANY,(uint8_t)-1,any},
		// 0x051f
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
		{"SalRibbonSetItemVisible",ANY,(uint8_t)-1,any},
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
		// 0x052a
		{"SalCalGetSelectedDates",ANY,(uint8_t)-1,any},
		// 0x052b
		{"SalCalMarkDays",ANY,(uint8_t)-1,any},
		// 0x052c
		{"SalGridGetSummaryColumn",ANY,(uint8_t)-1,any},
		// 0x052d
		{"SalGridSetSummaryColumnJustify",ANY,(uint8_t)-1,any},
		// 0x052e
		{"SalGridGetSummaryColumnValue",ANY,(uint8_t)-1,any},
		// 0x052f
		{"SalRibbonSetItemTooltip",ANY,(uint8_t)-1,any},
		// 0x0530
		{"SalRibbonSetItemAccelerator",ANY,(uint8_t)-1,any},
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
		{"SalMenuGetFontSettings",ANY,(uint8_t)-1,any},
		// 0x0537
		{"SalMenuGetCheck",ANY,(uint8_t)-1,any},
		// 0x0538
		{"SalMenuGetEnabled",ANY,(uint8_t)-1,any},
		// 0x0539
		{"SalMenuInsert",ANY,(uint8_t)-1,any},
		// 0x053a
		{"SalMenuInsertEx",ANY,(uint8_t)-1,any},
		// 0x053b
		{"SalMenuGetCount",ANY,(uint8_t)-1,any},
		// 0x053c
		{"SalMenuGetNameByPosition",ANY,(uint8_t)-1,any},
		// 0x053d
		{"SalMenuDelete",ANY,(uint8_t)-1,any},
		// 0x053e
		{"SalMenuGetItemName",ANY,(uint8_t)-1,any},
		// 0x053f
		{"SalMenuGetHandle",ANY,(uint8_t)-1,any},
		// 0x0540
		{"SalMenuGetMDIPersistMenus",ANY,(uint8_t)-1,any},
		// 0x0541
		{"SalMenuSetPicture",ANY,(uint8_t)-1,any},
		// 0x0542
		{"SalWebReportCreate",ANY,(uint8_t)-1,any},
		// 0x0543
		{"SalWebReportCreateToFile",ANY,(uint8_t)-1,any},
		// 0x0544
		{"SalStatusCreateProgressBar",ANY,(uint8_t)-1,any},
		// 0x0545
		{"SalStatusSetPaneImage",ANY,(uint8_t)-1,any},
		// 0x0546
		{"SalStatusAddPane",ANY,(uint8_t)-1,any},
		// 0x0547
		{"SalStatusSetPaneText",ANY,(uint8_t)-1,any},
		// 0x0548
		{"SalStatusSetPaneVisible",ANY,(uint8_t)-1,any},
		// 0x0549
		{"SalStatusSetPaneTooltip",ANY,(uint8_t)-1,any},
		// 0x054a
		{"SalBackgroundWorkerStart",ANY,(uint8_t)-1,any},
		// 0x054b
		{"SalJSONDeserializeUDV",ANY,(uint8_t)-1,any},
		// 0x054c
		{"SalBackgroundWorkerReportProgress",ANY,(uint8_t)-1,any},
		// 0x054d
		{"SalBackgroundWorkerIsBusy",ANY,(uint8_t)-1,any},
		// 0x054e
		{"SalBackgroundWorkerCancel",ANY,(uint8_t)-1,any},
		// 0x054f
		{"SalBackgroundWorkerIsCanceled",ANY,(uint8_t)-1,any},
		// 0x0550
		{"SalRibbonSetItemTransparentColor",ANY,(uint8_t)-1,any},
		// 0x0551
		{"SalTabSetPageTransparentColor",ANY,(uint8_t)-1,any},
		// 0x0552
		{"SalNavSetPaneTransparentColor",ANY,(uint8_t)-1,any},
		// 0x0553
		{"SalMeterShowPercent",ANY,(uint8_t)-1,any},
		// 0x0554
		{"SalMeterSetTextColor",ANY,(uint8_t)-1,any},
		// 0x0555
		{"SalJSONSerializeUDV",ANY,(uint8_t)-1,any},
		// 0x0556
		{"SalSetLibraryPath",ANY,(uint8_t)-1,any},
		// 0x0557
		{"SalGridSetSummaryColumnFmtPicture",ANY,(uint8_t)-1,any},
		// 0x0558
		{"SalWebGetAppURL",ANY,(uint8_t)-1,any},
		// 0x0559
		{"SalWebGetConnectionString",ANY,(uint8_t)-1,any},
		// 0x055a
		{"SalWebGetAppSetting",ANY,(uint8_t)-1,any},
		// 0x055b
		{"SalSetHintText",ANY,(uint8_t)-1,any},
		// 0x055c
		{"SalGetHintText",ANY,(uint8_t)-1,any},
		// 0x055d
		{"SalSetIMEMode",ANY,(uint8_t)-1,any},
		// 0x055e
		{"SalOutlineLoadMigrate",ANY,(uint8_t)-1,any},
		// 0x055f
		{"SalMenuSetAnimate",ANY,(uint8_t)-1,any},
		// 0x0560
		{"SalTblDestroyEdit",ANY,(uint8_t)-1,any},
		// 0x0561
		{"SalIsX64",ANY,(uint8_t)-1,any},
		// 0x0562
		{"SalOutlineCopyItemProps",ANY,(uint8_t)-1,any},
		// 0x0563
		{"SalSetTooltipImage",ANY,(uint8_t)-1,any},
		// 0x0564
		{"SalFileGetStrEx",ANY,(uint8_t)-1,any},
		// 0x0565
		{"SalRTFSetMargin",ANY,(uint8_t)-1,any},
		// 0x0566
		{"SalRTFGetMargin",ANY,(uint8_t)-1,any},
		// 0x0567
		{"SalThemeSetXMLPathName",ANY,(uint8_t)-1,any},
		// 0x0568
		{"SalThemeGetXMLPathName",ANY,(uint8_t)-1,any},
		// 0x0569
		{"SalBackgroundWorkerAnyRunning",ANY,(uint8_t)-1,any},
		// 0x056a
		{"SalBackgroundWorkerTerminateAnyRunning",ANY,(uint8_t)-1,any},
		// 0x056b
		{"SalGridColumnSummaryDateValues",ANY,(uint8_t)-1,any},
		// 0x056c
		{"SalDateReturn",ANY,(uint8_t)-1,any},
		// 0x056d
		{"SalCenterWindowEx",ANY,(uint8_t)-1,any},
		// 0x056e
		{"SalNavGetExpandedCount",ANY,(uint8_t)-1,any},
		// 0x056f
		{"SalNavSetExpandedCount",ANY,(uint8_t)-1,any},
		// 0x0570
		{"SalStrCharLength",ANY,(uint8_t)-1,any},
		// 0x0571
		{"SalRibbonGetItemFieldWidth",ANY,(uint8_t)-1,any},
		// 0x0572
		{"SalRibbonSetItemFieldWidth",ANY,(uint8_t)-1,any},
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
		// 0x057a
		{"SalNotifyShowBalloon",ANY,(uint8_t)-1,any},
		// 0x057b
		{"SalNotifyDeleteIcon",ANY,(uint8_t)-1,any},
		// 0x057c
		{"SalJSONDeserializeUDVEx",ANY,(uint8_t)-1,any},
		// 0x057d
		{"SalJSONSerializeUDVEx",ANY,(uint8_t)-1,any},
		// 0x057e
		{"SalProfileStart",ANY,(uint8_t)-1,any},
		// 0x057f
		{"SalProfileSuspend",ANY,(uint8_t)-1,any},
		// 0x0580
		{"SalProfileContinue",ANY,(uint8_t)-1,any},
		// 0x0581
		{"SalProfileStop",ANY,(uint8_t)-1,any},
		// 0x0582
		{"SalGridIsRowExcludedByFilter",ANY,(uint8_t)-1,any},
		// 0x0583
		{"SalGridBackColorSet",ANY,(uint8_t)-1,any},
		// 0x0584
		{"SalGridBackColorGet",ANY,(uint8_t)-1,any},
		// 0x0585
		{"SalGridTextColorSet",ANY,(uint8_t)-1,any},
		// 0x0586
		{"SalGridTextColorGet",ANY,(uint8_t)-1,any},
		// 0x0587
		{"SalTabAttachWindowAsChild",ANY,(uint8_t)-1,any},
		// 0x0588
		{"SalTabIsWindowActivated",ANY,(uint8_t)-1,any},
		// 0x0589
		{"SalStrEncrypt",ANY,(uint8_t)-1,any},
		// 0x058a
		{"SalStrDecrypt",ANY,(uint8_t)-1,any},
		// 0x058b
		{"SalStrCompressEx",ANY,(uint8_t)-1,any},
		// 0x058c
		{"SalStrUncompressEx",ANY,(uint8_t)-1,any},
		// 0x058d
		{"SalNavSetGroupTitle",ANY,(uint8_t)-1,any},
		// 0x058e
		{"SalProfileGetInfo",ANY,(uint8_t)-1,any},
		// 0x058f
		{"SalProfileAnnotate",ANY,(uint8_t)-1,any},
		// 0x0590
		{"SalProfileTagEnter",ANY,(uint8_t)-1,any},
		// 0x0591
		{"SalProfileTagLeave",ANY,(uint8_t)-1,any},
		// 0x0592
		{"SalTraceDebug",ANY,(uint8_t)-1,any},
		// 0x0593
		{"SalDlgSetAutoHideStatus",ANY,(uint8_t)-1,any},
		// 0x0594
		{"SalDlgGetAutoHideStatus",ANY,(uint8_t)-1,any},
		// 0x0595
		{"SalXMLSerializeUDVToString",ANY,(uint8_t)-1,any},
		// 0x0596
		{"SalXMLDeserializeUDVFromString",ANY,(uint8_t)-1,any},
		// 0x0597
		{"SalStrHash",ANY,(uint8_t)-1,any},
		// 0x0598
		{"SalNavSaveStateEx",ANY,(uint8_t)-1,any},
		// 0x0599
		{"SalNavLoadStateEx",ANY,(uint8_t)-1,any},
		// 0x059a
		{"SalNotifyInitToast",ANY,(uint8_t)-1,any},
		// 0x059b
		{"SalNotifyShowToast",ANY,(uint8_t)-1,any},
		// 0x059c
		{"SalTabSetMargins",ANY,(uint8_t)-1,any},
		// 0x059d
		{"SalTabGetMargins",ANY,(uint8_t)-1,any},
		// 0x059e
		{"SalTabSetOrientation",ANY,(uint8_t)-1,any},
		// 0x059f
		{"SalTabGetOrientation",ANY,(uint8_t)-1,any},
		// 0x05a0
		{"SqlClearLongBindDatatype",ANY,(uint8_t)-1,any},
		// 0x05a1
		{"SalThemeSupportsNative3DFaceColor",ANY,(uint8_t)-1,any},
		// 0x05a2
		{"SalThemeEnableNative3DFaceColor",ANY,(uint8_t)-1,any},
		// 0x05a3
		{"SalThemeIsEnabledNative3DFaceColor",ANY,(uint8_t)-1,any},
		// 0x05a4
		{"SalTooltipSetDelay",ANY,(uint8_t)-1,any},
		// 0x05a5
		{"SalTooltipGetDelay",ANY,(uint8_t)-1,any},
		// 0x05a6
		{"SalTabEnableCtrlTab",ANY,(uint8_t)-1,any},
		// 0x05a7
		{"SalYieldSetInterval",ANY,(uint8_t)-1,any},
		// 0x05a8
		{"SalSetButtonChecked",ANY,(uint8_t)-1,any},
		// 0x05a9
		{"SalAnchorEnable",ANY,(uint8_t)-1,any},
		// 0x05aa
		{"SalNotifyClearToasts",ANY,(uint8_t)-1,any},
		// 0x05ab
		{"SalRTFSetReadOnly",ANY,(uint8_t)-1,any},
		// 0x05ac
		{"SalRTFGetReadOnly",ANY,(uint8_t)-1,any},
		// 0x05ad
		{"SqlSetLongDatatype",ANY,(uint8_t)-1,any},
		// 0x05ae
		{"SqlClearLongDatatype",ANY,(uint8_t)-1,any},
		// 0x05af
		{"SalIconSet",ANY,(uint8_t)-1,any},
		// 0x05b0
		{"SalFieldSetVerticalCentered",ANY,(uint8_t)-1,any},
		// 0x05b1
		{"SalFieldIsVerticalCentered",ANY,(uint8_t)-1,any},
		// 0x05b2
		{"SalRibbonSetItemImageEx",ANY,(uint8_t)-1,any},
		// 0x05b3
		{"SalRibbonAddItemEx",ANY,(uint8_t)-1,any},
		// 0x05b4
		{"SalSetComboBoxItemHeight",ANY,(uint8_t)-1,any},
		// 0x05b5
		{"SalGetComboBoxItemHeight",ANY,(uint8_t)-1,any},
		// 0x05b6
		{"SalScrollEnableCtxMenu",ANY,(uint8_t)-1,any},
		// 0x05b7
		{"SalCalSetSelectedDates",ANY,(uint8_t)-1,any},
		// 0x05b8
		{"SalZoomWindow",ANY,(uint8_t)-1,any},
		// 0x05b9
		{"SalMenuSetStatusText",ANY,(uint8_t)-1,any},
		// 0x05ba
		{"SalMenuSetTipText",ANY,(uint8_t)-1,any},
		// 0x05bb
		{"SalMenuGetStatusText",ANY,(uint8_t)-1,any},
		// 0x05bc
		{"SalMenuGetTipText",ANY,(uint8_t)-1,any},
		// 0x05bd
		{"SalWebGetClientIP",ANY,(uint8_t)-1,any},
		// 0x05be
		{"SalWebGetHttpMethod",ANY,(uint8_t)-1,any},
		// 0x05bf
		{"SalWebGetHttpHeader",ANY,(uint8_t)-1,any},
		// 0x05c0
		{"SalDateAddDay",ANY,(uint8_t)-1,any},
		// 0x05c1
		{"SalDateMonthEnd",ANY,(uint8_t)-1,any},
		// 0x05c2
		{"SalTabIsPageEnabled",ANY,(uint8_t)-1,any},
		// 0x05c3
		{"SalObjCopy",ANY,(uint8_t)-1,any},
		// 0x05c4
		{"SalGetZoom",ANY,(uint8_t)-1,any},
		// 0x05c5
		{"SalTabPageHasChild",ANY,(uint8_t)-1,any},
		// 0x05c6
		{"SalTblSwapRows",ANY,(uint8_t)-1,any},
		// 0x05c7
		{"SalAnchorIsEnabled",ANY,(uint8_t)-1,any},
		// 0x05c8
		{"SalAnchorGet",ANY,(uint8_t)-1,any},
		// 0x05c9
		{"SalAnchorChildInitScaling",ANY,(uint8_t)-1,any},
		// 0x05ca
		{"SalTblQueryRowCount",ANY,(uint8_t)-1,any}
};
