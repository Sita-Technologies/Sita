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


#ifdef __unix__ 
#include <iconv.h>
#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
#include <windows.h>
#else
#error "neither Unix nor Windows environment defined"
#endif
#include "outline_decs.hpp"
#include "decompile.hpp"
#include "helper.hpp"
#include "commandline_args.hpp"
#include "SalNumber.hpp"
#include "item.hpp"
#include "COutline.hpp"
#include "process_outline.hpp"
#include <stdio.h>
#include <string.h>
#include <exception>

#ifndef TDx64
struct ItemBodyType item_bodies[0x3d] = {
		{"NULL", 0x01, 0x01, 0x00, 0x00}, // 0x00
		{"TEXT", 0x01, 0x00, 0x00, 0x00}, // 0x01
		{"INT", 0x01, 0x01, 0x00, 0x04}, // 0x02
		{"LONG", 0x01, 0x01, 0x00, 0x04}, // 0x03
		{"HBITMAP", 0x01, 0x01, 0x00, 0x00}, // 0x04
		{"LIST", 0x01, 0x01, 0x00, 0x04}, // 0x05
		{"HWND", 0x00, 0x01, 0x00, 0x04}, // 0x06
		{"STRUCT", 0x01, 0x01, 0x00, 0x00}, // 0x07
		{"COORD", 0x01, 0x01, 0x00, 0x04}, // 0x08
		{"CODE", 0x00, 0x01, 0x00, 0x00}, // 0x09
		{"OLDVAROFFSET", 0x00, 0x00, 0x00, 0x02}, // 0x0a
		{"DLGITEM", 0x00, 0x01, 0x00, 0x04}, // 0x0b
		{"METAFILEPICT", 0x01, 0x01, 0x01, 0x00}, // 0x0c
		{"HANDLE", 0x01, 0x01, 0x00, 0x04}, // 0x0d
		{"ICON", 0x01, 0x01, 0x01, 0x00}, // 0x0e
		{"ARRAYBOUNDS", 0x00, 0x01, 0x00, 0x08}, // 0x0f
		{"INCLUDEHITEM", 0x00, 0x01, 0x00, 0x04}, // 0x10
		{"PICTURE", 0x01, 0x01, 0x00, 0x00}, // 0x11
		{"CLASS_MSGS", 0x00, 0x01, 0x00, 0x00}, // 0x12
		{"HITEM", 0x01, 0x01, 0x00, 0x04}, // 0x13
		{"WINATTR", 0x01, 0x01, 0x00, 0x00}, // 0x14
		{"RESOURCEID", 0x01, 0x01, 0x00, 0x02}, // 0x15
		{"QUESTQUERYDEF", 0x01, 0x01, 0x01, 0x00}, // 0x16
		{"QUESTCOLUMNINFO", 0x01, 0x01, 0x01, 0x00}, // 0x17
		{"WINSTYLE", 0x01, 0x01, 0x00, 0x04}, // 0x18
		{"SQLWB", 0x01, 0x01, 0x01, 0x04}, // 0x19
		{"RESOURCE", 0x01, 0x01, 0x01, 0x02}, // 0x1a
		{"VIEWSIZE", 0x01, 0x01, 0x01, 0x02}, // 0x1b
		{"VIEWINFO", 0x01, 0x01, 0x01, 0x00}, // 0x1c
		{"VIRTFUN", 0x00, 0x01, 0x00, 0x00}, // 0x1d
		{"VIRTFUNMERGED", 0x00, 0x00, 0x00, 0x04}, // 0x1e
		{"CCDATA", 0x01, 0x01, 0x01, 0x00}, // 0x1f
		{"CCSIZE", 0x01, 0x01, 0x01, 0x02}, // 0x20
		{"CLASSCHILDOFFSET", 0x00, 0x01, 0x00, 0x08}, // 0x21
		{"ORDINAL", 0x00, 0x01, 0x00, 0x04}, // 0x22
		{"CLASSPROPS", 0x01, 0x01, 0x01, 0x00}, // 0x23
		{"CLASSPROPSSIZE", 0x01, 0x01, 0x01, 0x02}, // 0x24
		{"QUESTVIEWDEF", 0x01, 0x01, 0x01, 0x02}, // 0x25
		{"INHERITQUEST", 0x01, 0x01, 0x01, 0x02}, // 0x26
		{"INHERITPROPS", 0x01, 0x01, 0x01, 0x02}, // 0x27
		{"MDARRAYBOUNDS", 0x00, 0x01, 0x00, 0x00}, // 0x28
		{"SYMID", 0x00, 0x01, 0x00, 0x04}, // 0x29
		{"DYNALIB_ORDINAL", 0x00, 0x01, 0x00, 0x02}, // 0x2a
		{"HLIBSAL", 0x00, 0x01, 0x00, 0x02}, // 0x2b
		{"DT_MAKERUNDLG", 0x01, 0x01, 0x01, 0x00}, // 0x2c
		{"INCLUDEINFO", 0x00, 0x01, 0x00, 0x02}, // 0x2d
		{"COMPILER_STRUCT", 0x00, 0x01, 0x00, 0x00}, // 0x2e
		{"COMPILER_INT", 0x00, 0x01, 0x00, 0x04}, // 0x2f
		{"CHILDLINECOUNT", 0x01, 0x00, 0x00, 0x04}, // 0x30
		{"ITEMPREV", 0x01, 0x00, 0x00, 0x02}, // 0x31
		{"ITEMCLONE", 0x01, 0x01, 0x00, 0x04}, // 0x32
		{"VAROFFSET", 0x00, 0x01, 0x00, 0x04}, // 0x33
		{"CLASS_XMSGS", 0x00, 0x01, 0x00, 0x00}, // 0x34
		{"ONX_INT", 0x01, 0x01, 0x01, 0x04}, // 0x35
		{"CLASS_DISPATCH", 0x01, 0x01, 0x00, 0x00}, // 0x36
		{"CLASS_CONSTRUCTOR", 0x00, 0x01, 0x00, 0x02}, // 0x37
		{"COM_DISPATCHFLAG", 0x01, 0x01, 0x00, 0x02}, // 0x38
		{"CLASS_DESTRUCTOR", 0x00, 0x01, 0x00, 0x04}, // 0x39
		{"BRKPTINFO", 0x00, 0x01, 0x00, 0x02}, // 0x3a
		{"ON_TABBAR", 0x01, 0x01, 0x00, 0x04}, // 0x3b
		{"DEFAULT_CONSTRUCTOR", 0x00, 0x01, 0x00, 0x04} // 0x3c
};
#else
struct ItemBodyType item_bodies[0x3d] = {
		{"NULL", 0x01, 0x01, 0x00, 0x00},
		{"TEXT", 0x01, 0x00, 0x00, 0x00},
		{"INT", 0x01, 0x01, 0x00, 0x04},
		{"LONG", 0x01, 0x01, 0x00, 0x08},
		{"HBITMAP", 0x01, 0x01, 0x00, 0x00},
		{"LIST", 0x01, 0x01, 0x00, 0x04},
		{"HWND", 0x00, 0x01, 0x00, 0x08},
		{"STRUCT", 0x01, 0x01, 0x00, 0x00},
		{"COORD", 0x01, 0x01, 0x00, 0x04},
		{"CODE", 0x00, 0x01, 0x00, 0x00},
		{"OLDVAROFFSET", 0x00, 0x00, 0x00, 0x02},
		{"DLGITEM", 0x00, 0x01, 0x00, 0x04},
		{"METAFILEPICT", 0x01, 0x01, 0x01, 0x00},
		{"HANDLE", 0x01, 0x01, 0x00, 0x08},
		{"ICON", 0x01, 0x01, 0x01, 0x00},
		{"ARRAYBOUNDS", 0x00, 0x01, 0x00, 0x08},
		{"INCLUDEHITEM", 0x00, 0x01, 0x00, 0x08},
		{"PICTURE", 0x01, 0x01, 0x00, 0x00},
		{"CLASS_MSGS", 0x00, 0x01, 0x00, 0x00},
		{"HITEM", 0x01, 0x01, 0x00, 0x08},
		{"WINATTR", 0x01, 0x01, 0x00, 0x00},
		{"RESOURCEID", 0x01, 0x01, 0x00, 0x02},
		{"QUESTQUERYDEF", 0x01, 0x01, 0x01, 0x00},
		{"QUESTCOLUMNINFO", 0x01, 0x01, 0x01, 0x00},
		{"WINSTYLE", 0x01, 0x01, 0x00, 0x04},
		{"SQLWB", 0x01, 0x01, 0x01, 0x04},
		{"RESOURCE", 0x01, 0x01, 0x01, 0x02},
		{"VIEWSIZE", 0x01, 0x01, 0x01, 0x02},
		{"VIEWINFO", 0x01, 0x01, 0x01, 0x00},
		{"VIRTFUN", 0x00, 0x01, 0x00, 0x00},
		{"VIRTFUNMERGED", 0x00, 0x00, 0x00, 0x04},
		{"CCDATA", 0x01, 0x01, 0x01, 0x00},
		{"CCSIZE", 0x01, 0x01, 0x01, 0x02},
		{"CLASSCHILDOFFSET", 0x00, 0x01, 0x00, 0x08},
		{"ORDINAL", 0x00, 0x01, 0x00, 0x04},
		{"CLASSPROPS", 0x01, 0x01, 0x01, 0x00},
		{"CLASSPROPSSIZE", 0x01, 0x01, 0x01, 0x02},
		{"QUESTVIEWDEF", 0x01, 0x01, 0x01, 0x02},
		{"INHERITQUEST", 0x01, 0x01, 0x01, 0x02},
		{"INHERITPROPS", 0x01, 0x01, 0x01, 0x02},
		{"MDARRAYBOUNDS", 0x00, 0x01, 0x00, 0x00},
		{"SYMID", 0x00, 0x01, 0x00, 0x04},
		{"DYNALIB_ORDINAL", 0x00, 0x01, 0x00, 0x02},
		{"HLIBSAL", 0x00, 0x01, 0x00, 0x04},
		{"DT_MAKERUNDLG", 0x01, 0x01, 0x01, 0x00},
		{"INCLUDEINFO", 0x00, 0x01, 0x00, 0x02},
		{"COMPILER_STRUCT", 0x00, 0x01, 0x00, 0x00},
		{"COMPILER_INT", 0x00, 0x01, 0x00, 0x04},
		{"CHILDLINECOUNT", 0x01, 0x00, 0x00, 0x04},
		{"ITEMPREV", 0x01, 0x00, 0x00, 0x04},
		{"ITEMCLONE", 0x01, 0x01, 0x00, 0x08},
		{"VAROFFSET", 0x00, 0x01, 0x00, 0x04},
		{"CLASS_XMSGS", 0x00, 0x01, 0x00, 0x00},
		{"ONX_INT", 0x01, 0x01, 0x01, 0x04},
		{"CLASS_DISPATCH", 0x01, 0x01, 0x00, 0x00},
		{"CLASS_CONSTRUCTOR", 0x00, 0x01, 0x00, 0x02},
		{"COM_DISPATCHFLAG", 0x01, 0x01, 0x00, 0x02},
		{"CLASS_DESTRUCTOR", 0x00, 0x01, 0x00, 0x08},
		{"BRKPTINFO", 0x00, 0x01, 0x00, 0x02},
		{"ON_TABBAR", 0x01, 0x01, 0x00, 0x08},
		{"DEFAULT_CONSTRUCTOR", 0x00, 0x01, 0x00, 0x08}
};
#endif

#ifndef TDx64
const char* get_event_name(struct ItemBody* item_body) {
	if (item_body->type != 0x2f) {
		return NULL;
	}
	uint32_t event;
	memcpy(&event, &item_body->size, sizeof(event));

	switch (event) {
	case 0x0010:
		return "SAM_Close";
	case 0x0113:
		return "SAM_Timer";
	case 0x0233:
		return "SAM_DropFiles";
	case 0x03e9:
		return "SAM_DDE_DataChange";
	case 0x03ea:
		return "SAM_DDE_ClientRequest";
	case 0x03eb:
		return "SAM_DDE_ClientExecute";
	case 0x1001:
		return "SAM_Create";
	case 0x1002:
		return "SAM_Destroy";
	case 0x1007:
		return "SAM_SetFocus";
	case 0x1008:
		return "SAM_KillFocus";
	case 0x2001:
		return "SAM_AppStartup";
	case 0x2002:
		return "SAM_AppExit";
	case 0x2003:
		return "SAM_SqlError";
	case 0x2004:
		return "SAM_AnyEdit";
	case 0x2005:
		return "SAM_FieldEdit";
	case 0x2006:
		return "SAM_Click";
	case 0x200c:
		return "SAM_Validate";
	case 0x200d:
		return "SAM_ReportFetchInit";
	case 0x200e:
		return "SAM_ReportFetchNext";
	case 0x200f:
		return "SAM_ReportStart";
	case 0x2010:
		return "SAM_ReportFinish";
	case 0x2013:
		return "SAM_Print";
	case 0x201c:
		return "SAM_Help";
	case 0x2021:
		return "SAM_ReportNotify";
	case 0x202e:
		return "SAM_DragStart";
	case 0x202f:
		return "SAM_DragEnter";
	case 0x2030:
		return "SAM_DragMove";
	case 0x2031:
		return "SAM_DragExit";
	case 0x2032:
		return "SAM_DragDrop";
	case 0x2033:
		return "SAM_DragCanAutoStart";
	case 0x2034:
		return "SAM_DragEnd";
	case 0x2035:
		return "SAM_DragNotify";
	case 0x2038:
		return "SAM_CreateComplete";
	case 0x2041:
		return "SAM_Activate";
	case 0x2048:
		return "SAM_ContextMenu";
	case 0x204e:
		return "SAM_Dock";
	case 0x2052:
		return "SAM_DockResize";
	case 0x2053:
		return "SAM_DockResizeNotify";
	case 0x2055:
		return "SAM_SessionError";
	case 0x2009:
		return "SAM_DoubleClick";
	case 0x200a:
		return "SAM_ScrollBar";
	case 0x2016:
		return "SAM_CornerClick";
	case 0x2057:
		return "SAM_TabChange";
	case 0x2063:
		return "SAM_NetException";
	case 0x2064:
		return "SAM_TBItemSelect";
	case 0x2066:
		return "SAM_DisplayTooltip";
	case 0x2067:
		return "SAM_FrameSize";
	case 0x2068:
		return "SAM_RibbonItemClick";
	case 0x2069:
		return "SAM_RibbonShow";
	case 0x2070:
		return "SAM_MenuItemClick";
	case 0x2071:
		return "SAM_ThreadEvent";
	case 0x2072:
		return "SAM_NotifyIcon";
	case 0x2076:
		return "SAM_RTFPaste";
	case 0x4000:
		return "SAM_User";
	// Windows messages passed through TD. Not SAM_ but SAL event handlers
	// CAN be registered for them, so they appear in compiled Message Actions.
	case 0x0005: return "WM_SIZE";
	case 0x000F: return "WM_PAINT";
	case 0x002B: return "WM_DRAWITEM";
	case 0x002C: return "WM_MEASUREITEM";
	case 0x0100: return "WM_KEYDOWN";
	case 0x0101: return "WM_KEYUP";
	case 0x0102: return "WM_CHAR";
	case 0x0111: return "WM_COMMAND";
	case 0x0200: return "WM_MOUSEMOVE";
	case 0x0201: return "WM_LBUTTONDOWN";
	case 0x0202: return "WM_LBUTTONUP";
	case 0x0203: return "WM_LBUTTONDBLCLK";
	case 0x0204: return "WM_RBUTTONDOWN";
	case 0x0205: return "WM_RBUTTONUP";
	case 0x0206: return "WM_RBUTTONDBLCLK";
	case 0x03e0:
		if (is_verbose()) {
			return "WM_DDE_First ! aka WM_DDE_Initiate";
		}
		return "WM_DDE_First"; // same numeric constant as WM_DDE_Initiate — known compiler loss
	case 0x03e1:
		return "WM_DDE_Terminate";
	case 0x03e2:
		return "WM_DDE_Advise";
	case 0x03e3:
		return "WM_DDE_Unadvise";
	case 0x03e4:
		return "WM_DDE_Ack";
	case 0x03e5:
		return "WM_DDE_Data";
	case 0x03e6:
		return "WM_DDE_Request";
	case 0x03e7:
		return "WM_DDE_Poke";
	case 0x03e8:
		return "WM_DDE_Execute";
	default:
		return NULL;
	}
}
#endif

uint16_t CItem::itembody_elementsize(struct ItemBody* item_body) {
	if (item_body->type && item_body->type <= 0x3c) {
		uint8_t size = item_bodies[item_body->type].size;
		if (!size) {
			return 3 + item_body->size;
		}
		return 1+size;
	}
	return 0;
}

struct ItemBody* CItem::itembody_next(struct ItemBody* item_body, struct tagITEM* p_item) {
	if (item_body == NULL) {
		// get first
		// test for remaining length
		if (!p_item) {
			return NULL;
		}
		if (p_item->data_length < 3 || p_item->data_length < itembody_elementsize((struct ItemBody*)p_item->data)) {
			// item incomplete
			if (is_verbose() && p_item->data_length) {
				oputs("[[");
				for (uint32_t i = 0; i < p_item->data_length; i++) {
					oprintf("%02x ",p_item->data[i]);
				}
				oputs("..]]");
			}
			return NULL;
		}
		return (struct ItemBody*)p_item->data;
	}
	if ((char*)item_body + 3 - (char*)p_item->data >= p_item->data_length) {

		return NULL;
	}
	uint16_t elem_size = itembody_elementsize(item_body);
	if (elem_size == 0) {
		return NULL; // error: cannot parse due to unknown item body type
	}
	struct ItemBody* ret = (struct ItemBody*)((char*)item_body + elem_size);
	if ((char*)ret + 3 - (char*)p_item->data > p_item->data_length || (char*)ret + itembody_elementsize(ret) - (char*)p_item->data > p_item->data_length) {
		if (is_verbose() && (char*)ret - (char*)p_item->data < p_item->data_length) {
			oputs("[[");
			for (uint32_t i = 0; (char*)ret + i - (char*)p_item->data < p_item->data_length; i++) {
				oprintf("%02x ",((unsigned char*)ret)[i]);
			}
			oputs("..]]");
		}
		return NULL;
	}
	return (struct ItemBody*)((char*)item_body + elem_size);
}

struct ItemBody* CItem::get_itembody(class COutline* outline, uint64_t item_id, uint16_t type) {
	tagITEM* p_item = outline->get_item(item_id);
	if (!p_item) {
		return NULL;
	}
	for (struct ItemBody* item_body = itembody_next(0,p_item);item_body;item_body = itembody_next(item_body,p_item)) {
		if (item_body->type == type) {
			return item_body;
		}
	}
	return NULL;
}

#define AVOID_COMPILED_UNCOMPILED_DUPLICATES \
		if (!(outline->get_file_hdr().flags & FLAG_COMPILED)) { \
			/* uncompiled app, should already have printed 0x01-itembody string data */ \
		return; \
	} \
\
/* if compiled app contained 0x01-string-data, don't decompile 0x09-item-data */ \
		if (get_itembody(outline, item_id, 0x01)) { \
			return; \
		}

CItem::CItem(const char* name) : name(name) {
}

void CItem::first_pass(class COutline* outline, uint64_t item_id, uint64_t* memory_item) {
	struct ItemBody* dlgitem = get_itembody(outline, item_id, 0x0b);
	if (dlgitem) {
		if (!CDlg::cur_dlg_item.empty()) {
			outline->set_dialog_dlgitem(CDlg::cur_dlg_item.top(), *((uint32_t*)(((char*)dlgitem)+1)), item_id);
		}
	}
}

void CItem::preprocess(class COutline* outline, uint64_t item_id, uint64_t* memory_item) {
}

void CItem::print(class COutline* outline, uint64_t item_id, uint64_t* memory_item){
	if (this->name != NULL) {
		oputs(this->name);
	}else if (is_verbose()) {
		oputs("NULL");
	}
	if (this->name || is_verbose()) {
		const char16_t* str = outline->symbol_lookup(item_id);

		bool printed_name = false;
		if (str) {
			oputs(" ");
			print_utf16(str, strlen_utf16(str));
			printed_name = true;
		}

		if (!printed_name) {
			struct ItemBody* item_body = get_itembody(outline, item_id, 0x01);
			if (item_body) {
				oputs(" ");
				print_utf16((const char16_t*)item_body->data, item_body->size);
			}
		}

		if (is_verbose()) {
			print_all_itembodies(outline,item_id);
		}
	}
}

void CItem::print_all_itembodies(class COutline* outline, uint64_t item_id) {
	tagITEM* p_item = outline->get_item(item_id);
	for (struct ItemBody* item_body = itembody_next(0,p_item);item_body;item_body = itembody_next(item_body,p_item)) {
		if (item_body->type == 0x01) {
			continue;
		}
		uint32_t s = itembody_elementsize(item_body);
		if (item_body->type && item_body->type <= 0x3c) {
			oprintf(" %s:",item_bodies[item_body->type].name);
			switch (item_bodies[item_body->type].size) {
			case 2:
				oprintf("0x%04x",item_body->size);
				break;
			case 4: {
				uint32_t v;
				memcpy(&v, &item_body->size, sizeof(v));
				oprintf("0x%08x",v);
				break;
			}
			case 8: {
				uint32_t v[2];
				memcpy(v, &item_body->size, sizeof(v));
				oprintf("0x%08x;0x%08x",v[0],v[1]);
				break;
			}
			default:
				oputs("[[");
				for (uint32_t i=1 + (item_bodies[item_body->type].size==0?2:0) ;i<s;i++) {
					oprintf("%02x%s",*((uint8_t*)item_body+i),(i+1<s)?" ":"");
				}
				oputs("]]");
			}
		}else{
			oputs(" [[");
			for (uint32_t i=0;i + ((char*)item_body - (char*)p_item->data)<p_item->data_length;i++) {
				oprintf("%02x%s",*((uint8_t*)item_body+i),(i+1 + ((char*)item_body - (char*)p_item->data)<p_item->data_length)?" ":"");
			}
			oputs("]]");
		}
	}
}

void CItem::itembody_add_string(class COutline* outline, uint64_t item_id, const char* str) {
	size_t len = strlen(str);
	if (len) {
		// convert to UTF-16
		size_t out_len = 2*len+2 + sizeof(struct ItemBody);
		struct ItemBody* out = alloc<struct ItemBody*>(out_len);
		char* out_buffer = (char*)(out+1);
		out_len -= sizeof(struct ItemBody);
#ifdef __unix__ 
		iconv_t str_convert = iconv_open("UTF-16LE", "UTF-8");
		iconv(str_convert, (char**)&str, &len, &out_buffer, &out_len);
		iconv_close(str_convert);
#else
		out_len = MultiByteToWideChar(CP_UTF8, 0, (LPCCH)str, (int)len, (LPWSTR)out_buffer, (int)out_len);
		out_buffer += 2*out_len;
#endif
		*(out_buffer++) = 0;
		*(out_buffer++) = 0;
		out->size = (uint16_t)(out_buffer - (char*)(out+1));
		out->type = 0x01;
		CItem::add_itembody(outline, item_id, out);
		free(out);
	}
}

void CItem::decompile(class COutline* outline, uint64_t item_id, uint64_t* memory_item) {
	if (is_binary_app_output() && !get_itembody(outline, item_id, 0x01)) {

		const char16_t* str = outline->symbol_lookup(item_id);
		if (str) {
			size_t len = strlen_utf16(str)+2;
			if (len) {
				// Append array suffix to name for binary output — see
				// decompile_helper for the full explanation. Same applies
				// here for variable types registered as plain `CVar(...)`
				// in tag_items[] (Number / Date/Time / String / Boolean /
				// File Handle / Sql Handle / Window Handle / Session Handle
				// / Long String / Binary), which inherit CItem::decompile
				// rather than overriding it.
				char arr_buf[128];
				size_t arr_n = format_array_suffix(outline, item_id, arr_buf, sizeof(arr_buf));
				size_t arr_utf16 = arr_n * 2;
				struct ItemBody* out = alloc<struct ItemBody*>(sizeof(struct ItemBody)+len+arr_utf16);
				out->type = 0x01;
				out->size = (uint16_t)(len + arr_utf16);
				memcpy(out->data,str,len);
				if (arr_n) {
					uint8_t* p = out->data + len - 2;
					for (size_t i = 0; i < arr_n; i++) {
						*p++ = (uint8_t)arr_buf[i];
						*p++ = 0;
					}
					*p++ = 0;
					*p = 0;
				}
				add_itembody(outline, item_id, out);
				free(out);
			}

		}else if (get_itembody(outline, item_id, 0x09)) {

			struct outstream out;
			char* out_ptr = 0;
			out.pos = 0;
			out.buf = &out_ptr;
			oset(out);
			bool verbose_tmp = is_verbose();
			set_verbose(false);


			this->print(outline,item_id,memory_item);
			if (out_ptr) {
				char* str = out_ptr;
				if (strncmp(out_ptr,this->name,strlen(this->name))==0) {
					str += strlen(this->name);
					while (*str == ' ') {
						str++;
					}
				}
				itembody_add_string(outline,item_id,str);
			}

			set_verbose(verbose_tmp);
			out.buf = 0;
			out.f = stdout;
			out.pos = 0;
			oset(out);
			if (out_ptr) {
				free(out_ptr);
			}

			CItem::remove_itembody(outline, item_id, 0x09);
		}
	}
}

// Helper: format the array suffix for an item into a caller's ASCII buffer
// (e.g. "[*]", "[10]", "[1:5]"). Returns chars written (excluding terminating
// NUL). Returns 0 if the item has no MDARRAYBOUNDS body (i.e. not an array).
// Both the text-output `print_array_boundaries` path and the binary-output
// `-a` path that builds body 0x01 (TEXT) need to spell the same suffix; this
// helper keeps the format consistent.
size_t CItem::format_array_suffix(class COutline* outline, uint64_t item_id, char* out, size_t out_sz) {
	struct ItemBody* item_body = get_itembody(outline, item_id, 0x28);
	if (!item_body) return 0;
	if (out_sz == 0) return 0;
	uint32_t* array_boundaries = (uint32_t*)item_body->data;
	if (!array_boundaries[0]) return 0;
	size_t pos = 0;
	auto put = [&](char c) { if (pos + 1 < out_sz) out[pos++] = c; };
	auto putn = [&](uint64_t n) {
		char tmp[24];
		int t = snprintf(tmp, sizeof(tmp), "%llu", (unsigned long long)n);
		for (int i = 0; i < t; i++) put(tmp[i]);
	};
	put('[');
	for (uint32_t d = 0; d < array_boundaries[0]; d++) {
		if (d) put(',');
		uint32_t lower = array_boundaries[2*d+1];
		uint32_t upper = array_boundaries[2*d+2];
		if (!lower && !upper) {
			put('*');
		} else if (!lower) {
			putn((uint64_t)upper + 1);
		} else {
			putn(lower);
			put(':');
			putn(upper);
		}
	}
	put(']');
	if (pos < out_sz) out[pos] = 0;
	return pos;
}

void CItem::print_array_boundaries(class COutline* outline, uint64_t item_id) {
	char buf[128];
	size_t n = format_array_suffix(outline, item_id, buf, sizeof(buf));
	if (n) {
		oputs(buf);
	}
}

void CItem::postprocess(class COutline* outline, uint64_t item_id, uint64_t* memory_item) {
}

void CItem::add_itembody(class COutline* outline, uint64_t item_id, struct ItemBody* item_body) {
	if (!item_body) {
		return;
	}
	tagITEM* p_item = outline->get_item(item_id);
	if (!p_item) {
		return;
	}
	uint16_t size = itembody_elementsize(item_body);
	if (!outline->change_item_size(item_id, p_item->data_length + size)) {
		fprintf(stderr,"error: resize of item 0x%08llx failed\n",(unsigned long long)item_id);
		return;
	}
	p_item = outline->get_item(item_id);
	memcpy(&p_item->data[p_item->data_length-size],item_body,size);
}

void CItem::remove_itembody(class COutline* outline, uint64_t item_id, uint8_t itembody_type) {
	tagITEM* p_item = outline->get_item(item_id);
	if (!p_item) {
		return;
	}

	uint32_t shrink = 0;
	while (struct ItemBody* item_body = get_itembody(outline, item_id, itembody_type)) {
		uint32_t size = 0;
		if ((size = itembody_elementsize(item_body)) == 0) {
			break;
		}
		struct ItemBody* look_ahead = itembody_next(item_body,p_item);
		shrink += size;
		p_item->data_length -= size;
		if (look_ahead) {
			if ((uint8_t*)look_ahead-(uint8_t*)item_body != size) {
				fprintf(stderr,"error: itembody_next didn't increment pointer by item_body->size\n");
				p_item->data_length += shrink;
				return;
			}
			for (uint8_t* i = (uint8_t*)look_ahead; i<p_item->data + p_item->data_length+size;i++) {
				*(i-size) = *i;
			}
		}else{
			break;
		}
	}
	if (shrink) {
		p_item->data_length += shrink;
		outline->change_item_size(item_id, p_item->data_length - shrink);
	}
}

void CItem::addvar(class COutline* outline, uint64_t memory_item, varscope var_scope, uint64_t item) {
	// get variable name and memory offset!!
	tagITEM* p_item = outline->get_item(item);
	if (!p_item) {
		return;
	}

	uint32_t var_offset = 0x00;
	uint32_t var_size = 0x00;
	struct ItemBody* item_body;
	item_body = get_itembody(outline, item, 0x33);
	bool has_offset_body = item_body != nullptr;
	if (item_body) {
		var_offset = *((uint32_t*)((uint8_t*)item_body+1));
	}
	item_body = get_itembody(outline, item, 0x2f);
	if (item_body) {
		var_size = *((uint32_t*)((uint8_t*)item_body+1));
	}

	if (!var_size) {
		// exported variable from dynalib...?

		// dynalib ordinal
		uint16_t ordinal = 0x00;
		item_body = get_itembody(outline, item, 0x2a);
		if (item_body) {
			ordinal = *((uint16_t*)((uint8_t*)item_body+1));
		}

		// include hitem
		uint32_t include_hitem = 0x00;
		item_body = get_itembody(outline, item, 0x10);
		if (item_body) {
			include_hitem = *((uint32_t*)((uint8_t*)item_body+1));
		}
		// libsal
		uint16_t libsal = 0x00;
		if (include_hitem) {
			ItemBody* hlibsal = get_itembody(outline, include_hitem, 0x2b);
			if (hlibsal) {
				libsal = *((uint16_t*)((uint8_t*)hlibsal+1));
			}
		}
		if (libsal && ordinal) {
			outline->add_dynalib_var(libsal,ordinal,item);
			return;
		}

		// class object in contents of form window...?
		if (var_scope == varscope::CURRENT_FORM) {
			uint64_t object_class = CObject::get_class(outline, item);
			if (object_class && outline->has_any_variable(object_class, varscope::CURRENT_OBJECT)) {
				outline->add_variable(memory_item, var_scope, var_offset, item);
				outline->add_variable(item, var_scope, 0, object_class);
				return;
			}
		}

		/*
		if (is_verbose()) {
			oprintf("[[WARN: var_size is 0, var_offset is 0x%04x]]",var_offset);
		}
		return; // don't add variable of empty size
		*/

		// Decoration items inside `Window Variables` / `Contents` (e.g.
		// GROUP_SEPARATOR / `! ` lines, type 0x7e) carry neither body 0x33
		// (offset) nor body 0x2f (size), and they did not match any of the
		// dynalib / class-object paths above. Registering them at offset 0
		// would shadow the real first variable. Skip them.
		if (!has_offset_body) {
			return;
		}
	}

	// A Contents control (body 0x0b, no var_size) whose body 0x33 holds
	// the Contents-block's shared offset (not a real per-control offset)
	// collides with a legit Window Parameter / Window Variable at the same
	// slot. Skip such controls.
	//
	// Distinguishing trait: Child Grid / Child Table (the only Contents
	// item types that contain accessible per-instance state — their
	// Window Variables register at CURRENT_OBJECT scope of the item via
	// CDlgParent::first_pass) keep their registration. Plain Background
	// Text / Pushbutton / Group Box / etc. fall through and get skipped —
	// they don't expose any name resolvable through the form's CURRENT_FORM
	// scope anyway.
	tagITEM* p_item_for_check = outline->get_item(item);
	if (var_size == 0
			&& get_itembody(outline, item, 0x0b)
			&& p_item_for_check
			&& p_item_for_check->type < TAG_ITEMS_AMOUNT
			&& !dynamic_cast<CDlgParent*>(::tag_items[p_item_for_check->type])) {
		return;
	}

	outline->add_variable(memory_item, var_scope, var_offset, item);
}

CItem::~CItem() {
}

// Body types emitted as `.data <NAME> ... .enddata` blocks by the runtime's
// SalOutlineSaveAsText writer. Each entry pairs an ItemBody type id with the
// canonical name printed after `.data `. RESOURCE has a different shape
// (`.data RESOURCE <a> <b> <c> <d>` with extra header values) and is handled
// separately. METAFILEPICT / ICON / SQLWB / QUEST* / VIEWSIZE / INHERITQUEST
// / CLASS_DISPATCH all have val3=1 in the body table but are not currently
// emitted; extend the table if they appear in real input.
struct DataBlockEmit {
	uint8_t body_type;   // ItemBody.type
	const char* name;    // string after ".data "
};
static const DataBlockEmit kDataBlockEmits[] = {
	{ 0x1c, "VIEWINFO" },
	{ 0x1f, "CCDATA" },
	{ 0x20, "CCSIZE" },
	// DT_MAKERUNDLG (0x2c) intentionally skipped — it embeds runtime
	// paths to the build's `.exe`/`.dll`/`.apc`/`.apl` siblings. The
	// runtime `bx` step uses those paths to locate sibling artifacts,
	// so emitting the body verbatim from a .exe input + then rebuilding
	// under a different output filename breaks bx silently. The runtime
	// regenerates DT_MAKERUNDLG itself during build — leaving it stripped
	// is correct behaviour.
	{ 0x35, "ONX_INT" },
	{ 0x23, "CLASSPROPS" },
	{ 0x24, "CLASSPROPSSIZE" },
	{ 0x27, "INHERITPROPS" },
	{ 0x1a, "RESOURCE" },
};

// Emit the hex-grid for a `.data` block payload. Layout (matches the
// runtime's SalOutlineSaveAsText writer):
//   - 32 bytes per line, prefixed `<offset_hex_4>: `
//   - Bytes are grouped by 8 bytes per group separated by single spaces;
//     within a group, hex digits are continuous (no space between bytes)
//   - Final partial line stops mid-grid at the last byte; trailing newline
static void print_data_block_hex(const uint8_t* payload, uint32_t length) {
	for (uint32_t off = 0; off < length; off += 32) {
		oprintf("%04X: ", off);
		uint32_t line_end = off + 32;
		if (line_end > length) line_end = length;
		for (uint32_t i = off; i < line_end; i++) {
			if (i != off && (i - off) % 8 == 0) {
				oputs(" ");
			}
			oprintf("%02X", payload[i]);
		}
		oputs("\n");
	}
}

// Emit `.data <NAME>\n<hex>\n.enddata\n` for any data-shaped body found on
// the item. Order matches the body chain (which is the same order the
// runtime emits its `.data` blocks at). The lines are flush-left (no
// `.head` prefix). RESOURCE is handled separately (extra leading numeric
// header).
void CItem::print_data_blocks(class COutline* outline, uint64_t item_id) {
	if (is_binary_app_output()) {
		return;
	}
	tagITEM* p_item = outline->get_item(item_id);
	if (!p_item) return;
	// Skip imported items: tagITEM.flags bit 0x400 marks an item that came
	// from a `File Include:`-pulled .apl/.app and is reproduced here as a
	// local copy for the runtime resolver. The text writer does NOT emit
	// .data blocks for such items — the library carries them.
	if (p_item->flags & 0x400) {
		return;
	}
	for (struct ItemBody* ib = itembody_next(0, p_item); ib; ib = itembody_next(ib, p_item)) {
		const char* name = nullptr;
		bool has_resource_header = false;
		for (size_t k = 0; k < sizeof(kDataBlockEmits)/sizeof(kDataBlockEmits[0]); k++) {
			if (ib->type == kDataBlockEmits[k].body_type) {
				name = kDataBlockEmits[k].name;
				has_resource_header = (ib->type == 0x1a); // RESOURCE
				break;
			}
		}
		if (!name) continue;
		// Compute payload pointer + length per body shape.
		// item_bodies[t].size: 0 = variable (size-field is byte length), N>0
		// = fixed inline value (size-field IS the value, N bytes).
		uint8_t fixed_sz = item_bodies[ib->type].size;
		const uint8_t* payload;
		uint32_t length;
		if (fixed_sz == 0) {
			payload = ib->data;
			length = ib->size;
		} else {
			payload = (const uint8_t*)&ib->size;
			length = fixed_sz;
		}
		if (has_resource_header) {
			// RESOURCE bodies in the runtime's text output carry a header
			// line:
			//   `.data RESOURCE <a> <b> <c> <d>`
			// where the four numbers come from the 16-byte ResHdr that
			// precedes the variable resource bytes. Until the header
			// layout is fully decoded across all RESOURCE shapes, fall
			// back to plain `.data RESOURCE` without the four numbers —
			// the runtime still accepts it on re-load (the header is
			// rebuilt from the bytes themselves).
			oprintf(".data %s\n", name);
		} else {
			oprintf(".data %s\n", name);
		}
		print_data_block_hex(payload, length);
		oputs(".enddata\n");
	}
}

// Emit a synthetic `Resource Id: <decimal>` child line if the item carries
// a RESOURCEID body (0x15). The runtime writer prints this line at
// indent+1 between the parent's main line and its real children. The body
// is a 2-byte fixed value at &item_body->size. Only emit in text mode
// (binary outputs already preserve the body in the .app), and only for
// non-imported items (the runtime does NOT emit synthetic `Resource Id:`
// lines for items pulled in by File Include from a library .apl — the
// library carries them already; emitting here would create duplicate
// `Duplicate symbol` errors at cbi -b time). Triggered for
// Menu (0x128), Menu Item (0xa2), Windows Menu (0x12c), Toolbar Button
// (0x29c), and any other item type whose binary form carries a
// RESOURCEID body — same general gate as `.data` emission.
static void print_synth_resource_id(class COutline* outline, uint64_t item_id, uint32_t indention) {
	if (is_binary_app_output()) return;
	tagITEM* p_item = outline->get_item(item_id);
	if (!p_item) return;
	if (p_item->flags & 0x400) return; // imported — library carries it
	struct ItemBody* ib = CItem::get_itembody(outline, item_id, 0x15);
	if (!ib) return;
	uint16_t value = ib->size; // RESOURCEID is 2-byte fixed: value at &ib->size
	print_indent(indention + 1);
	oprintf("Resource Id: %u\n", value);
}

// Helper for the WINATTR handle-scan (Title / Status Text / ToolTip
// emission). Validates that handle_id `h` in OSEG `seginf` references a
// length-prefixed UTF-16LE string heap block, and writes the decoded
// chars into out_chars[0..*out_chars_count]. Returns true on success;
// false for invalid handles, tagITEM-tagged blocks (those carry real
// items, not strings), zero-length / out-of-bounds payloads, or lengths
// that imply non-text (odd byte count, empty after null-strip, etc.).
// Layout: `[uint16 length_in_bytes][UTF-16LE chars, usually null-
// terminated][padding to 4-byte boundary]`.
static bool decode_string_handle(class COutline* outline,
                                 uint32_t seginf, uint32_t handle_id,
                                 const char16_t** out_chars, size_t* out_count) {
	if (handle_id == 0 || handle_id > outline->get_max_handle(seginf)) return false;
	if (outline->is_handle_tagitem(seginf, handle_id)) return false;
	uint8_t* raw = outline->get_handle_data(seginf, handle_id);
	if (!raw) return false;
	uint32_t blk = outline->get_handle_data_size(seginf, handle_id);
	if (blk < 2) return false;
	uint16_t length_bytes = (uint16_t)raw[0] | ((uint16_t)raw[1] << 8);
	// Bounds: length+2 (for the length field itself) must fit in the block.
	// Guard against junk bodies that happen to pass the handle-tag check.
	if (length_bytes < 2 || length_bytes > blk - 2 || (length_bytes & 1)) return false;
	const char16_t* chars = (const char16_t*)(raw + 2);
	size_t n = length_bytes / 2;
	while (n > 0 && chars[n - 1] == 0) n--;
	if (n == 0) return false;
	// Reject obviously non-text payloads: any embedded NUL or control char
	// other than \t/\r/\n. Real menu/control titles are printable strings
	// (sometimes with `&` mnemonic and the occasional accented char).
	for (size_t i = 0; i < n; i++) {
		uint16_t c = (uint16_t)chars[i];
		if (c == 0) return false;
		if (c < 0x20 && c != '\t' && c != '\r' && c != '\n') return false;
	}
	*out_chars = chars;
	*out_count = n;
	return true;
}

// Per-(item-type, slot) WINATTR offset table. Each entry says: "for items
// of type T, the runtime's pseudo-child <slot> is the string handle stored
// at WINATTR byte offset N".
struct WinAttrStringSlot {
	uint16_t item_type;
	const char* slot_label; // emitted verbatim: "Title:" / "Status Text:" /
	                        //                   "ToolTip:" / "Picture File Name:"
	uint16_t winattr_offset; // u16-aligned offset of the handle-id in WINATTR
};
static const WinAttrStringSlot kWinAttrStringSlots[] = {
	// Form Window (0x01)
	{ 0x0001, "Title:",              24 },
	// Table Window (0x02)
	{ 0x0002, "Title:",              24 },
	// Pushbutton (0x06)
	{ 0x0006, "Title:",              36 },
	{ 0x0006, "Picture File Name:", 124 },
	{ 0x0006, "ToolTip:",           152 },
	// Radio Button (0x07)
	{ 0x0007, "Title:",              36 },
	// Check Box (0x08)
	{ 0x0008, "Title:",              36 },
	// Group Box (0x09)
	{ 0x0009, "Title:",             118 },
	// Background Text (0x0c)
	{ 0x000c, "Title:",             118 },
	// Column (0x0d)
	{ 0x000d, "Title:",              36 },
	// MDI Window (0x13)
	{ 0x0013, "Title:",              24 },
	// Option Button (0x14)
	{ 0x0014, "Title:",              36 },
	{ 0x0014, "Picture File Name:", 120 },
	// Dialog Box (0x42)
	{ 0x0042, "Title:",              24 },
	// Menu Item (0xa2)
	{ 0x00a2, "Title:",               6 },
	{ 0x00a2, "Status Text:",        20 },
	// Popup Menu (0xb8)
	{ 0x00b8, "Title:",               6 },
	{ 0x00b8, "Status Text:",        20 },
	// Form Window Class (0xf7) — when used as a class header
	{ 0x00f7, "Title:",               6 },
	// Pushbutton Class (0xfc)
	{ 0x00fc, "Title:",               6 },
	// Quest Table Window (0x112)
	{ 0x0112, "Title:",              24 },
	// Menu (0x128)
	{ 0x0128, "Title:",              14 },
	{ 0x0128, "Status Text:",        20 },
	// Windows Menu (0x12c)
	{ 0x012c, "Title:",              14 },
	{ 0x012c, "Status Text:",        20 },
	// Tab (0x240) — older Tab Bar Tab
	{ 0x0240, "Title:",              28 },
	// Grid Window (0x25c)
	{ 0x025c, "Title:",              24 },
	// Pane Separator (0x282)
	{ 0x0282, "Title:",              40 },
	// Tab (0x2bd) — Ribbon-style Tab
	{ 0x02bd, "Title:",               6 },
	// Button (0x2c0) — Ribbon Button
	{ 0x02c0, "Title:",              10 },
	{ 0x02c0, "Picture File Name:",  16 },
	{ 0x02c0, "ToolTip:",            28 },
	// Group (0x2c1) — Ribbon Group
	{ 0x02c1, "Title:",               6 },
	// Dropdown (0x2c2) — Ribbon Dropdown
	{ 0x02c2, "Title:",               6 },
	{ 0x02c2, "ToolTip:",            12 },
	{ 0x02c2, "Picture File Name:",  22 },
	// Check Button (0x2c6) — Ribbon Check Button
	{ 0x02c6, "Title:",              10 },
	{ 0x02c6, "Picture File Name:",  16 },
	// Radio Button (0x2c7) — Ribbon Radio Button
	{ 0x02c7, "Title:",              10 },
	{ 0x02c7, "Picture File Name:",  16 },
	{ 0x02c7, "ToolTip:",            28 },
	// Combo (0x2c8) — Ribbon Combo
	{ 0x02c8, "Title:",              10 },
	{ 0x02c8, "ToolTip:",            36 },
	// DataField (0x2c9) — Ribbon DataField
	{ 0x02c9, "Title:",              10 },
	{ 0x02c9, "ToolTip:",            32 },
};

static void print_synth_winattr_strings(class COutline* outline, uint64_t item_id,
                                        uint32_t indention) {
	if (is_binary_app_output()) return;
	tagITEM* p_item = outline->get_item(item_id);
	if (!p_item) return;
	if (p_item->flags & 0x400) return; // imported — library carries it
	struct ItemBody* ib = CItem::get_itembody(outline, item_id, 0x14);
	if (!ib) return;
	uint32_t seginf = (uint32_t)(item_id >> ITEM_ID_WIDTH);
	const uint8_t* d = ib->data;
	uint32_t end = ib->size;
	// Walk slot table; emit each slot whose handle id at the registered
	// offset decodes to a valid raw-string heap block.
	for (size_t k = 0; k < sizeof(kWinAttrStringSlots)/sizeof(kWinAttrStringSlots[0]); k++) {
		const WinAttrStringSlot& slot = kWinAttrStringSlots[k];
		if (slot.item_type != p_item->type) continue;
		if ((uint32_t)slot.winattr_offset + 2 > end) continue;
		uint16_t h = (uint16_t)d[slot.winattr_offset]
		           | ((uint16_t)d[slot.winattr_offset + 1] << 8);
		if (h == 0) continue;
		const char16_t* chars = nullptr;
		size_t n = 0;
		if (!decode_string_handle(outline, seginf, h, &chars, &n)) continue;
		print_indent(indention + 1);
		oprintf("%s ", slot.slot_label);
		print_utf16(chars, n * 2);
		oputs("\n");
	}
}

// Per-(item-type) Data Type slot offset in WINATTR. Data Field (0x04) and
// Column (0x0d) both encode the variable's data type as a single byte at
// fixed offsets:
//   1 = Date/Time, 2 = Number, 4 = String, 6 = Long String
// Multiline Field uses "String Type:" rather than "Data Type:" — different
// slot name, not currently emitted.
//
// Why this matters: the runtime's `bx` link pass binds typed call-arguments
// against function Parameters. When `-t` text emission omits the `Data
// Type:` synth-child of a Data Field, the runtime's cx infers the default
// type (which may differ from the original) and bx fails with "Function
// argument N does not match declared data type" / "Assignment of different
// types" for every reference to the variable.
struct WinAttrDataTypeSlot {
	uint16_t item_type;
	uint16_t winattr_offset;
	bool wrap_in_data_block; // true → emit `Data\n  Data Type: T` (Data Field
	                         //         shape); false → emit `Data Type: T`
	                         //         flat (Column shape).
};
static const WinAttrDataTypeSlot kWinAttrDataTypeSlots[] = {
	{ 0x0004, 40, true  },  // Data Field — wraps in `Data` block
	{ 0x000d, 54, false },  // Column — emits `Data Type:` flat
};

static const char* data_type_name(uint8_t v) {
	switch (v) {
		case 1: return "Date/Time";
		case 2: return "Number";
		case 4: return "String";
		case 6: return "Long String";
		default: return nullptr; // unknown / Class Default — skip
	}
}

// Emit `Data` block synthetic-children for a Data Field or Column item:
//
//   <indent+1>  Data
//   <indent+2>  Data Type: <T>
//
// (Only `Data Type:` is emitted — it's the load-bearing slot for the
// runtime's argument-type binding.) Routed via CItem::print_extra_lines's
// normal path. Limited to types where the per-type WINATTR offset is
// known and the byte decodes to a recognized type name (1 / 2 / 4 / 6 —
// anything else falls through silently rather than emit a wrong type).
static void print_synth_data_type(class COutline* outline, uint64_t item_id, uint32_t indention) {
	if (is_binary_app_output()) return;
	tagITEM* p_item = outline->get_item(item_id);
	if (!p_item) return;
	if (p_item->flags & 0x400) return; // imported
	const WinAttrDataTypeSlot* slot = nullptr;
	for (size_t k = 0; k < sizeof(kWinAttrDataTypeSlots)/sizeof(kWinAttrDataTypeSlots[0]); k++) {
		if (kWinAttrDataTypeSlots[k].item_type == p_item->type) {
			slot = &kWinAttrDataTypeSlots[k]; break;
		}
	}
	if (!slot) return;
	struct ItemBody* ib = CItem::get_itembody(outline, item_id, 0x14);
	if (!ib || ib->size <= slot->winattr_offset) return;
	uint8_t byte = ib->data[slot->winattr_offset];
	const char* type_name = data_type_name(byte);
	if (!type_name) return;
	if (slot->wrap_in_data_block) {
		print_indent(indention + 1);
		oputs("Data\n");
		print_indent(indention + 2);
		oprintf("Data Type: %s\n", type_name);
	} else {
		// Column emits Data Type flat at indent+1.
		print_indent(indention + 1);
		oprintf("Data Type: %s\n", type_name);
	}
}

// Per-type geometry slot offsets in WINATTR. The runtime emits a `Window
// Location and Size` block with `Left:` / `Top:` / `Width:` / `Height:`
// synthesised children (values in 1/1000-inch units, 4-byte u32). Each
// item type has its own per-slot offset (the WINATTR prefix length
// differs by type because each type's WINATTR carries type-specific
// fields before the geometry block).
struct WinAttrGeomSlot {
	uint16_t item_type;
	uint16_t left_off, top_off, width_off, height_off;
};
static const WinAttrGeomSlot kWinAttrGeomSlots[] = {
	// Form Window (0x01)
	{ 0x0001,  86,  98, 110, 126 },
	// Table Window (0x02)
	{ 0x0002,  74,  86,  98, 114 },
	// Child Table (0x03)
	{ 0x0003,  36,  48,  60,  76 },
	// Data Field (0x04)
	{ 0x0004,  52,  64,  76,  92 },
	// Multiline Field (0x05)
	{ 0x0005,  64,  76,  88, 104 },
	// Pushbutton (0x06)
	{ 0x0006,  42,  54,  66,  82 },
	// Radio Button (0x07)
	{ 0x0007,  42,  54,  66,  82 },
	// Check Box (0x08)
	{ 0x0008,  42,  54,  66,  82 },
	// Group Box (0x09)
	{ 0x0009,  28,  40,  52,  68 },
	// Horizontal Scroll Bar (0x0a)
	{ 0x000a,  36,  48,  60,  76 },
	// Background Text (0x0c)
	{ 0x000c,  28,  40,  52,  68 },
	// Column (0x0d) — only Width slot (Column has no Left/Top)
	{ 0x000d,   0,   0,  66,   0 },
	// List Box (0x0e)
	{ 0x000e,  36,  48,  60,  76 },
	// Combo Box (0x0f)
	{ 0x000f,  36,  48,  60,  76 },
	// Frame (0x10)
	{ 0x0010,  28,  40,  52,  68 },
	// Picture (0x12)
	{ 0x0012,  36,  48,  60,  76 },
	// MDI Window (0x13)
	{ 0x0013,  58,  70,  82,  98 },
	// Option Button (0x14)
	{ 0x0014,  42,  54,  66,  82 },
	// Dialog Box (0x42)
	{ 0x0042,  58,  70,  82,  98 },
	// Combo Box Class (0x103)
	{ 0x0103,   6,  18,  30,  46 },
	// MDI Window Class (0x120) — Width/Height differ from Left/Top
	{ 0x0120,  40,  52,  64,  80 },
	// Date Picker (0x225)
	{ 0x0225,   0,  48,  60,  76 },
	// Date Time Picker (0x22c)
	{ 0x022c,  36,  48,  60,  76 },
	// Child Grid (0x235)
	{ 0x0235,  36,  48,  60,  76 },
	// Tab Bar (0x23a)
	{ 0x023a,   0,   0,  60,  76 },
	// Rich Text Control (0x245)
	{ 0x0245,  52,  64,  76,  92 },
	// Grid Window (0x25c)
	{ 0x025c,   0,   0,  98, 114 },
	// Tree Control (0x26b)
	{ 0x026b,   0,  54,  66,  82 },
};

static void print_synth_form_geometry(class COutline* outline, uint64_t item_id, uint32_t indention) {
	if (is_binary_app_output()) return;
	tagITEM* p_item = outline->get_item(item_id);
	if (!p_item) return;
	if (p_item->flags & 0x400) return; // imported — library carries it
	const WinAttrGeomSlot* slot = nullptr;
	for (size_t k = 0; k < sizeof(kWinAttrGeomSlots)/sizeof(kWinAttrGeomSlots[0]); k++) {
		if (kWinAttrGeomSlots[k].item_type == p_item->type) {
			slot = &kWinAttrGeomSlots[k]; break;
		}
	}
	if (!slot) return;
	struct ItemBody* ib = CItem::get_itembody(outline, item_id, 0x14);
	if (!ib) return;
	const uint8_t* d = ib->data;
	uint32_t end = ib->size;
	auto u32_at = [&](uint32_t off) -> uint32_t {
		if (off + 4 > end) return 0;
		return (uint32_t)d[off] | ((uint32_t)d[off+1] << 8)
		     | ((uint32_t)d[off+2] << 16) | ((uint32_t)d[off+3] << 24);
	};
	uint32_t L = slot->left_off ? u32_at(slot->left_off) : 0;
	uint32_t T = slot->top_off ? u32_at(slot->top_off) : 0;
	uint32_t W = slot->width_off ? u32_at(slot->width_off) : 0;
	uint32_t H = slot->height_off ? u32_at(slot->height_off) : 0;
	// Skip if all four are 0 (entirely Default — no Window Location and
	// Size block needed).
	if (L == 0 && T == 0 && W == 0 && H == 0) return;
	// Decide whether to wrap in `Window Location and Size`. Form / Table /
	// Dialog Box / Frame / Group Box / etc. emit the wrapper plus L/T/W/H
	// as nested children. But Column (0x0d) emits `Width:` directly under
	// Column without the wrapper — wrapping it triggers a "This item type
	// is not allowed here" error at cx time. Heuristic: types with NO
	// Left/Top slot (only Width or Height) emit slots flat at indent+1;
	// everything else wraps.
	bool use_wrapper = (slot->left_off != 0) || (slot->top_off != 0);
	uint32_t base_indent = indention + 1 + (use_wrapper ? 1 : 0);
	auto emit_inch = [&](const char* label, uint16_t off, uint32_t value) {
		if (!off) return; // slot not registered for this type — skip
		print_indent(base_indent);
		oprintf("%s ", label);
		if (value == 0) {
			oputs("Default\n");
		} else {
			uint32_t whole = value / 1000;
			uint32_t frac = value % 1000;
			char buf[32];
			snprintf(buf, sizeof(buf), "%u.%03u", whole, frac);
			size_t len = 0;
			while (buf[len]) len++;
			while (len > 0 && buf[len-1] == '0') { buf[--len] = 0; }
			if (len > 0 && buf[len-1] == '.') { buf[--len] = 0; }
			oprintf("%s\"\n", buf);
		}
	};
	if (use_wrapper) {
		print_indent(indention + 1);
		oputs("Window Location and Size\n");
	}
	emit_inch("Left:",   slot->left_off,   L);
	emit_inch("Top:",    slot->top_off,    T);
	emit_inch("Width: ", slot->width_off,  W); // note trailing space — matches the runtime writer
	emit_inch("Height:", slot->height_off, H);
}

// Decode a Menu Item's WINATTR trailing 5 bytes
// `<vk> <modifier> 00 00 00` into the canonical
// `Keyboard Accelerator: <text>` line.
//
//   modifier byte:  0x00 = (none)
//                   0x10 = Shift+
//                   0x11 = Ctrl+
//                   0x12 = Alt+
//                   0x13 = Shift+Ctrl+
//                   0x14+ = unknown — emitted as `Mod0xNN+`
//   vk code: standard Windows VK_* values (0x08/BkSp, 0x0d/Enter,
//            0x21/PgUp, 0x2d/Ins, 0x2e/Del, 0x70-0x7B/F1-F12, ...);
//            ASCII letters/digits use their ASCII code; unknown VKs
//            fall back to `VK_0xNN`.
//
// Both bytes 0 → emit `(none)`. The runtime writer always emits the line
// (even `Keyboard Accelerator: (none)`), so we always emit too.
//
// Limited to Menu Item (0xa2). Pushbutton / Check Box / Radio Button
// accelerators are stored elsewhere in their (much larger) WINATTR —
// different encoding, not currently decoded.
static const char* vk_name(uint8_t vk, char* tmp, size_t tmp_sz) {
	switch (vk) {
	case 0x08: return "BkSp";
	case 0x09: return "Tab";
	case 0x0d: return "Enter";
	case 0x1b: return "Esc";
	case 0x20: return "Space";
	case 0x21: return "PgUp";
	case 0x22: return "PgDn";
	case 0x23: return "End";
	case 0x24: return "Home";
	case 0x25: return "Left";
	case 0x26: return "Up";
	case 0x27: return "Right";
	case 0x28: return "Down";
	case 0x2d: return "Ins";
	case 0x2e: return "Del";
	case 0x6a: return "Multiply";
	case 0x6b: return "Add";
	case 0x6d: return "Subtract";
	case 0x6e: return "Decimal";
	case 0x6f: return "Divide";
	case 0x70: return "F1";
	case 0x71: return "F2";
	case 0x72: return "F3";
	case 0x73: return "F4";
	case 0x74: return "F5";
	case 0x75: return "F6";
	case 0x76: return "F7";
	case 0x77: return "F8";
	case 0x78: return "F9";
	case 0x79: return "F10";
	case 0x7a: return "F11";
	case 0x7b: return "F12";
	}
	if (vk >= '0' && vk <= '9') {
		tmp[0] = (char)vk; tmp[1] = '\0';
		return tmp;
	}
	if (vk >= 'A' && vk <= 'Z') {
		tmp[0] = (char)vk; tmp[1] = '\0';
		return tmp;
	}
	if (vk >= 0x60 && vk <= 0x69) {
		// numpad 0..9 — TD's exact name unverified; "Num0".."Num9" is
		// a reasonable Microsoft-aligned guess
		snprintf(tmp, tmp_sz, "Num%u", (unsigned)(vk - 0x60));
		return tmp;
	}
	snprintf(tmp, tmp_sz, "VK_0x%02x", (unsigned)vk);
	return tmp;
}

static void print_synth_keyboard_accelerator(class COutline* outline,
                                             uint64_t item_id,
                                             uint32_t indention) {
	if (is_binary_app_output()) return;
	tagITEM* p_item = outline->get_item(item_id);
	if (!p_item) return;
	if (p_item->type != 0x00a2) return; // Menu Item only — see comment above
	if (p_item->flags & 0x400) return;  // imported — library carries it
	struct ItemBody* ib = CItem::get_itembody(outline, item_id, 0x14);
	if (!ib || ib->size < 5) return;
	const uint8_t* tail = ib->data + (ib->size - 5);
	uint8_t vk = tail[0];
	uint8_t mod = tail[1];
	// Trailing 3 bytes must be zero (sanity check — bail silently otherwise
	// to avoid emitting bogus accelerators on items whose WINATTR doesn't
	// follow the trailer convention).
	if (tail[2] || tail[3] || tail[4]) return;
	print_indent(indention + 1);
	oputs("Keyboard Accelerator: ");
	if (vk == 0 && mod == 0) {
		oputs("(none)\n");
		return;
	}
	switch (mod) {
	case 0x00: break;
	case 0x10: oputs("Shift+"); break;
	case 0x11: oputs("Ctrl+"); break;
	case 0x12: oputs("Alt+"); break;
	case 0x13: oputs("Shift+Ctrl+"); break;
	default: oprintf("Mod0x%02x+", (unsigned)mod); break;
	}
	char tmp[16];
	oprintf("%s\n", vk_name(vk, tmp, sizeof(tmp)));
}

void CItem::print_extra_lines(class COutline* outline, uint64_t item_id, uint32_t indention) {
	// Synthetic pseudo-children that the runtime writer emits but don't
	// exist as separate items in the binary outline:
	// 1. `Resource Id: <decimal>` from the RESOURCEID body (if present)
	// 2. `Title: <text>` and `Status Text: <text>` from raw-string handles
	//    referenced inside the WINATTR body
	// 3. `Keyboard Accelerator: <text>` for Menu Items (see helper above)
	// 4. `Window Location and Size` block (see print_synth_form_geometry)
	// 5. `.data <NAME> ... .enddata` blocks for any binary-shaped body
	// Order matches the runtime's own emission order (synthetic-children
	// first, then .data blocks at column 0). Real children come after via
	// iterate_items's normal recursion.
	print_synth_resource_id(outline, item_id, indention);
	print_synth_winattr_strings(outline, item_id, indention);
	print_synth_data_type(outline, item_id, indention);
	print_synth_keyboard_accelerator(outline, item_id, indention);
	print_synth_form_geometry(outline, item_id, indention);
	print_data_blocks(outline, item_id);
}


class COutlineVersion : public CItem {

public:
	COutlineVersion() : CItem(NULL) {
	}

	virtual void print(class COutline* outline, uint64_t item_id, uint64_t* memory_item){
		uint16_t ver = 0;
		if (outline->get_file_hdr().version < VERSION_TD52) {
			// outline version of TD5.1 is 37; older versions are not supported (yet)
			ver = 37;
		}else{
			// TD5.2 - TD7.4 follow this pattern
			ver = outline->get_file_hdr().version + 39 - VERSION_TD52;
		}
		oprintf("Outline Version - 4.0.%u",ver);
	}

	virtual ~COutlineVersion() {
	}
};

// Items whose printable form is "<name> <decimal>" with the decimal coming
// from a 4-byte numeric item body. cbi -b binds External Function
// declarations to DLL exports by Export Ordinal when the SAL function name
// doesn't match the DLL's literal export name. Without the value printed,
// cbi falls back to name-only resolution and reports "Cannot find function
// within external library". Same applies to `Resource Id:` for Menu /
// Menu Item: bodies and other simple-numeric outline rows where text
// decompile must preserve the value.
class CNumericItem : public CItem {
	uint8_t body_type;
public:
	CNumericItem(const char* name, uint8_t body_type)
		: CItem(name), body_type(body_type) {
	}

	virtual void print(class COutline* outline, uint64_t item_id, uint64_t* memory_item) {
		// Emit the standard "<name>" prefix (and any TEXT/symbol-lookup body
		// the base class would already handle).
		CItem::print(outline, item_id, memory_item);
		// Then append the numeric value if present. Skip in verbose mode —
		// `print_all_itembodies` already emits it as "INT:0x..." / "ORDINAL:0x..."
		// and a second copy would duplicate.
		if (is_verbose()) return;
		struct ItemBody* ib = get_itembody(outline, item_id, body_type);
		if (!ib) return;
		uint32_t v = 0;
		// item_bodies[].size = 4 for INT (0x02) and ORDINAL (0x22) — the
		// numeric value sits inline at &item_body->size (same layout
		// print_all_itembodies uses for 4-byte bodies).
		memcpy(&v, &ib->size, sizeof(v));
		// Skip 0 — cbi-c treats blank `Export Ordinal:` as "unset, fall back
		// to name match", but `Export Ordinal: 0` as "bind to ordinal 0"
		// (invalid: DLL ordinals start at 1). Sita-emitted External Function
		// declarations with no explicit ordinal carry a zero-valued body 0x22;
		// printing it would break name-match resolution everywhere.
		if (v == 0) return;
		oprintf(" %u", v);
	}

	virtual ~CNumericItem() {
	}
};

// Items whose printable form is "<name> Yes|No". The runtime writer always
// emits the Yes/No suffix because the cx step defaults a missing value to
// the opposite of what the bx step expects for visibility-modifier rows.
// Affects `Protected Variable:` / `Protected Function:` (LIST body 0x05;
// non-zero = Yes, zero = No). Without the value, bx falls back to
// "protected" and external references fail with "Symbol is undefined or
// unable to be referenced from current location".
class CYesNoItem : public CItem {
	uint8_t body_type;
public:
	CYesNoItem(const char* name, uint8_t body_type)
		: CItem(name), body_type(body_type) {
	}

	virtual void print(class COutline* outline, uint64_t item_id, uint64_t* memory_item) {
		CItem::print(outline, item_id, memory_item);
		if (is_verbose()) return;
		struct ItemBody* ib = get_itembody(outline, item_id, body_type);
		// Body present at all? The runtime always emits one; absent should
		// not happen on real samples, but if it does, fall back silently
		// to avoid printing a bogus value.
		if (!ib) return;
		uint32_t v = 0;
		memcpy(&v, &ib->size, sizeof(v));
		oputs(v ? " Yes" : " No");
	}

	virtual ~CYesNoItem() {
	}
};

uint32_t CItem::get_funcvar_typedef(class COutline* outline, uint64_t item_id) {
	struct ItemBody* item_body = CItem::get_itembody(outline, item_id, 0x14);
	if (item_body && item_body->size >= 7) {
		if (item_body->data[0] == 0x05) {
#ifndef TDx64
			return *(uint32_t*)&item_body->data[4];
#else
			// Function returns uint32_t; the 64-bit body field is wider but
			// only the low 32 bits identify a typedef. Explicit narrowing
			// silences MSVC C4244.
			return (uint32_t)*(uint64_t*)&item_body->data[4];
#endif
		}
	}
	return 0;
}

class CFunctionalVar : public CItem {

public:
	CFunctionalVar() : CItem(NULL) {
	}
	virtual void print(class COutline* outline, uint64_t item_id, uint64_t* memory_item){
		oputs("FunctionalVar:");
		const char16_t* str = outline->symbol_lookup(item_id);
		if (!str) {
			struct ItemBody* itb = get_itembody(outline, item_id, 0x01);
			if (itb) {
				str = (const char16_t*)itb->data;
			}
		}
		if (str) {
			oputs(" ");
			print_utf16(str, strlen_utf16(str));
		}

		CItem::print_array_boundaries(outline, item_id);

		// CLASS_CONSTRUCTOR (0x37) carries the declaration's initializer hint.
		// Value 0x0001 corresponds to `= OBJ_Null` (the default-null form seen
		// in TD samples). Other values likely encode `= new ClassX` but we
		// don't have a test case — leave those unhandled for now.
		struct ItemBody* ctor = get_itembody(outline, item_id, 0x37);
		if (ctor) {
			uint16_t val = *((uint16_t*)&ctor->size);
			if (val == 0x0001) {
				oputs(" = OBJ_Null");
			}
		}

		if (is_verbose()) {
			print_all_itembodies(outline, item_id);
		}
	}

	// Emit the SAL `Class: <ClassName>` binding so cbi -b can resolve member
	// accesses (`var.field`). The class name lives in an auxiliary heap
	// block of the same OSEG, referenced by WINATTR's bytes [2:4] (uint16
	// LE handle_id). Without this child line, cbi -c writes a .app whose
	// FunctionalVar item has WINATTR data[2:4]=0 and no class-name heap
	// block — cbi -b then fails with "Symbol is undefined" on every member
	// access.
	virtual void print_extra_lines(class COutline* outline, uint64_t item_id, uint32_t indention) {
		struct ItemBody* ib = get_itembody(outline, item_id, 0x14);
		if (!ib || ib->size < 4) {
			return;
		}
		// data[0:2] is the variable-kind discriminator; only 0x0105 (FunctionalVar)
		// uses the class-name handle at data[2:4]. Other kinds may overload the slot.
		if (ib->data[0] != 0x05 || ib->data[1] != 0x01) {
			return;
		}
		uint16_t handle_id = (uint16_t)ib->data[2] | ((uint16_t)ib->data[3] << 8);
		if (!handle_id) {
			return;
		}
		uint32_t seginf = (uint32_t)(item_id >> ITEM_ID_WIDTH);
		uint8_t* raw = outline->get_handle_data(seginf, handle_id);
		if (!raw) {
			return;
		}
		// Heap-block payload: [uint16 length_in_bytes][UTF-16LE chars, possibly
		// null-terminated][padding to 4-byte boundary].
		uint16_t length_bytes = (uint16_t)raw[0] | ((uint16_t)raw[1] << 8);
		if (length_bytes < 2 || (length_bytes & 1)) {
			return;
		}
		const char16_t* name = (const char16_t*)(raw + 2);
		// Strip a trailing null character (the on-disk string is usually
		// null-terminated within the length).
		size_t chars = length_bytes / 2;
		while (chars > 0 && name[chars - 1] == 0) {
			chars--;
		}
		if (chars == 0) {
			return;
		}
		print_indent(indention + 1);
		oputs("Class: ");
		print_utf16(name, chars * 2);
		oputs("\n");
		// Also emit any `.data` blocks attached to the FunctionalVar item —
		// CFunctionalVar overrides print_extra_lines to add the synthetic
		// Class line, so it must call the base emission path explicitly to
		// keep .data parity with other items.
		CItem::print_data_blocks(outline, item_id);
	}

	virtual ~CFunctionalVar() {
	}
};

/**
 * represents item types that contain a line of code
 */
class CStatement : public CItem {
private:
	datatype expected_datatype;
public:
	CStatement(const char* str, datatype expected_datatype = datatype::ANY) : CItem(str), expected_datatype(expected_datatype) {
	}
	/**
	 * decompile corresponding line of code
	 */
	virtual void print(class COutline* outline, uint64_t item_id, uint64_t* memory_item){
		//bool tmp = DEBUG;
		//DEBUG = false;
		CItem::print(outline, item_id, memory_item);
		//DEBUG = tmp;

		AVOID_COMPILED_UNCOMPILED_DUPLICATES

		// compiled
		struct ItemBody* item_body = get_itembody(outline, item_id, 0x09);
		if (item_body && item_body->size > 0) {
			oputs(" ");
			struct CompileBlock* compile_block = (struct CompileBlock*)item_body->data;
			if (compile_block->size > 0 && compile_block->start > 0) {
				struct DecompileInfo di = {
						outline,
						memory_item,
						compile_block,
						(struct tagOPERATOR*)((char*)compile_block+compile_block->start),
						this->expected_datatype,
						varscope::NONE,
						0xff,
						NULL,
						NULL,
						0,  // caller_arg_count: not in call context here
				};
				decompile_expression(di);
			}
		}

	}
	virtual ~CStatement() {
	}
};

/**
 * represents item types that contain a line of code
 */
class CLoop : public CItem {

private:
	static uint64_t last_loop_id;

public:
	CLoop() : CItem("Loop") {
	}
	/**
	 * decompile corresponding line of code
	 */
	virtual void print(class COutline* outline, uint64_t item_id, uint64_t* memory_item){
		CItem::print(outline, item_id, memory_item);

		if (outline->get_item_loop_info(item_id)) {
			outline->set_item_loop_info(item_id, ++CLoop::last_loop_id);
			oprintf(" loop_%llu",CLoop::last_loop_id);
		}
	}

	virtual ~CLoop() {
	}
};

uint64_t CLoop::last_loop_id = 0;

/**
 * represents item types that contain a line of code
 */
class CBreak : public CItem {
public:
	CBreak(const char* name) : CItem(name) {
	}
	/**
	 * decompile corresponding line of code
	 */
	virtual void print(class COutline* outline, uint64_t item_id, uint64_t* memory_item){
		CItem::print(outline, item_id, memory_item);

		struct ItemBody* item_body = get_itembody(outline, item_id, 0x03);
		if (item_body) {
			uint64_t item_ref = 0;
			memcpy(&item_ref,&item_body->size,item_bodies[0x03].size);
			tagITEM* item_p = outline->get_item(item_ref);
			if (item_p) {
				if (item_p->type == Item::Type::LOOP) {
					uint64_t loop_id = outline->get_item_loop_info(item_ref);
					if (loop_id) {
						oprintf(" loop_%u",loop_id);
					}
				}
			}
		}
	}

	virtual void first_pass(COutline* outline, uint64_t item_id, uint64_t* memory_item) {
		CItem::first_pass(outline, item_id, memory_item);
		struct ItemBody* item_body = get_itembody(outline, item_id, 0x03);
		if (item_body) {
			uint64_t item_ref = 0;
			memcpy(&item_ref,&item_body->size,item_bodies[0x03].size);
			tagITEM* item_p = outline->get_item(item_ref);
			if (item_p) {
				if (item_p->type == Item::Type::LOOP) {
					outline->set_item_loop_info(item_ref, 1);
				}
			}
		}
	}

	virtual ~CBreak() {
	}
};

/**
 * represents item types that contain a line of code
 */
class CCase : public CItem {
public:
	CCase() : CItem("Case") {
	}
	/**
	 * decompile corresponding line of code
	 */
	virtual void print(class COutline* outline, uint64_t item_id, uint64_t* memory_item){
		CItem::print(outline, item_id, memory_item);

		struct ItemBody* item_body = get_itembody(outline, item_id, 0x03);
		if (item_body) {
			uint64_t num = 0;
			memcpy(&num,&item_body->size,item_bodies[0x03].size);
			oprintf(" %llu",num);
		}
	}

	virtual ~CCase() {
	}
};

/**
 * represents item types that contain a line of code
 */
class CVar : public CItem {
protected:
	void decompile_helper(class COutline* outline, uint64_t item_id,const char16_t* assigned_value) {
		if (is_binary_app_output() && !get_itembody(outline, item_id, 0x01)) {

			const char16_t* str = outline->symbol_lookup(item_id);
			if (str) {
				size_t len = strlen_utf16(str)+2;
				if (len) {

					size_t assign_len = 0;
					if (assigned_value && *assigned_value) {
						assign_len = 6 + strlen_utf16(assigned_value);
					}

					// Array variables: source-form `.app` stores the array-
					// ness as a suffix in the name string itself
					// (`dArray[*]`, `nMatrix[10,5]`, …) — NOT in the runtime
					// ARRAYBOUNDS / MDARRAYBOUNDS bodies (those are
					// recomputed at compile time by cbi -b). When Sita reads
					// a `.exe`, it sees the runtime bodies but the symbol's
					// stored name lacks the suffix. Without appending the
					// suffix here, the resulting `.app` rebuilds but cbi -b
					// then errors out with "Array variable expected" /
					// "Window handle variable or array required" for every
					// reference to the variable — it doesn't know the
					// variable is an array because no `[...]` is in the
					// name.
					char arr_buf[128];
					size_t arr_n = format_array_suffix(outline, item_id, arr_buf, sizeof(arr_buf));
					size_t arr_utf16 = arr_n * 2; // ASCII → UTF-16LE: each char becomes 2 bytes

					struct ItemBody* out = alloc<struct ItemBody*>(sizeof(struct ItemBody)+len+arr_utf16+assign_len);
					out->type = 0x01;
					out->size = (uint16_t)(len + arr_utf16 + assign_len);
					memcpy(out->data,str,len);

					if (arr_n) {
						// Insert array suffix right before the existing
						// trailing NUL (positions [len-2, len-1] are the
						// original NUL pair). Shift NUL to after the suffix.
						uint8_t* p = out->data + len - 2;
						for (size_t i = 0; i < arr_n; i++) {
							*p++ = (uint8_t)arr_buf[i];
							*p++ = 0;
						}
						*p++ = 0;
						*p = 0;
					}

					if (assign_len) {
						char16_t equals[3] = {' ','=',' '};
						memcpy(out->data+len+arr_utf16-2,equals,6);
						memcpy(out->data+len+arr_utf16+4,assigned_value,assign_len-4);
					}

					add_itembody(outline, item_id, out);
					free(out);
				}
			}
		}
	}

	void decompile_number(class COutline* outline, uint64_t item_id, void (*sprint_num)(char*,const struct SalNumber*)){
		if (is_binary_app_output() && !get_itembody(outline, item_id, 0x01)) {
			char buf[300];
			*buf = 0;
			struct ItemBody* item_body = get_itembody(outline, item_id, 0x2e);
			if (item_body) {
				sprint_num(buf, (SalNumber*)item_body->data);
			}
			size_t buf_len = strlen(buf)+1;

			// convert to UTF-16
			size_t out_len = 2*buf_len;
			char* out = alloc<char*>(out_len);
			char* out_buffer = out;
			char* in = buf;
#ifdef __unix__ 
			iconv_t str_convert = iconv_open("UTF-16LE", "UTF-8");
			iconv(str_convert, (char**)&in, &buf_len, &out_buffer, &out_len);
			iconv_close(str_convert);
#else
			out_len = MultiByteToWideChar(CP_UTF8, 0, (LPCCH)in, (int)buf_len, (LPWSTR)out_buffer, (int)out_len);
			out_buffer += 2*out_len;
#endif

			decompile_helper(outline, item_id, (const char16_t*)out);
			free(out);
		}
	}

public:
	CVar(const char* str) : CItem(str) {
	}
	/**
	 * handle array
	 */
	virtual void print(class COutline* outline, uint64_t item_id, uint64_t* memory_item){
		CItem::print(outline, item_id, memory_item);
		CItem::print_array_boundaries(outline, item_id);
	}
	virtual ~CVar() {
	}
};

/**
 * represents preinitialized constant variable
 */
class CNumber : public CVar {
public:
	CNumber() : CVar("Number:") {
	}

	virtual void print(class COutline* outline, uint64_t item_id, uint64_t* memory_item){
		CItem::print(outline, item_id, memory_item);
		CItem::print_array_boundaries(outline, item_id);

		struct ItemBody* item_body = get_itembody(outline, item_id, 0x2e);
		if (item_body) {
			oputs(" = ");
			print_number((SalNumber*)item_body->data);
		}
	}

	virtual void decompile(class COutline* outline, uint64_t item_id, uint64_t* memory_item){
		if (is_binary_app_output() && !get_itembody(outline, item_id, 0x01)) {
			decompile_number(outline, item_id, sprint_number);
		}
	}

	virtual ~CNumber() {
	}
};

/**
 * represents preinitialized constant variable
 */
class CDateTime : public CVar {
public:
	CDateTime() : CVar("Date/Time:") {
	}

	virtual void print(class COutline* outline, uint64_t item_id, uint64_t* memory_item){
		CItem::print(outline, item_id, memory_item);
		CItem::print_array_boundaries(outline, item_id);

		struct ItemBody* item_body = get_itembody(outline, item_id, 0x2e);
		if (item_body) {
			oputs(" = ");
			print_date((SalNumber*)item_body->data);
		}
	}

	virtual void decompile(class COutline* outline, uint64_t item_id, uint64_t* memory_item){
		if (is_binary_app_output() && !get_itembody(outline, item_id, 0x01)) {
			decompile_number(outline, item_id, sprint_date);
		}
	}

	virtual ~CDateTime() {
	}
};

/**
 * represents preinitialized constant variable
 */
class CBoolean : public CVar {
public:
	CBoolean() : CVar("Boolean:") {
	}

	virtual void print(class COutline* outline, uint64_t item_id, uint64_t* memory_item){
		CItem::print(outline, item_id, memory_item);
		CItem::print_array_boundaries(outline, item_id);

		struct ItemBody* item_body = get_itembody(outline, item_id, 0x2e);
		if (item_body) {
			oprintf(" = %s",boolval((SalNumber*)item_body->data)?"TRUE":"FALSE");
		}
	}

	virtual void decompile(class COutline* outline, uint64_t item_id, uint64_t* memory_item){
		if (is_binary_app_output() && !get_itembody(outline, item_id, 0x01)) {
			decompile_number(outline, item_id, sprint_bool);
		}
	}

	virtual ~CBoolean() {
	}
};

/**
 * represents preinitialized constant variable
 */
class CString : public CVar {
public:
	CString() : CVar("String:") {
	}

	virtual void print(class COutline* outline, uint64_t item_id, uint64_t* memory_item){
		CItem::print(outline, item_id, memory_item);
		CItem::print_array_boundaries(outline, item_id);

		struct ItemBody* item_body = get_itembody(outline, item_id, 0x2e);
		if (item_body) {
			oputs(" = ");
			const struct String* str = outline->string_lookup(*((uint16_t*)item_body->data));
			if (str) {
				print_utf16_quoted(str->str,str->len);
			}else{
				oprintf("[[ref:0x%08x]]",*((uint16_t*)item_body->data));
			}
		}
	}

	virtual void decompile(class COutline* outline, uint64_t item_id, uint64_t* memory_item){
		if (is_binary_app_output() && !get_itembody(outline, item_id, 0x01)) {
			const struct String* str = NULL;
			struct ItemBody* item_body = get_itembody(outline, item_id, 0x2e);
			if (item_body) {
				str = outline->string_lookup(*((uint16_t*)item_body->data));
				if (str) {
					char16_t* quoted = alloc<char16_t*>(2*str->len+6);
					char16_t* buf = quoted;
					*(buf++) = '"';
					for (size_t i=0; i<str->len; i+=2) {
						if (!str->str[i/2]) {
							break;
						}
						if (str->str[i/2] == '"' || str->str[i/2] == '\\') {
							*(buf++) = '\\';
						}
						*(buf++) = str->str[i/2];
					}
					*(buf++) = '"';
					*(buf++) = 0;

					decompile_helper(outline, item_id, quoted);
					free(quoted);
				}else{
					decompile_helper(outline, item_id, NULL);
				}
			}else{
				decompile_helper(outline, item_id, NULL);
			}
		}
	}

	virtual ~CString() {
	}
};

const struct MatchItemsToScope CCON[] = {
		// `On <event>` handlers carry their own Parameters block (e.g.
		// `wParam` / `lParam`, or COM event args like
		// `On evRecordRetrieved(strName, strStreet, …)`). Bytecode
		// references them with var_scope = INTERNAL_FUNCTION_PARAM (0x02).
		// Without this registration the access prints as `sc02_var0000`
		// etc.
		{varscope::INTERNAL_FUNCTION_PARAM, 0x89}, // Parameters
		{varscope::NONE, 0x00}};

const struct MatchItemsToScope CTHREADEVENT[] = {
		// `Thread Events` per-event handlers (`Thread Start`,
		// `Thread Before Start`, `Thread Report Progress`, `Thread Finished`,
		// `Thread Report Error`) inside a `BackgroundWorkerVar:` carry an
		// `Event Parameters` (0x2df) subblock with the event-specific
		// parameter declarations (e.g. `Number: nProgress, String: strProgress`
		// for Thread Report Progress). Bytecode references them with
		// var_scope = INTERNAL_FUNCTION_PARAM (0x02), same as `On <event>`.
		{varscope::INTERNAL_FUNCTION_PARAM, Item::Type::EVENT_PARAMETERS},
		{varscope::NONE, 0x00}};

class COn : public CVarScope {
public:
	COn() : CVarScope("On", CCON) {
	}
	/**
	 * decompile corresponding line of code
	 */
	virtual void print(class COutline* outline, uint64_t item_id, uint64_t* memory_item){
		CItem::print(outline, item_id, memory_item);

		AVOID_COMPILED_UNCOMPILED_DUPLICATES

		struct ItemBody* item_body = get_itembody(outline, item_id, 0x2f);
		if (item_body) {
			oputs(" ");
			if (!get_event_name(item_body)) {
				uint32_t v;
				memcpy(&v, &item_body->size, sizeof(v));
				oprintf("%u",v);
			}else{
				oputs(get_event_name(item_body));
			}
		}
	}
	virtual ~COn() {
	}

	void decompile(class COutline* outline, uint64_t item_id, uint64_t* memory_item) {
		if (is_binary_app_output()) {
			// replace 0x2f itembody by string itembody
			struct ItemBody* item_body = get_itembody(outline, item_id, 0x2f);
			if (item_body) {
				if (!get_event_name(item_body)) {
					char tmp[30];
					uint32_t v;
					memcpy(&v, &item_body->size, sizeof(v));
					sprintf(tmp,"%u",v);
					itembody_add_string(outline, item_id, tmp);
				}else{
					itembody_add_string(outline, item_id, get_event_name(item_body));
				}
			}
			remove_itembody(outline,item_id,0x2f);
		}
	}
};

class CClassDefinitions : public CItem {
private:

	static void callback0(class COutline* outline, uint64_t item, void* param) {
		struct ItemBody* item_body = get_itembody(outline, item, 0x0d);
		if (item_body) {
			uint64_t class_id = 0;
			memcpy(&class_id,&item_body->size,item_bodies[0x0d].size);
			outline->add_class_item(class_id, item);
		}
		uint16_t type[] = {
				Item::Type::CLASS_VARIABLES,
				0
		};
		outline->find_children_of_type_and_run(callback1, &item, item, type, false);
		// Function-static variables (`Static Variables` block inside each
		// Function: of the class) live in the same class-static memory
		// region as Class Variables, accessed by the bytecode via
		// sc=0x0f (STATIC_CLASS_VAR) using the enclosing class's HANDLE +
		// the var's VAROFFSET. To resolve the same way for read/write
		// sites, walk every Function of the class and register each
		// Static Variable child under (class_item, STATIC_CLASS_VAR,
		// var_offset) — same registration shape as CLASS_VARIABLES, just
		// sourced from a deeper subtree. METHODS = 0x117 (rendered as
		// "Functions" in SAL) is the container holding the class's
		// Function: items as NULL-ITEMCLONE children that dereference to
		// the actual Function items in another segment.
		uint16_t methods_type[] = { Item::Type::METHODS, 0 };
		outline->find_children_of_type_and_run(callback_methods, &item, item, methods_type, false);
	}

	static void callback1(class COutline* outline, uint64_t item, void* param) {
		outline->find_children_of_type_and_run(callback2, param, item, NULL, false);
	}
	static void callback2(class COutline* outline, uint64_t item, void* param) {
		addvar(outline, *(uint64_t*)param, varscope::STATIC_CLASS_VAR, item);
	}

	// Walk the METHODS container's children (Functions). For each Function,
	// walk its Static Variables block and register each variable as
	// STATIC_CLASS_VAR of the enclosing class. `param` carries the class
	// item id (same as callback1/2's param convention).
	static void callback_methods(class COutline* outline, uint64_t methods_item, void* param) {
		uint16_t fn_type[] = { Item::Type::INT_FUNCTION, 0 };
		outline->find_children_of_type_and_run(callback_fn, param, methods_item, fn_type, false);
	}
	static void callback_fn(class COutline* outline, uint64_t fn_item, void* param) {
		uint16_t sv_type[] = { Item::Type::STATIC_VARIABLES, 0 };
		outline->find_children_of_type_and_run(callback1, param, fn_item, sv_type, false);
	}

public:
	CClassDefinitions(const char* str) : CItem(str) {
	}

	virtual void first_pass(class COutline* outline, uint64_t item_id, uint64_t* memory_item) {
		CItem::first_pass(outline, item_id, memory_item);
		outline->find_children_of_type_and_run(callback0, NULL, item_id, NULL, false);
	}

	virtual ~CClassDefinitions() {
	}
};


void CGlobalDecs::callback0(class COutline* outline, uint64_t item, void* param) {
	// process all variables declared inside this node
	outline->find_children_of_type_and_run(callback1, param, item, 0, false);
}

void CGlobalDecs::callback1(class COutline* outline, uint64_t item, void* param) {
	addvar(outline, *(uint64_t*)param, varscope::LIB_GLOBALS, item);
}

uint64_t CGlobalDecs::lib_globals = 0;

CGlobalDecs::CGlobalDecs(const char* str) : CItem(str) {
}

void CGlobalDecs::first_pass(class COutline* outline, uint64_t item_id, uint64_t* memory_item) {
	CItem::first_pass(outline, item_id, memory_item);
	uint16_t types[] = {
			Item::Type::VARIABLES,
			0
	};
	if (!lib_globals) {
		lib_globals = item_id;
	}
	outline->find_children_of_type_and_run(callback0, &lib_globals, item_id, types, false);
}

void CGlobalDecs::preprocess(class COutline* outline, uint64_t item_id, uint64_t* memory_item) {
	CItem::preprocess(outline, item_id, memory_item);
}

CGlobalDecs::~CGlobalDecs() {
}


// process top node of variable scope
void CVarScope::callback1(class COutline* outline, uint64_t item, void* param) {
	// process all variables declared inside this node
	outline->find_children_of_type_and_run(callback2, param, item, NULL, false);
}
// process single variable node
void CVarScope::callback2(class COutline* outline, uint64_t item, void* param) {
	struct Params* params = (struct Params*) param;
	addvar(outline, *params->memory_item, *params->var_scope, item);
}


CVarScope::CVarScope(const char* str, const struct MatchItemsToScope* scope) : CItem(str), scope(scope) {
}

void CVarScope::first_pass(class COutline* outline, uint64_t item_id, uint64_t* memory_item) {
	CItem::first_pass(outline, item_id, memory_item);
	for (size_t i=0; scope[i].sc != varscope::NONE; i++) {
		uint16_t type[] = {
				scope[i].item_type,
				0
		};
		struct CVarScope::Params p = {type, &scope[i].sc, &item_id};
		outline->find_children_of_type_and_run(callback1, &p, item_id, type);
	}
}

void CVarScope::preprocess(class COutline* outline, uint64_t item_id, uint64_t* memory_item) {
	for (size_t i=0; scope[i].sc != varscope::NONE; i++) {
		memory_item[scope[i].sc] = item_id;
	}
	CItem::preprocess(outline, item_id, memory_item);
}

void CVarScope::postprocess(class COutline* outline, uint64_t item_id, uint64_t* memory_item) {
	/*
	for (size_t i=0; scope[i].sc != varscope::NONE; i++) {
	}
	*/
}

CVarScope::~CVarScope() {
}


const struct MatchItemsToScope CCLASS_TYPES[2] = {{varscope::CURRENT_OBJECT, Item::Type::INSTANCE_VARIABLES},{varscope::NONE,0}};
void CClass::callback3(class COutline* outline, uint64_t item, void* param) {
		// process all variables declared inside this node
		outline->find_children_of_type_and_run(callback4, param, item, NULL, false);
	}
	// process single variable node
void CClass::callback4(class COutline* outline, uint64_t item, void* param) {
	// resolve item address, add them to scope (call CClass), find out offset...

	// get variable name and memory offset
	uint64_t classdef_pointer = 0;
	uint32_t var_offset = 0;
	struct ItemBody* item_body = get_itembody(outline, item, 0x33);
	if (item_body) {
		var_offset = *((uint32_t*)((uint8_t*)item_body+1));
	}
	item_body = get_itembody(outline, item, 0x13);
	if (item_body) {
		memcpy(&classdef_pointer, (uint8_t*)item_body+1, item_bodies[0x13].size);
	}

	if (!classdef_pointer) {
		return;
	}
	outline->add_variable(*(uint64_t*)param, varscope::CURRENT_OBJECT, var_offset, classdef_pointer);
}


CClass::CClass(const char* str) : CVarScope(str, CCLASS_TYPES), target_control_type(0) {
	// Pre-compute the matching control-instance type for this class
	// registration so first_pass can register it for synthetic
	// `Class: <name>` emission. e.g. "Data Field Class:" → 0x04 (the
	// tag_items index of "Data Field:"). The lookup runs once per
	// registration (constructor time) — TAG_ITEMS_AMOUNT scans is fine.
	if (!str) return;
	const char* suffix = " Class:";
	size_t name_len = strlen(str);
	size_t suffix_len = strlen(suffix);
	if (name_len <= suffix_len || strcmp(str + name_len - suffix_len, suffix) != 0) {
		return;
	}
	// Build control name = name without " Class" but keeping ":".
	// "Data Field Class:" → "Data Field:".
	char target_name[128];
	if (name_len - suffix_len + 1 >= sizeof(target_name)) return;
	memcpy(target_name, str, name_len - suffix_len);
	target_name[name_len - suffix_len] = ':';
	target_name[name_len - suffix_len + 1] = '\0';
	for (uint16_t i = 0; i < TAG_ITEMS_AMOUNT; i++) {
		if (!tag_items[i]) continue;
		const char* candidate = tag_items[i]->get_name();
		if (candidate && strcmp(candidate, target_name) == 0) {
			target_control_type = i;
			break;
		}
	}
}

void CClass::first_pass(class COutline* outline, uint64_t item_id, uint64_t* memory_item) {
	uint16_t type[] = {
			Item::Type::DERIVED_FROM,
			Item::Type::DERIVED_FROM_INTERFACE,
			0
	};
	outline->find_children_of_type_and_run(callback3, &item_id, item_id, type);
	CVarScope::first_pass(outline, item_id, memory_item);
	// Register this class definition as the binding for control instances
	// of the matching type. If multiple classes of the same type are
	// declared, the first declared wins. Imported classes (bit 0x400) are
	// skipped — main-app classes shadow library-provided ones.
	if (target_control_type) {
		tagITEM* p_item = outline->get_item(item_id);
		if (p_item && !(p_item->flags & 0x400)) {
			outline->register_class_for_control_type(target_control_type, item_id);
		}
	}
}

void CClass::preprocess(class COutline* outline, uint64_t item_id, uint64_t* memory_item) {
	CVarScope::preprocess(outline, item_id, memory_item);
}

CClass::~CClass() {
}

CObject::CObject (const char* str) : CClass(str) {
}

uint64_t CObject::get_class(class COutline* outline, uint64_t item_id) {
	struct ItemBody* ib = get_itembody(outline, item_id, 0x14);
	if (!ib) {
		return 0;
	}
	if (ib->size <= 0x02) {
		return 0;
	}
	uint16_t type = *((uint16_t*)ib->data); // should match item->type value!!
	uint32_t offset = 0;
	switch (type) { // adapt to 64bit apps!
	case 0x01: // Form Window
		offset = 0x04; // may depend on version of Team Developer
		break;
	case 0x06: // Pushbutton
		offset = 0x10; // may depend on version of Team Developer
		break;
	default:
		offset = 0x10; // not correct for all types
	}
	if (ib->size < offset + sizeof(uint32_t)) { // adapt to 64bit apps!
		return 0;
	}
	uint64_t class_type = 0;
#ifndef TDx64
	class_type = *((uint32_t*)&ib->data[offset]);
#else
	class_type = *((uint64_t*)&ib->data[offset]);
#endif
	tagITEM* class_item = outline->get_item(class_type);
	if (!class_item) {
		return 0;
	}
	if (class_item->type >= TAG_ITEMS_AMOUNT) {
		return 0;
	}
	try{
		CClass* scope_resolution = dynamic_cast<CClass*>(::tag_items[class_item->type]);
		if (!scope_resolution) {
			return 0;
		}
		return class_type;
	}catch(...) {
		return 0;
	}
}

void CObject::first_pass(class COutline* outline, uint64_t item_id, uint64_t* memory_item) {
	CItem::first_pass(outline,item_id,memory_item);
}

void CObject::preprocess(class COutline* outline, uint64_t item_id, uint64_t* memory_item) {
	uint64_t it_class = get_class(outline, item_id);
	if (!it_class) {
		return;
	}
	memory_item[varscope::CURRENT_OBJECT] = it_class;
}

void CObject::print(class COutline* outline, uint64_t item_id, uint64_t* memory_item) {
	// Always emit the generic control/object type label (this->name), never
	// substitute the user-defined subclass name. Matches TD GUI convention:
	// `Form Window: frm1`, not `frmCls: frm1`. The subclass relationship is
	// recoverable from the item's class metadata elsewhere in the output.
	CClass::print(outline, item_id, memory_item);
}

void CObject::print_extra_lines(class COutline* outline, uint64_t item_id, uint32_t indention) {
	// Emit synthetic `Class: <name>` for control instances of types that
	// have a registered class definition in the outline. Gives cbi -b the
	// class binding it needs to resolve `obj.member` external references.
	// Skip in binary output mode (the .app reconstruction doesn't need a
	// synthetic child) and skip imported items (the library carries the
	// binding via 0x400 flag).
	if (!is_binary_app_output()) {
		tagITEM* p_item = outline->get_item(item_id);
		if (p_item && !(p_item->flags & 0x400)) {
			uint64_t class_def = outline->get_default_class_for_control_type(p_item->type);
			if (class_def) {
				const char16_t* class_name = outline->symbol_lookup(class_def);
				if (class_name) {
					print_indent(indention + 1);
					oputs("Class: ");
					print_utf16(class_name, strlen_utf16(class_name));
					oputs("\n");
				}
			}
		}
	}
	CItem::print_extra_lines(outline, item_id, indention);
}

CObject::~CObject() {
}

#ifndef TDx64
struct MatchItemsToScope SCOPE_FUNCTION[] = {
		{varscope::INTERNAL_FUNCTION_VAR,0x88}, // Local Variables
		{varscope::INTERNAL_FUNCTION_PARAM,0x89}, // Parameters [intern function]
		{varscope::INTERNAL_FUNCTION_PARAM,0x210}, // Parameters [dynalink?]
		{varscope::LIB_GLOBALS,0x119}, // Static Variables [Global]
		{varscope::NONE,0}
};
struct MatchItemsToScope SCOPE_CONSTRUCTOR[] = {
		{varscope::INTERNAL_FUNCTION_VAR,0x88}, // Local Variables
		{varscope::INTERNAL_FUNCTION_PARAM,0x2d4}, // Parameters
		//0x0e,0x119, // Static Variables [Global]
		{varscope::NONE,0}
};
#endif

std::stack<uint64_t> CDlg::cur_dlg_item = std::stack<uint64_t>();

CDlg::CDlg(const char* str) : CObject(str) {
}

void CDlg::callback0(class COutline* outline, uint64_t item, void* param) {
	struct Params* params = (struct Params*) param;
	outline->find_children_of_type_and_run(callback1, param, item, params->type);
}

void CDlg::first_pass(class COutline* outline, uint64_t item_id, uint64_t* memory_item) {
	CObject::first_pass(outline, item_id, memory_item);
	// Derived From: register the parent class's pointer into this item's
	// CURRENT_OBJECT scope so the cascade walks into the parent's Instance
	// Variables. CClass::first_pass does this for plain class tags, but CDlg
	// (used for `Dialog Box Class:` / `Form Window Class:` templates)
	// overrides first_pass and used to skip the Derived From walk — that left
	// inherited Instance Variables unreachable via sc07 (e.g. wizwiz's
	// cWizardFrame inheriting `Items[*]` from cFormPageList).
	{
		uint16_t type[] = {
				Item::Type::DERIVED_FROM,
				Item::Type::DERIVED_FROM_INTERFACE,
				0};
		outline->find_children_of_type_and_run(CClass::callback3, &item_id, item_id, type);
	}
	const struct MatchItemsToScope scope[] = {
			{varscope::CURRENT_FORM, 0x0076},
			{varscope::CURRENT_FORM, 0x0191},
			{varscope::CURRENT_FORM, 0x0072},
			// `Background Threads:` (BACKGROUND_THREADS = 0x2e4) is a
			// form-level container introduced in TD 7.1 holding
			// `BackgroundWorkerVar:` instances (typed handles for
			// SalBackgroundWorker* APIs). They live in the form's
			// CURRENT_FORM variable storage — without this walk, calls
			// like `Call SalBackgroundWorkerStart(<var>)` decompile as
			// `SalBackgroundWorkerStart(sc04_var0000)`.
			{varscope::CURRENT_FORM, Item::Type::BACKGROUND_THREADS},
			// CDlg is used for both form-instance and class-template items
			// (Form Window Class / Dialog Box Class). Templates may carry
			// Instance Variables (type 0x109) that must register as
			// CURRENT_OBJECT so derived instances can resolve them via the
			// offset-0 class-pointer cascade. Harmless for plain instances —
			// they just don't have INSTANCE_VARIABLES children.
			{varscope::CURRENT_OBJECT, Item::Type::INSTANCE_VARIABLES},
			{varscope::NONE, 0x00}};
	CVarScope vc(NULL, scope);
	vc.first_pass(outline, item_id, memory_item);

	// Tool Bar
	uint16_t type1[] = {0x10e, 0x00};
	uint16_t type2[] = {0x072, 0x00};
	varscope sc = varscope::CURRENT_FORM;
	struct CVarScope::Params p = {type2, &sc, &item_id};
	outline->find_children_of_type_and_run(callback0, &p, item_id, type1);

	uint64_t object_class = CObject::get_class(outline, item_id);
	if (object_class && outline->has_any_variable(object_class, varscope::CURRENT_OBJECT)) {
		outline->add_variable(item_id, varscope::CURRENT_FORM, 0, object_class);
	}

	cur_dlg_item.push(item_id);
}

void CDlg::preprocess(class COutline* outline, uint64_t item_id, uint64_t* memory_item) {
	CObject::preprocess(outline, item_id, memory_item);
	memory_item[varscope::CURRENT_FORM] = item_id;
	// CDlg is also the tag for `Form Window Class:` / `Dialog Box Class:`
	// templates. Their Instance Variables (0x109) are registered on the
	// template itself at CURRENT_OBJECT scope (by CDlg::first_pass, Zb), so
	// a method body inside the template needs CURRENT_OBJECT pointed at the
	// template to resolve `sc07_var...` references against those vars.
	// Detect the template case by checking if the item has any
	// CURRENT_OBJECT-scope memory registered — only templates do, plain
	// instances don't.
	if (outline->has_any_variable(item_id, varscope::CURRENT_OBJECT)) {
		memory_item[varscope::CURRENT_OBJECT] = item_id;
		// CURRENT_FORM_CLASS (0x09) — bytecode references Instance Variables
		// of a `Form Window Class:` / `Dialog Box Class:` template via this
		// scope when the access compiles from a control's message-action body
		// nested inside the class (rather than a method body of the class
		// itself). The vars are already registered at CURRENT_OBJECT scope;
		// pointing memory_item[0x09] at the same template lets lookup walk
		// the same map (with a CURRENT_OBJECT fallback in print_var_name).
		memory_item[varscope::CURRENT_FORM_CLASS] = item_id;
	}
	cur_dlg_item.push(item_id);
}

void CDlg::postprocess(class COutline* outline, uint64_t item_id, uint64_t* memory_item) {
	if (cur_dlg_item.top() != item_id || cur_dlg_item.empty()) {
		throw std::exception();
	}
	cur_dlg_item.pop();
	CObject::postprocess(outline, item_id, memory_item);
}

CDlg::~CDlg() {
}

CDlgParent::CDlgParent(const char* str) : CObject(str) {
}

void CDlgParent::first_pass(class COutline* outline, uint64_t item_id, uint64_t* memory_item) {
	CObject::first_pass(outline, item_id, memory_item);
	// Register instance vars declared inside this container's "Window Variables"
	// (0x76) section at CURRENT_OBJECT scope of the container. Child Grid /
	// Child Table instances can carry their own local variables just like a
	// Form Window — without this, the vars never register and their bytecode
	// references mis-resolve to the container itself.
	const struct MatchItemsToScope scope[] = {
		{varscope::CURRENT_OBJECT, 0x0076},
		{varscope::CURRENT_OBJECT, 0x0191},
		{varscope::CURRENT_OBJECT, 0x0072},
		{varscope::NONE, 0x00}};
	CVarScope vc(NULL, scope);
	vc.first_pass(outline, item_id, memory_item);
	// A Child Table / Child Grid that derives its behaviour from a class
	// with Instance Variables accesses the inherited member via scope=0x07
	// (CURRENT_OBJECT). CDlgParent::preprocess sets memory_item[CURRENT_OBJECT]
	// = item_id (the instance), but the instance carries no CURRENT_OBJECT
	// entry, so the cascade to the parent class never starts and the access
	// leaks as `sc07_var00aa`.
	//
	// Mirror CDlg::first_pass for the CURRENT_OBJECT case: register the
	// class pointer at offset 0 of the instance's CURRENT_OBJECT scope so
	// lookup_variable(instance, CURRENT_OBJECT, off) walks back to off=0,
	// finds the class, then cascades through the class's own CURRENT_OBJECT
	// (DERIVED_FROM-registered class chain via callback4) into the parent
	// class where the variable lives.
	uint64_t object_class = CObject::get_class(outline, item_id);
	if (object_class && outline->has_any_variable(object_class, varscope::CURRENT_OBJECT)) {
		outline->add_variable(item_id, varscope::CURRENT_OBJECT, 0, object_class);
	}

	// High-offset Child-Table member access: Child Table / Child Grid
	// columns live in `CHILD_GRID_CONTENTS` (0xd3) and carry FORM-RELATIVE
	// VAROFFSETs. Bytecode like `Set <col>.<member> = <value>` compiles
	// to a single sc04 access at offset = column_form_offset +
	// member_offset_in_class. The existing CDlg-level Contents walk
	// (form's 0x072) doesn't recurse into Child Tables; CDlgParent's
	// CURRENT_OBJECT walk only includes 0x0072 (Tab Bar Contents) and
	// skips 0xd3, so columns never reach addvar.
	//
	// Walk CHILD_GRID_CONTENTS at the form's CURRENT_FORM scope (the form
	// id is `cur_dlg_item.top()` here — CDlgParent has not yet pushed
	// itself onto the stack). addvar's class-object branch then registers
	// each column at form.CURRENT_FORM[VAROFFSET] and column.CURRENT_FORM[0]
	// = its class, so the 4-way cascade in lookup_variable resolves a
	// member access through the column's class CURRENT_OBJECT scope.
	if (!CDlg::cur_dlg_item.empty()) {
		static const varscope kCurrentForm = varscope::CURRENT_FORM;
		static const uint16_t kContentsTypes[] = { Item::Type::CHILD_GRID_CONTENTS, 0 };
		uint64_t form_id = CDlg::cur_dlg_item.top();
		struct CVarScope::Params p = {kContentsTypes, &kCurrentForm, &form_id};
		outline->find_children_of_type_and_run(CVarScope::callback1, &p, item_id, kContentsTypes);
	}

	CDlg::cur_dlg_item.push(item_id);
}

void CDlgParent::preprocess(class COutline* outline, uint64_t item_id, uint64_t* memory_item) {
	CObject::preprocess(outline, item_id, memory_item);
	memory_item[varscope::CURRENT_OBJECT] = item_id;
	CDlg::cur_dlg_item.push(item_id);
}

void CDlgParent::postprocess(class COutline* outline, uint64_t item_id, uint64_t* memory_item) {
	if (!CDlg::cur_dlg_item.empty() && CDlg::cur_dlg_item.top() == item_id) {
		CDlg::cur_dlg_item.pop();
	}
}

CDlgParent::~CDlgParent() {
}


CItem* tag_items[TAG_ITEMS_AMOUNT] = {
		new CItem(NULL),
		new CDlg("Form Window:"),
		new CDlg("Table Window:"),
		new CDlgParent("Child Table:"),
		new CObject("Data Field:"),
		new CObject("Multiline Field:"),
		new CObject("Pushbutton:"),
		new CObject("Radio Button:"),
		new CObject("Check Box:"),
		new CObject("Group Box:"),
		new CObject("Horizontal Scroll Bar:"),
		new CObject("Vertical Scroll Bar:"),
		new CObject("Background Text:"),
		new CItem("Column:"),
		new CObject("List Box:"),
		new CObject("Combo Box:"),
		new CObject("Frame:"),
		new CObject("Line:"),
		new CObject("Picture:"),
		new CDlg("MDI Window:"),
		new CObject("Option Button:"),
		new CObject("Spin Field:"),
		new CObject("Custom Control:"),
		new CItem(NULL),
		new CItem(NULL),
		new CItem(NULL),
		new CItem("Absolute Screen Location?"),
		new CItem("Always Show List?"),
		new CItem("Application Actions"),
		new CItem("Application Description:"),//,SCOPE_GLOBAL_VARS),
		new CItem("Automatically Created at Runtime?"),
		new CItem("Begin X: "),
		new CItem("Begin Y: "),
		new CItem("Background Color:"),
		new CItem("Background Color:"),
		new CItem("Background Color:"),
		new CItem("Background Text"),
		new CBoolean(),
		new CItem("Border?"),
		new CItem("Border Color:"),
		new CItem("Border Color:"),
		new CItem("Border Style:"),
		new CItem("Border Thickness:"),
		new CBreak("Break"),
		new CItem("Check Box"),
		new CStatement("Checked when:", datatype::_BOOLEAN),
		new CItem("Display Settings"),
		new CItem("Child Table Window"),
		new CItem("Visible?"),
		new CItem("Title:"),
		new CItem("Width: "),
		new CItem("Combo Box"),
		new CItem("Constants"),
		new CItem("Coordinates"),
		new CItem("Corners:"),
		new CItem("Country:"),
		new CItem("Maximum Data Length:"),
		new CItem("Data Type:"),
		new CDateTime(),
		new CItem("Database:"),
		new CItem("Password:"),
		new CItem("User:"),
		new CItem("Database Include:"),
		new CItem("Description:"),
		new CItem("Design-time Settings"),
		new CItem("Visible at Design time?"),
		new CDlg("Dialog Box:"),
		new CItem("Dialog Box"),
		new CItem("Type of Dialog:"),
		new CItem("Display Settings"),
		new CItem("Actions"),
		new CItem("Editable?"),
		new CStatement("Else If"),
		new CItem("Else"),
		new CStatement("Enabled when:", datatype::_BOOLEAN),
		new CItem("End X: "),
		new CItem("End Y: "),
		new CNumericItem("Export Ordinal:", 0x22),
		new CVar("Boolean:"),
		new CVar("Date/Time:"),
		new CVar("File Handle:"),
		new CItem("External Functions"),
		new CVarScope("Function:",SCOPE_FUNCTION), // external function
		new CVar("Long String:"),
		new CItem("Nothing"),
		new CVar("Number:"),
		new CItem("Parameters"),
		new CItem("Returns"),
		new CItem("Receive Boolean:"),
		new CItem("Receive Date/Time:"),
		new CItem("Receive File Handle:"),
		new CItem("Receive Long String:"),
		new CItem("Receive Number:"),
		new CItem("Receive Sql Handle:"),
		new CItem("Receive String:"),
		new CItem("Receive Window Handle:"),
		new CVar("Sql Handle:"),
		new CVar("String:"),
		new CItem("Template:"),
		new CVar("Window Handle:"),
		new CItem("Data"),
		new CItem("Data Field"),
		new CItem("Display Settings"),
		new CVar("File Handle:"),
		new CItem("Font Enhancement:"),
		new CItem("Font Enhancement:"),
		new CItem("Font Enhancement:"),
		new CItem("Font Name:"),
		new CItem("Font Name:"),
		new CItem("Font Name:"),
		new CItem("Font Size:"),
		new CItem("Font Size:"),
		new CItem("Font Size:"),
		new CItem("Format:"),
		new CItem("Contents"),
		new CItem("Height:"),
		new CItem("Number of Pages:"),
		new CItem("Form Size"),
		new CItem("Window Variables"),
		new CItem("Width: "),
		new CItem("Form Window"),
		new CItem("Display Settings"),
		new CItem("Frame"),
		new CStatement("Call"),
		new CGlobalDecs("Global Declarations"),
		new CItem("Group Box"),
		new CItem("Group Separator"),
		new CItem("Helps"),
		new CItem("Icon File:"),
		new CStatement("If", datatype::_BOOLEAN),
		new CItem("Libraries"),
		new CItem("File Include:"),
		new CItem("Initial State:"),
		new CItem(NULL),
		new CItem("Internal Functions"),
		new CVarScope("Function:",SCOPE_FUNCTION),
		new CItem("Local variables"),
		new CItem("Parameters"),
		new CItem("Returns"),
		new CCase(),
		new CItem("Default"),
		new CStatement("Select Case", datatype::NUMBER),
		new CItem("Justify:"),
		new CItem("Keyboard Accelerator:"),
		new CItem("Keyboard Accelerator:"),
		new CItem("Library name:"),
		new CItem("Line Color:"),
		new CItem("Line Color:"),
		new CItem("Line"),
		new CItem("Line Thickness:"),
		new CItem("List Box"),
		new CItem("List Initialization"),
		new CItem("Text:"),
		new CItem("Long help message:"),
		new CVar("Long String:"),
		new CLoop(),
		new CItem("Maximizable?"),
		new CItem("Contents"),
		new CItem("Display Settings"),
		new CItem("Menu"),
		new CItem("Menu Actions"),
		new CItem("Menu Column"),
		new CItem("Menu Item:"),
		new CItem("Menu Settings"),
		new CItem("Menu Row"),
		new CItem("Menu Separator"),
		new CItem("Minimizable?"),
		new CItem("Modal Dialog?"),
		new CItem("Data"),
		new CItem("Display Settings"),
		new CItem("Multiline Field"),
		new CItem("Multiple selection?"),
		new CNumber(),
		new CItem("Message Actions"),
		new COn(),
		new CItem("When SqlError"),
		new CItem("Options Box Location"),
		new CItem("Outline Window Location and Size"),
		new CItem("Outline Window State:"),
		new CItem("Picture"),
		new CItem("File Name:"),
		new CItem("Fit:"),
		new CItem("Scaling"),
		new CItem("Storage:"),
		new CItem("Popup Menu:"),
		new CItem("Pushbutton"),
		new CItem("Fully Qualified External References?"),
		new CItem("Radio Button"),
		new CItem("!"),
		new CItem("Resizable?"),
		// Return's default datatype is _BOOLEAN so that a bare `Return 0` /
		// `Return 1` in SAM_Validate and similar event handlers decompiles
		// to `Return FALSE` / `Return TRUE`. The _BOOLEAN branch in Const
		// falls back to a numeric print for non-0/1 values, so `Return 42`
		// in a Number-returning internal function still prints correctly.
		new CStatement("Return", datatype::_BOOLEAN),
		new CItem("Receive Boolean:"),
		new CItem("Receive Date/Time:"),
		new CItem("Receive File Handle:"),
		new CItem("Receive Long String:"),
		new CItem("Receive Number:"),
		new CItem("Receive Sql Handle:"),
		new CItem("Receive String:"),
		new CItem("Receive Window Handle:"),
		new CItem("Height: "),
		new CItem("Width: "),
		new CStatement("Set"),
		new CItem("Short help message:"),
		new CItem("Sorted?"),
		new CVar("Sql Handle:"),
		new CItem("String Type:"),
		new CString(),
		new CItem("Structure:"),
		new CItem("System"),
		new CItem("System Menu?"),
		new CItem("System Modal?"),
		new CItem("Contents"),
		new CItem("Discardable?"),
		new CItem("Memory Settings"),
		new CItem("Maximum Rows in Memory:"),
		new CItem("Display Settings"),
		new CItem("Text Color:"),
		new CItem("Text Color:"),
		new CItem("Text Color:"),
		new CItem("Tile To Parent?"),
		new CItem("Tool Palette Location"),
		new CItem("Top Level Table Window"),
		new CItem("User"),
		new CItem("Variables"),
		new COutlineVersion(),
		new CItem("Vertical Scroll?"),
		new CItem("Visible?"),
		new CStatement("While"),
		new CItem("Window Defaults"),
		new CItem("Height:"),
		new CItem("Left:"),
		new CItem("Window Location and Size"),
		new CItem("Title:"),
		new CItem("Top:"),
		new CItem("Window Handle:"),
		new CItem("Width: "),
		new CItem("Word Wrap?"),
		new CItem("Workspace Size"),
		new CItem("Formats"),
		new CVar("Number:"),
		new CVar("Date/Time:"),
		new CItem("Picture Transparent Color:"),
		new CItem("Picture File Name:"),
		new CItem("Derived From"),
		new CClassDefinitions("Class Definitions"),
		new CClass("Functional Class:"),
		new CDlg("Dialog Box Class:"),
		new CDlg("Form Window Class:"),
		new CClass("Table Window Class:"),
		new CClass("Child Table Class:"),
		new CClass("Data Field Class:"),
		new CClass("Multiline Field Class:"),
		new CClass("Pushbutton Class:"),
		new CClass("Radio Button Class:"),
		new CClass("Check Box Class:"),
		new CClass("Horizontal Scroll Bar Class:"),
		new CClass("Vertical Scroll Bar Class:"),
		new CClass("Column Class:"),
		new CClass("List Box Class:"),
		new CClass("Combo Box Class:"),
		new CClass("Picture Class:"),
		new CFunctionalVar(),
		new CItem("Class:"),
		new CItem("Reject Multiple Window Instances?"),
		new CItem("Enable Runtime Checks Of External References?"),
		new CItem("Instance Variables"),
		new CItem("Editable?"),
		new CItem("Object Menu"),
		new CItem("Resource Id:"),
		new CItem("Size:"),
		new CItem("Tool Bar"),
		new CItem("Windows Menu:"),
		new CItem("Tool Bar"),
		new CObject("Quest Child Window:"),
		new CObject("Quest Table Window:"),
		new CItem("Auto Execute?"),
		new CItem("Object Links"),
		new CItem("Outline Version -"),
		new CItem("Functions"),
		new CItem("Functions"),
		new CItem("Class Variables"),
		new CItem("Static Variables"),
		new CClass("Custom Control Class:"),
		new CClass("Spin Field Class:"),
		new CClass("Option Button Class:"),
		new CItem("DLL Name:"),
		new CItem("MS Windows Class Name:"),
		new CItem("Class:"),
		new CClass("MDI Window Class:"),
		new CClass("Quest Child Window Class:"),
		new CClass("Quest Table Window Class:"),
		new CItem("Display Settings"),
		new CItem("Location?"),
		new CItem("Accessories Enabled?"),
		new CItem("Visible?"),
		new CItem("Visible?"),
		new CItem("Menu:"),
		new CItem("Title:"),
		new CItem("Named Menu:"),
		new CItem("Named Menus"),
		new CItem("Windows Menu:"),
		new CItem("Status Text:"),
		new CItem("Class Editor Location"),
		new CItem("Default Classes"),
		new CItem("Form Window:"),
		new CItem("Dialog Box:"),
		new CItem("Table Window:"),
		new CItem("Quest Window:"),
		new CItem("Data Field:"),
		new CItem("Multiline Field:"),
		new CItem("Pushbutton:"),
		new CItem("Radio Button:"),
		new CItem("Check Box:"),
		new CItem("Child Table:"),
		new CItem("Quest Child Window:"),
		new CItem("List Box:"),
		new CItem("Combo Box:"),
		new CItem("Picture:"),
		new CItem("Vertical Scroll Bar:"),
		new CItem("Horizontal Scroll Bar:"),
		new CItem("Column:"),
		new CItem("MDI Window:"),
		new CItem("Display Style?"),
		new CItem("Display Style?"),
		new CClass("Background Text Class:"),
		new CClass("Group Box Class:"),
		new CClass("Line Class:"),
		new CClass("Frame Class:"),
		new CItem("Background Text:"),
		new CItem("Group Box:"),
		new CItem("Line:"),
		new CItem("Frame:"),
		new CItem("Width Editable?"),
		new CItem("Height Editable?"),
		new CItem("Size Editable?"),
		new CItem("Width Editable?"),
		new CObject("Column:"),
		new CItem("Condition:"),
		new CItem("Input Mask:"),
		new CItem("Input:"),
		new CItem("Template Methods"),
		new CItem("Derived From:"),
		new CItem("Database Link:"),
		new CItem("SQL Attribute:"),
		new CItem("SQLWindows Attributes"),
		new CItem("Method:"),
		new CItem("User Variables"),
		new CItem("SQLWindows Variables"),
		new CItem("Output"),
		new CItem("Define:"),
		new CItem("Default"),
		new CItem("Menus"),
		new CItem("Data Type:"),
		new CItem("Input"),
		new CItem("Search:"),
		new CItem("Message Actions"),
		new CItem("TplIf"),
		new CItem("TplSet"),
		new CItem("TplDelete"),
		new CItem("TplLoopForeignTables"),
		new CItem("TplLoopPrimaryKey"),
		new CItem("TplLoopForeignKey"),
		new CItem("Menu Item:"),
		new CItem("Popup Menu:"),
		new CItem("Windows Menu:"),
		new CItem("Menu Actions"),
		new CItem("TplIf"),
		new CItem("TplSet"),
		new CItem("TplIf"),
		new CItem("TplSet"),
		new CItem("Spin Field:"),
		new CItem("Option Button:"),
		new CItem("Custom Control:"),
		new CItem("Spin Field"),
		new CItem("Option Button"),
		new CItem("Style: "),
		new CItem("ExStyle: "),
		new CItem("Display Settings"),
		new CItem("Tile To Parent?"),
		new CItem("Tab Stop?"),
		new CItem("Vertical Scroll?"),
		new CItem("Horizontal Scroll?"),
		new CItem("Border?"),
		new CItem("Etched Border?"),
		new CItem("Hollow?"),
		new CItem("Group Name:"),
		new CItem("Help Context Number:"),
		new CItem("Required Object?"),
		new CItem("Multiple Instances?"),
		new CItem("Button Style:"),
		new CItem("Image Style:"),
		new CItem("Template Settings"),
		new CItem("AutoSQL:"),
		new CItem("Supported Databases"),
		new CItem("Database Brand:"),
		new CItem("Help File Name:"),
		new CItem("Sample Picture:"),
		new CItem("Required Include Files"),
		new CItem("Version:"),
		new CItem("TplIf"),
		new CItem("Line Style:"),
		new CItem("Window Parameters"),
		new CItem(NULL),
		new CItem("Accessory Frame"),
		new CItem("Accessories Enabled?"),
		new CItem("View:"),
		new CItem("Resources"),
		new CItem("Bitmap:"),
		new CItem("Icon:"),
		new CItem("Cursor:"),
		new CItem("File Name:"),
		new CItem("Browse Bar?"),
		new CItem("Detail Table:"),
		new CItem("Select From:"),
		new CItem("Dialog Box:"),
		new CItem("Form Window:"),
		new CItem("Table Window:"),
		new CItem("MDI Window:"),
		new CItem("External Functions"),
		new CItem("Constants"),
		new CItem("Resources"),
		new CItem("Variables"),
		new CItem("Internal Function:"),
		new CItem("Class Definitions"),
		new CItem("Included Objects"),
		new CItem("File Include:"),
		new CItem("Value Required?"),
		new CItem("Formats"),
		new CItem("Named Menus"),
		new CItem("Next Class Child Key:"),
		new CItem("Class Child Ref Key:"),
		new CItem("Class ChildKey:"),
		new CItem("UDV Structs"),
		new CItem("UDV Struct:"),
		new CItem("Class:"),
		new CItem("Variables"),
		new CItem(":"),
		new CItem(":"),
		new CItem("UDVMap:"),
		new CItem("Use Release 4.0 Scope Rules?"),
		new CItem("Database Relationship Model:"),
		new CItem("struct"),
		new CItem("structPointer"),
		new CItem("DLL Settings"),
		new CItem("Menu Item Name:"),
		new CItem("Receive Boolean:"),
		new CItem("Receive Date/Time:"),
		new CItem("Receive File Handle:"),
		new CItem("Receive Number:"),
		new CItem("Receive Sql Handle:"),
		new CItem("Receive Window Handle:"),
		new CVar("String:"),
		new CItem("Receive String:"),
		new CItem("struct"),
		new CItem("List in Tool Palette?"),
		new CItem("Class DLL Name:"),
		new CClass("General Window Class:"),
		new CItem("Dynalib:"),
		new CItem("Cell Options"),
		new CItem("Cell Type?"),
		new CItem("Multiline Cell?"),
		new CItem("Cell DropDownList"),
		new CItem("Auto Drop Down?"),
		new CItem("Allow Text Editing?"),
		new CItem("Cell CheckBox"),
		new CItem("Check Value:"),
		new CItem("Uncheck Value:"),
		new CItem("List Values"),
		new CItem("Text:"),
		new CItem("Allow Row Sizing?"),
		new CItem("Lines Per Row:"),
		new CItem("Property Template:"),
		new CItem("Sorted?"),
		new CItem("Vertical Scroll?"),
		new CItem("Ignore Case?"),
		new CItem("Functional Class Object:"),
		new CItem("Dynalink Form Window:"),
		new CItem("Dynalink Table Window:"),
		new CItem("Dynalink MDI Window:"),
		new CItem("Functions"),
		new CItem("Dynalink Function:"),
		new CVarScope("Function:",SCOPE_FUNCTION),
		new CItem("Dynalink Dialog Box:"),
		new CItem("Dynalink Quest Table Window:"),
		new CItem("Contents"),
		new CItem("Dynalink Boolean:"),
		new CItem("Dynalink Date/Time:"),
		new CItem("Dynalink File Handle:"),
		new CItem("Dynalink Long String:"),
		new CItem("Dynalink Number:"),
		new CItem("Dynalink Sql Handle:"),
		new CItem("Dynalink String:"),
		new CItem("Dynalink Window Handle:"),
		new CObject("ActiveX:"),
		new CClass("ActiveX Class:"),
		new CItem("ActiveX:"),
		new CItem("GUID:"),
		new CItem("License Key:"),
		new CItem("Host Name:"),
		new CItem("Activation:"),
		new CItem("Display Settings"),
		new CItem("Type:"),
		new COn(),
		new CClass("COM Proxy Class:"),
		new CItem("ComProxyVar:"),
		new CClass("CoClass:"),
		new CItem("CoClassVar:"),
		new CItem("Attributes"),
		new CItem("Help String:"),
		new CItem("Help Context:"),
		new CItem("Creatable:"),
		new CItem("Licensed:"),
		new CItem("Events"),
		new CItem("Event:"),
		new CClass("Interface:"),
		new CItem("InterfaceVar:"),
		new CItem("Attributes"),
		new CItem("Functions"),
		new CVarScope("Function:",SCOPE_FUNCTION),
		new CItem("Attributes"),
		new CItem("Dispatch Number:"),
		new CItem("Session Handle:"),
		new CItem("Receive Session Handle:"),
		new CItem("Session Handle:"),
		new CItem("Receive Session Handle:"),
		new CItem("Enumerations"),
		new CItem("Enum:"),
		new CItem("Item:"),
		new CItem("Parameters"),
		new CItem("Returns"),
		new CItem("Use:"),
		new CItem("ThreadSafe:"),
		new CItem("Derived From"),
		new CItem("Interface:"),
		new CItem("Allow Child Docking?"),
		new CItem("Allow Dock to Parent?"),
		new CItem("Docking Toolbar?"),
		new CItem("Toolbar Docking Orientation:"),
		new CItem("Docking Orientation:"),
		new CItem("Button Appearance:"),
		new CItem("Resizable?"),
		new CItem("Horizontal Scroll?"),
		new CItem("When SessionError"),
		new CItem("Edit Fields Read Only On Disable?"),
		new CItem("XML NumberType:"),
		new CItem("XML DateTimeType:"),
		new CItem("XML DataType:"),
		new CItem("XML Serialize:"),
		new CItem("XML Nulls Allowed:"),
		new CObject("Date Picker:"),
		new CClass("Date Picker Class:"),
		new CItem("Date Picker:"),
		new CItem("Display Settings"),
		new CItem("Show Non Month Days?"),
		new CItem("Show Today?"),
		new CItem("Show None?"),
		new CObject("Date Time Picker:"),
		new CClass("Date Time Picker Class:"),
		new CItem("Date Time Picker:"),
		new CItem("Display Settings"),
		new CItem("Time Format:"),
		new CItem("Mode:"),
		new CItem("Read Only?"),
		new CItem("Disabled?"),
		new CItem("Date Time Picker"),
		new CDlgParent("Child Grid:"),
		new CClass("Child Grid Class:"),
		new CItem("Child Grid:"),
		new CItem("Display Settings"),
		new CItem("Child Grid Window"),
		new CObject("Tab Bar:"),
		new CClass("Tab Bar Class:"),
		new CItem("Tab Bar:"),
		new CItem("Display Settings"),
		new CItem("Tab Bar"),
		new CItem("Contents"),
		new CItem("Tab:"),
		new CItem("Tab Child:"),
		new CItem("Orientation?"),
		new CItem("Style?"),
		new CItem("Enable Scroll?"),
		new CObject("Rich Text Control:"),
		new CClass("Rich Text Control Class:"),
		new CItem("Rich Text Control:"),
		new CItem("Data"),
		new CItem("Display Settings"),
		new CItem("Rich Text Control"),
		new CItem("RTC Toolbar Visible?"),
		new CItem("Rulerbar Visible?"),
		new CItem("HSCrollbar Enable?"),
		new CItem("VScrollBar Enable?"),
		new CItem("Left Margin: "),
		new CItem("Right Margin: "),
		new CItem("Top Margin: "),
		new CItem("Bottom Margin: "),
		new CItem("Binary:"),
		new CItem("Receive Binary:"),
		new CItem("Dynalink Binary:"),
		new CItem("Binary:"),
		new CItem("Receive Binary:"),
		new CItem("ToolTip:"),
		new CItem("Image Alignment:"),
		new CItem("Text Alignment:"),
		new CItem("Text Image Relation:"),
		new CDlg("Grid Window:"),
		new CClass("Grid Window Class:"),
		new CItem("Display Settings"),
		new CItem("Grid Window:"),
		new CItem("Top Level Grid Window"),
		new CItem("Grid Window:"),
		new CItem("Date Picker"),
		new CItem("AutoFill?"),
		new CItem("GroupBox Style:"),
		new CItem("GroupBox Style:"),
		new CItem("Display Style?"),
		new CItem("Display Style?"),
		new CObject("Separator:"),
		new CClass("Separator Class:"),
		new CItem("Separator:"),
		new CObject("Tree Control:"),
		new CClass("Tree Control Class:"),
		new CItem("Tree Control"),
		new CItem("Tree Control:"),
		new CItem("TreeItem:"),
		new CItem("Normal Image:"),
		new CItem("Selected Image:"),
		new CItem("Show Root?"),
		new CItem("Has Checkbox?"),
		new CItem("Track Select?"),
		new CObject("Navigation Bar:"),
		new CItem("Contents"),
		new CItem("Pane:"),
		new CItem("Pane Child:"),
		new CClass("Navigation Bar Class:"),
		new CItem("Navigation Bar:"),
		new CItem("Display Settings"),
		new CItem("Navigation Bar"),
		new CItem("Splitter Visible?"),
		new CItem("Splitter Enable?"),
		new CItem("Object Title:"),
		new CItem("Expanded Picture File Name:"),
		new CItem("Collapsed Picture File Name:"),
		new CObject("Pane Separator:"),
		new CClass("Group Separator Class:"),
		new CItem("Pane Separator"),
		new CItem("Pane Separator:"),
		new CItem("Expand?"),
		new CItem("Child Window:"),
		new CItem("Auto Hide Scroll?"),
		new CItem("Invert Vertical Font?"),
		new CItem("Pane Separator Top:"),
		new CItem("Expanded?"),
		new CItem("Xaml:"),
		new CItem("Assembly Symbol File:"),
		new CItem("External Assemblies"),
		new CItem("Symbol Import:"),
		new CClass("Web Service Class:"),
		new CItem("Operations"),
		new CItem("Operation:"),
		new CItem("WPF Custom:"),
		new CClass("WPFCustom Class:"),
		new CItem("WPF Custom:"),
		new CItem("WPF Custom"),
		new CItem("Symbol File Include:"),
		new CClass("Net Import Class:"),
		new CItem("Net Class Var:"),
		new CItem("Named Toolbars"),
		new CItem("Toolbar:"),
		new CItem("Toolbar Button:"),
		new CItem("Actions"),
		new CItem("Show Week Number:"),
		new CItem("Multi Row:"),
		new CItem("Resource Dictionary:"),
		new CItem("XAML Style:"),
		new CItem("Summary Bar Enabled?"),
		new CItem("Column Aggregate Type:"),
		new CItem("Brush:"),
		new CItem("XAML:"),
		new CItem("Background Brush:"),
		new CItem("Text Brush:"),
		new CItem("Flow Direction:"),
		new CItem("Flow Direction:"),
		new CItem("When Exception"),
		new CItem("End Exception"),
		new CItem("Rethrow"),
		new CItem("Hide Column Headers?"),
		new CItem("Smooth?"),
		new CItem("Vertical?"),
		new CItem("Progress From Color:"),
		new CItem("Progress To Color:"),
		new CItem("Step Size:"),
		new CItem("Range Minimum:"),
		new CItem("Range Maximum:"),
		new CItem("Progress Brush:"),
		new CItem("Progress Bar"),
		new CItem("Progress Bar:"),
		new CItem("Progress Bar Settings"),
		new CObject("Progress Bar:"),
		new CClass("Progress Bar Class:"),
		new CItem("Themed Background?"),
		new CItem("Ribbon"),
		new CItem("Tab:"),
		new CItem("Display Size:"),
		new CItem("Ribbon Actions"),
		new CItem("Button:"),
		new CItem("Group:"),
		new CItem("Dropdown:"),
		new CItem("Ribbon Separator"),
		new CItem("Ribbon Bar Enabled?"),
		new CItem("Tray:"),
		new CItem("Check Button:"),
		new CItem("Radio Button:"),
		new CItem("Combo:"),
		new CItem("DataField:"),
		new CItem("Width: "),
		new CItem("Spell Check?"),
		new CItem("Throw"),
		new CItem("Named Exceptions"),
		new CItem("Exception:"),
		new CItem("Exception Variables"),
		new CItem("Keyboard Accelerator:"),
		new CItem("Constructor/Destructor"),
		new CVarScope("Constructor:",SCOPE_CONSTRUCTOR),
		new CItem("Destructor:"),
		new CItem("Parameters"),
		new CItem("GalleryColumns:"),
		new CItem("Gallery:"),
		new CItem("Dropdown Gallery:"),
		new CItem("Gallery Item:"),
		new CItem("Hint Text:"),
		new CItem("Word Wrap?"),
		new CItem("Show Close Buttons:"),
		new CItem("Paint As Background:"),
		new CItem("Persist Child Menus?"),
		new CItem("Allow Text Filter:"),
		new CItem("Event Parameters"),
		new CVarScope("Thread Start", CTHREADEVENT),
		new CVarScope("Thread Before Start", CTHREADEVENT),
		new CVarScope("Thread Report Progress", CTHREADEVENT),
		new CVarScope("Thread Finished", CTHREADEVENT),
		new CItem("Background Threads:"),
		new CItem("Thread Events"),
		new CClass("Background Worker Class:"),
		new CItem("BackgroundWorkerVar:"),
		// LIST body 0x05; non-zero = Yes, zero = No. The runtime always
		// emits the value — missing it makes cbi -b default to Protected
		// and breaks external `obj.member` references.
		new CYesNoItem("Protected Variable:", 0x05),
		new CYesNoItem("Protected Function:", 0x05),
		new CItem("Show Percent:"),
		new CItem("IME Mode:"),
		new CItem("Dynalink Grid Window:"),
		new CVarScope("Thread Report Error", CTHREADEVENT),
		new CItem("Always Show Drop Button?"),
		new CItem("MDI Tabs:"),
		new CItem("Anchoring Enabled?"),
		new CItem("Vertical Anchor:"),
		new CItem("Horizontal Anchor:"),
		new CItem("Minimum Height:"),
		new CItem("Minimum Width:"),
		new CBreak("Continue"),
		new CItem("ForEach"),
		new CItem("Anchor Maximum Width:"),
		new CItem("Anchor Maximum Height:")
};
