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

#ifdef __unix__ 
#include <iconv.h>
#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
#include <windows.h>
#else
#error "neither Unix nor Windows environment defined"
#endif
#include "item.hpp"
#include "outline_decs.hpp"
#include "COutline.hpp"
#include "decompile.hpp"
#include "helper.hpp"
#include "commandline_args.hpp"
#include "SalNumber.hpp"
#include <stdio.h>
#include <string.h>
#include <exception>

struct ItemBodyType {
	const char* name;
	uint8_t val1;
	uint8_t val2;
	uint8_t val3;
	uint8_t size;
};

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

const char* get_event_name(struct ItemBody* item_body) {
	if (item_body->type != 0x2f) {
		return NULL;
	}
	uint32_t event = *((uint32_t*)&item_body->size);

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
	case 0x4000:
		return "SAM_User";
	case 0x03e0:
		if (is_verbose()) {
			return "WM_DDE_First ! aka WM_DDE_Initiate";
		}
		return "WM_DDE_First"; // also called/same as: WM_DDE_Initiate // TODO: when print which one?
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

struct ItemBody* CItem::itembody_next(struct ItemBody* item_body, struct tagITEM* p_item) {
	if (item_body == NULL) {
		// get first
		// test for remaining length
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

struct ItemBody* CItem::get_itembody(class COutline* outline, uint32_t item_id, uint16_t type) {
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

void CItem::first_pass(class COutline* outline, uint32_t item_id, uint32_t* memory_item) {
	struct ItemBody* dlgitem = get_itembody(outline, item_id, 0x0b);
	if (dlgitem) {
		if (!CDlg::cur_dlg_item.empty()) {
			outline->set_dialog_dlgitem(CDlg::cur_dlg_item.top(), *((uint32_t*)(((char*)dlgitem)+1)), item_id);
		}
	}
}

void CItem::preprocess(class COutline* outline, uint32_t item_id, uint32_t* memory_item) {
}

void CItem::print(class COutline* outline, uint32_t item_id, uint32_t* memory_item){
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

void CItem::print_all_itembodies(class COutline* outline, uint32_t item_id) {
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
			case 4:
				oprintf("0x%08x",*((uint32_t*)&item_body->size));
				break;
			case 8:
				oprintf("0x%08x;0x%08x",((uint32_t*)&item_body->size)[0],((uint32_t*)&item_body->size)[1]);
				break;
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

void CItem::itembody_add_string(class COutline* outline, uint32_t item_id, const char* str) {
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

void CItem::decompile(class COutline* outline, uint32_t item_id, uint32_t* memory_item) {
	if (get_app_output_filename() && !get_itembody(outline, item_id, 0x01)) {

		const char16_t* str = outline->symbol_lookup(item_id);
		if (str) {
			size_t len = strlen_utf16(str)+2;
			if (len) {
				struct ItemBody* out = alloc<struct ItemBody*>(sizeof(struct ItemBody)+len);
				out->type = 0x01;
				out->size = (uint16_t)len;
				memcpy(out->data,str,len);
				add_itembody(outline, item_id, out);
				free(out);
			}

		}else if (get_itembody(outline, item_id, 0x09)) {

			struct outstream out;
			char* out_ptr = 0;
			out.pos = 0;
			out.buf = &out_ptr;
			oset(out);

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

void CItem::print_array_boundaries(class COutline* outline, uint32_t item_id) {
	// print array bounds
	struct ItemBody* item_body = get_itembody(outline, item_id, 0x28);
	if (item_body) {
		uint32_t* array_boundaries = (uint32_t*)item_body->data;
		if (array_boundaries[0]) {
			oputs("[");
			for (uint32_t d=0;d<array_boundaries[0];d++) {
				if (d) {
					oputs(",");
				}
				uint32_t lower = array_boundaries[2*d+1];
				uint32_t upper = array_boundaries[2*d+2];
				if (!lower && !upper) {
					oputs("*");
				}else if (!lower) {
					oprintf("%lu",((uint64_t)upper)+1);
				}else{
					oprintf("%u:%u",lower,upper);
				}
			}
			oputs("]");
		}
	}
}

void CItem::postprocess(class COutline* outline, uint32_t item_id, uint32_t* memory_item) {
}

void CItem::add_itembody(class COutline* outline, uint32_t item_id, struct ItemBody* item_body) {
	if (!item_body) {
		return;
	}
	tagITEM* p_item = outline->get_item(item_id);
	if (!p_item) {
		return;
	}
	uint16_t size = itembody_elementsize(item_body);
	if (!outline->change_item_size(item_id, p_item->data_length + size)) {
		fprintf(stderr,"error: resize of item 0x%08x failed",item_id);
		return;
	}
	p_item = outline->get_item(item_id);
	memcpy(&p_item->data[p_item->data_length-size],item_body,size);
}

void CItem::remove_itembody(class COutline* outline, uint32_t item_id, uint8_t itembody_type) {
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

void CItem::addvar(class COutline* outline, uint32_t memory_item, varscope var_scope, uint32_t item) {
	// get variable name and memory offset!!
	tagITEM* p_item = outline->get_item(item);
	if (!p_item) {
		return;
	}

	uint32_t var_offset = 0x00;
	uint32_t var_size = 0x00;
	struct ItemBody* item_body;
	item_body = get_itembody(outline, item, 0x33);
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
			uint32_t object_class = CObject::get_class(outline, item);
			if (object_class && outline->has_any_variable(object_class, varscope::CURRENT_OBJECT)) {
				outline->add_variable(memory_item, var_scope, var_offset, item);
				outline->add_variable(item, var_scope, 0, object_class);
				return;
			}
		}


		if (is_verbose()) {
			oprintf("[[WARN: var_size is 0, var_offset is 0x%04x]]",var_offset);
		}
		return; // don't add variable of empty size
	}

	outline->add_variable(memory_item, var_scope, var_offset, item);
}

CItem::~CItem() {
}


class COutlineVersion : public CItem {

public:
	COutlineVersion() : CItem(NULL) {
	}

	virtual void print(class COutline* outline, uint32_t item_id, uint32_t* memory_item){
		uint16_t ver = 0;
		if (outline->get_file_hdr().version < VERSION_TD60) {
			// too small
			ver = 41;
		}else if (outline->get_file_hdr().version > VERSION_TD74) {
			// too large
			ver = VERSION_TD74 + 41 - VERSION_TD60;
		}else{
			// supported area
			ver = outline->get_file_hdr().version + 41 - VERSION_TD60;
		}
		oprintf("Outline Version - 4.0.%u",ver);
	}

	virtual ~COutlineVersion() {
		CItem::~CItem();
	}
};


class CFunctionalVar : public CItem {

public:
	CFunctionalVar() : CItem(NULL) {
	}
	virtual void print(class COutline* outline, uint32_t item_id, uint32_t* memory_item){
		bool printed = false;
		struct ItemBody* item_body = get_itembody(outline, item_id, 0x14);
		if (item_body) {
			if (item_body->data[0] != 0x05) {
				// ?
			}
			if (item_body->data[0] == 0x05) {
				const char16_t* name = outline->symbol_lookup(*(uint32_t*)&item_body->data[4]);
				if (!name) {
					struct ItemBody* itb = get_itembody(outline, *(uint32_t*)&item_body->data[4], 0x01);
					if (itb) {
						name = (const char16_t*)itb->data;
					}
				}
				if (name) {
					print_utf16(name);
					oputs(":");
				}else{
					oprintf("FunctionalVar_0x%08x:",*(uint32_t*)&item_body->data[4]);
				}
				printed = true;
			}
		}

		if (!printed) {
			oputs("FunctionalVar:");
		}
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

		if (is_verbose()) {
			print_all_itembodies(outline, item_id);
		}
	}
	virtual ~CFunctionalVar() {
		CItem::~CItem();
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
	virtual void print(class COutline* outline, uint32_t item_id, uint32_t* memory_item){
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
				struct DecompileInfo di = { // @suppress("Invalid arguments")
						outline,
						memory_item,
						compile_block,
						(struct tagOPERATOR*)((char*)compile_block+compile_block->start),
						this->expected_datatype,
						varscope::NONE,
						0xff,
						NULL
				};
				decompile_expression(di);
			}
		}

	}
	virtual ~CStatement() {
		CItem::~CItem();
	}
};

/**
 * represents item types that contain a line of code
 */
class CLoop : public CItem {

private:
	static uint32_t last_loop_id;

public:
	CLoop() : CItem("Loop") {
	}
	/**
	 * decompile corresponding line of code
	 */
	virtual void print(class COutline* outline, uint32_t item_id, uint32_t* memory_item){
		CItem::print(outline, item_id, memory_item);

		if (outline->get_item_loop_info(item_id)) {
			outline->set_item_loop_info(item_id, ++CLoop::last_loop_id);
			oprintf(" loop_%u",CLoop::last_loop_id);
		}
	}

	virtual ~CLoop() {
		CItem::~CItem();
	}
};

uint32_t CLoop::last_loop_id = 0;

/**
 * represents item types that contain a line of code
 */
class CBreak : public CItem {
public:
	CBreak() : CItem("Break") {
	}
	/**
	 * decompile corresponding line of code
	 */
	virtual void print(class COutline* outline, uint32_t item_id, uint32_t* memory_item){
		CItem::print(outline, item_id, memory_item);

		struct ItemBody* item_body = get_itembody(outline, item_id, 0x03);
		if (item_body) {
			uint32_t item_ref = *((uint32_t*)&item_body->size);
			tagITEM* item_p = outline->get_item(item_ref);
			if (item_p) {
				if (item_p->type == Item::Type::LOOP) {
					uint32_t loop_id = outline->get_item_loop_info(item_ref);
					if (loop_id) {
						// TODO: determine whether the loop is the nearest break-out-item so that no label may be needed - only set additional item info if this is not the case
						oprintf(" loop_%u",loop_id);
					}
				}
			}
		}
	}

	virtual void first_pass(COutline* outline, uint32_t item_id, uint32_t* memory_item) {
		CItem::first_pass(outline, item_id, memory_item);
		struct ItemBody* item_body = get_itembody(outline, item_id, 0x03);
		if (item_body) {
			uint32_t item_ref = *((uint32_t*)&item_body->size);
			tagITEM* item_p = outline->get_item(item_ref);
			if (item_p) {
				if (item_p->type == Item::Type::LOOP) {
					// TODO: determine whether the loop is the nearest break-out-item
					// so that no label may be needed - only set additional item info
					// if this is not the case
					outline->set_item_loop_info(item_ref, 1);
				}
			}
		}
	}

	virtual ~CBreak() {
		CItem::~CItem();
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
	virtual void print(class COutline* outline, uint32_t item_id, uint32_t* memory_item){
		CItem::print(outline, item_id, memory_item);

		struct ItemBody* item_body = get_itembody(outline, item_id, 0x03);
		if (item_body) {
			uint32_t num = *((uint32_t*)&item_body->size);
			oprintf(" %u",num);
		}
	}

	virtual ~CCase() {
		CItem::~CItem();
	}
};

/**
 * represents item types that contain a line of code
 */
class CVar : public CItem {
protected:
	void decompile_helper(class COutline* outline, uint32_t item_id,const char16_t* assigned_value) {
		if (get_app_output_filename() && !get_itembody(outline, item_id, 0x01)) {

			const char16_t* str = outline->symbol_lookup(item_id);
			if (str) {
				size_t len = strlen_utf16(str)+2;
				if (len) {

					size_t assign_len = 0;
					if (assigned_value && *assigned_value) {
						assign_len = 6 + strlen_utf16(assigned_value);
					}

					struct ItemBody* out = alloc<struct ItemBody*>(sizeof(struct ItemBody)+len+assign_len);
					out->type = 0x01;
					out->size = (uint16_t)(len + assign_len);
					memcpy(out->data,str,len);

					if (assign_len) {
						char16_t equals[3] = {' ','=',' '};
						memcpy(out->data+len-2,equals,6);
						memcpy(out->data+len+4,assigned_value,assign_len-4);
					}

					add_itembody(outline, item_id, out);
					free(out);
				}
			}
		}
	}

	void decompile_number(class COutline* outline, uint32_t item_id, void (*sprint_num)(char*,const struct SalNumber*)){
		if (get_app_output_filename() && !get_itembody(outline, item_id, 0x01)) {
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
	virtual void print(class COutline* outline, uint32_t item_id, uint32_t* memory_item){
		CItem::print(outline, item_id, memory_item);
		CItem::print_array_boundaries(outline, item_id);
	}
	virtual ~CVar() {
		CItem::~CItem();
	}
};

/**
 * represents preinitialized constant variable
 */
class CNumber : public CVar {
public:
	CNumber() : CVar("Number:") {
	}

	virtual void print(class COutline* outline, uint32_t item_id, uint32_t* memory_item){
		CItem::print(outline, item_id, memory_item);

		struct ItemBody* item_body = get_itembody(outline, item_id, 0x2e);
		if (item_body) {
			oputs(" = ");
			print_number((SalNumber*)item_body->data);
		}
	}

	virtual void decompile(class COutline* outline, uint32_t item_id, uint32_t* memory_item){
		if (get_app_output_filename() && !get_itembody(outline, item_id, 0x01)) {
			decompile_number(outline, item_id, sprint_number);
		}
	}

	virtual ~CNumber() {
		CItem::~CItem();
	}
};

/**
 * represents preinitialized constant variable
 */
class CDateTime : public CVar {
public:
	CDateTime() : CVar("Date/Time:") {
	}

	virtual void print(class COutline* outline, uint32_t item_id, uint32_t* memory_item){
		CItem::print(outline, item_id, memory_item);

		struct ItemBody* item_body = get_itembody(outline, item_id, 0x2e);
		if (item_body) {
			oputs(" = ");
			print_date((SalNumber*)item_body->data);
		}
	}

	virtual void decompile(class COutline* outline, uint32_t item_id, uint32_t* memory_item){
		if (get_app_output_filename() && !get_itembody(outline, item_id, 0x01)) {
			decompile_number(outline, item_id, sprint_date);
		}
	}

	virtual ~CDateTime() {
		CItem::~CItem();
	}
};

/**
 * represents preinitialized constant variable
 */
class CBoolean : public CVar {
public:
	CBoolean() : CVar("Boolean:") {
	}

	virtual void print(class COutline* outline, uint32_t item_id, uint32_t* memory_item){
		CItem::print(outline, item_id, memory_item);

		struct ItemBody* item_body = get_itembody(outline, item_id, 0x2e);
		if (item_body) {
			oprintf(" = %s",boolval((SalNumber*)item_body->data)?"TRUE":"FALSE");
		}
	}

	virtual void decompile(class COutline* outline, uint32_t item_id, uint32_t* memory_item){
		if (get_app_output_filename() && !get_itembody(outline, item_id, 0x01)) {
			decompile_number(outline, item_id, sprint_bool);
		}
	}

	virtual ~CBoolean() {
		CItem::~CItem();
	}
};

/**
 * represents preinitialized constant variable
 */
class CString : public CVar {
public:
	CString() : CVar("String:") {
	}

	virtual void print(class COutline* outline, uint32_t item_id, uint32_t* memory_item){
		CItem::print(outline, item_id, memory_item);

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

	virtual void decompile(class COutline* outline, uint32_t item_id, uint32_t* memory_item){
		if (get_app_output_filename() && !get_itembody(outline, item_id, 0x01)) {
			const struct String* str = NULL;
			struct ItemBody* item_body = get_itembody(outline, item_id, 0x2e);
			if (item_body) {
				str = outline->string_lookup(*((uint16_t*)item_body->data));

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
		}
	}

	virtual ~CString() {
		CItem::~CItem();
	}
};

const struct MatchItemsToScope CCON[] = {
		// {varscope::INTERNAL_FUNCTION_PARAM,0x89}, // Parameters [intern function] // TODO: "Parameters" item may have an offset... --> handle is somehow??
		{varscope::NONE, 0x00}};

class COn : public CVarScope {
public:
	COn() : CVarScope("On", CCON) {
	}
	/**
	 * decompile corresponding line of code
	 */
	virtual void print(class COutline* outline, uint32_t item_id, uint32_t* memory_item){
		CItem::print(outline, item_id, memory_item);

		AVOID_COMPILED_UNCOMPILED_DUPLICATES

		struct ItemBody* item_body = get_itembody(outline, item_id, 0x2f);
		if (item_body) {
			oputs(" ");
			if (!get_event_name(item_body)) {
				oprintf("%u",*((uint32_t*)&item_body->size));
			}else{
				oputs(get_event_name(item_body));
			}
		}
	}
	virtual ~COn() {
		CVarScope::~CVarScope();
	}

	void decompile(class COutline* outline, uint32_t item_id, uint32_t* memory_item) {
		if (get_app_output_filename()) {
			// replace 0x2f itembody by string itembody
			struct ItemBody* item_body = get_itembody(outline, item_id, 0x2f);
			if (item_body) {
				if (!get_event_name(item_body)) {
					char tmp[30];
					sprintf(tmp,"%u",*((uint32_t*)&item_body->size));
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

	static void callback0(class COutline* outline, uint32_t item, void* param) {
		struct ItemBody* item_body = get_itembody(outline, item, 0x0d);
		if (item_body) {
			uint32_t class_id = *((uint32_t*)&item_body->size);
			outline->add_class_item(class_id, item);
		}
		uint16_t type[] = {
				Item::Type::CLASS_VARIABLES,
				0
		};
		outline->find_children_of_type_and_run(callback1, &item, item, type, false);
	}

	static void callback1(class COutline* outline, uint32_t item, void* param) {
		outline->find_children_of_type_and_run(callback2, param, item, NULL, false);
	}
	static void callback2(class COutline* outline, uint32_t item, void* param) {
		addvar(outline, *(uint32_t*)param, varscope::STATIC_CLASS_VAR, item);
	}

public:
	CClassDefinitions(const char* str) : CItem(str) {
	}

	virtual void first_pass(class COutline* outline, uint32_t item_id, uint32_t* memory_item) {
		CItem::first_pass(outline, item_id, memory_item);
		outline->find_children_of_type_and_run(callback0, NULL, item_id, NULL, false);
	}

	virtual ~CClassDefinitions() {
		CItem::~CItem();
	}
};


void CGlobalDecs::callback0(class COutline* outline, uint32_t item, void* param) {
	// process all variables declared inside this node
	outline->find_children_of_type_and_run(callback1, param, item, 0, false);
}

void CGlobalDecs::callback1(class COutline* outline, uint32_t item, void* param) {
	addvar(outline, *(uint32_t*)param, varscope::LIB_GLOBALS, item);
}

uint32_t CGlobalDecs::lib_globals = 0;

CGlobalDecs::CGlobalDecs(const char* str) : CItem(str) {
}

void CGlobalDecs::first_pass(class COutline* outline, uint32_t item_id, uint32_t* memory_item) {
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

void CGlobalDecs::preprocess(class COutline* outline, uint32_t item_id, uint32_t* memory_item) {
	CItem::preprocess(outline, item_id, memory_item);
}

CGlobalDecs::~CGlobalDecs() {
	CItem::~CItem();
}


// process top node of variable scope
void CVarScope::callback1(class COutline* outline, uint32_t item, void* param) {
	// process all variables declared inside this node
	outline->find_children_of_type_and_run(callback2, param, item, NULL, false);
}
// process single variable node
void CVarScope::callback2(class COutline* outline, uint32_t item, void* param) {
	struct Params* params = (struct Params*) param;
	addvar(outline, *params->memory_item, *params->var_scope, item);
}



CVarScope::CVarScope(const char* str, const struct MatchItemsToScope* scope) : CItem(str), scope(scope) {
}

void CVarScope::first_pass(class COutline* outline, uint32_t item_id, uint32_t* memory_item) {
	CItem::first_pass(outline, item_id, memory_item);
	for (size_t i=0; scope[i].sc != varscope::NONE; i++) {
		uint16_t type[] = {
				scope[i].item_type,
				0
		};
		struct CVarScope::Params p = {type, &scope[i].sc, &item_id}; // @suppress("Invalid arguments")
		outline->find_children_of_type_and_run(callback1, &p, item_id, type);
	}
}

void CVarScope::preprocess(class COutline* outline, uint32_t item_id, uint32_t* memory_item) {
	for (size_t i=0; scope[i].sc != varscope::NONE; i++) {
		memory_item[scope[i].sc] = item_id;
	}
	CItem::preprocess(outline, item_id, memory_item);
}

void CVarScope::postprocess(class COutline* outline, uint32_t item_id, uint32_t* memory_item) {
	/*
	for (size_t i=0; scope[i].sc != varscope::NONE; i++) {
	}
	*/
}
CVarScope::~CVarScope() {
	CItem::~CItem();
}


const struct MatchItemsToScope CCLASS_TYPES[2] = {{varscope::CURRENT_OBJECT, Item::Type::INSTANCE_VARIABLES},{varscope::NONE,0}};
void CClass::callback3(class COutline* outline, uint32_t item, void* param) {
		// process all variables declared inside this node
		outline->find_children_of_type_and_run(callback4, param, item, NULL, false);
	}
	// process single variable node
void CClass::callback4(class COutline* outline, uint32_t item, void* param) {
	// resolve item address, add them to scope (call CClass), find out offset...

	// get variable name and memory offset
	uint32_t classdef_pointer = 0;
	uint32_t var_offset = 0;
	struct ItemBody* item_body = get_itembody(outline, item, 0x33);
	if (item_body) {
		var_offset = *((uint32_t*)((uint8_t*)item_body+1));
	}
	item_body = get_itembody(outline, item, 0x13);
	if (item_body) {
		classdef_pointer = *((uint32_t*)((uint8_t*)item_body+1));
	}

	if (!classdef_pointer) {
		return;
	}
	outline->add_variable(*(uint32_t*)param, varscope::CURRENT_OBJECT, var_offset, classdef_pointer);
}


CClass::CClass(const char* str) : CVarScope(str, CCLASS_TYPES) {
}

void CClass::first_pass(class COutline* outline, uint32_t item_id, uint32_t* memory_item) {
	uint16_t type[] = {
			Item::Type::DERIVED_FROM, //// TODO: there exist three different "Derived From:" items, e.g. one for interfaces... --> TODO: build app that uses them and watch instance variable access
			Item::Type::DERIVED_FROM_INTERFACE,
			0
	};
	outline->find_children_of_type_and_run(callback3, &item_id, item_id, type);
	CVarScope::first_pass(outline, item_id, memory_item);
}

void CClass::preprocess(class COutline* outline, uint32_t item_id, uint32_t* memory_item) {
	CVarScope::preprocess(outline, item_id, memory_item);
}

CClass::~CClass() {
	CVarScope::~CVarScope();
}

CObject::CObject (const char* str) : CClass(str) {
}

uint32_t CObject::get_class(class COutline* outline, uint32_t item_id) {
	struct ItemBody* ib = get_itembody(outline, item_id, 0x14);
	if (!ib) {
		return 0;
	}
	if (ib->size <= 0x02) {
		return 0;
	}
	uint16_t type = *((uint16_t*)ib->data); // should match item->type value!!
	uint32_t offset = 0;
	switch (type) {
	case 0x01: // Form Window
		offset = 0x04; // may depend on version of Team Developer
		break;
	case 0x06: // Pushbutton
		offset = 0x10; // may depend on version of Team Developer
		break;
	default:
		offset = 0x10; // FIXME: THIS IS NOT CORRECT!!!!!
		//return 0; // TODO: not supported yet
	}
	if (ib->size < offset + sizeof(uint32_t)) {
		return 0;
	}
	uint32_t class_type = *((uint32_t*)&ib->data[offset]);
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

void CObject::first_pass(class COutline* outline, uint32_t item_id, uint32_t* memory_item) {
	CItem::first_pass(outline,item_id,memory_item);
}

void CObject::preprocess(class COutline* outline, uint32_t item_id, uint32_t* memory_item) {
	uint32_t it_class = get_class(outline, item_id);
	if (!it_class) {
		return;
	}
	memory_item[varscope::CURRENT_OBJECT] = it_class;
}

void CObject::print(class COutline* outline, uint32_t item_id, uint32_t* memory_item) {
	uint32_t it_class = get_class(outline, item_id);
	if (!it_class) {
		CClass::print(outline, item_id, memory_item);
		return;
	}
	const char16_t* class_name = outline->symbol_lookup(it_class);
	if (!class_name) {
		CClass::print(outline, item_id, memory_item);
		return;
	}
	print_utf16(class_name);
	oputs(": ");
	const char16_t* str = outline->symbol_lookup(item_id);
	if (str) {
		print_utf16(str);
	}else{
		struct ItemBody* item_body = get_itembody(outline, item_id, 0x01);
		if (item_body) {
			print_utf16((const char16_t*)item_body->data, item_body->size);
		}
	}

	if (is_verbose()) {
		print_all_itembodies(outline,item_id);
	}
}

CObject::~CObject() {
	CClass::~CClass();
}

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

std::stack<uint32_t> CDlg::cur_dlg_item = std::stack<uint32_t>();

CDlg::CDlg(const char* str) : CObject(str) {
}

void CDlg::callback0(class COutline* outline, uint32_t item, void* param) {
	struct Params* params = (struct Params*) param;
	outline->find_children_of_type_and_run(callback1, param, item, params->type);
}

void CDlg::first_pass(class COutline* outline, uint32_t item_id, uint32_t* memory_item) {
	CObject::first_pass(outline, item_id, memory_item);
	const struct MatchItemsToScope scope[] = {
			{varscope::CURRENT_FORM, 0x0076},
			{varscope::CURRENT_FORM, 0x0191},
			{varscope::CURRENT_FORM, 0x0072},
			{varscope::NONE, 0x00}};
	CVarScope vc(NULL, scope);
	vc.first_pass(outline, item_id, memory_item);

	// Tool Bar
	uint16_t type1[] = {0x10e, 0x00};
	uint16_t type2[] = {0x072, 0x00};
	varscope sc = varscope::CURRENT_FORM;
	struct CVarScope::Params p = {type2, &sc, &item_id}; // @suppress("Invalid arguments")
	outline->find_children_of_type_and_run(callback0, &p, item_id, type1);

	uint32_t object_class = CObject::get_class(outline, item_id);
	if (object_class && outline->has_any_variable(object_class, varscope::CURRENT_OBJECT)) {
		outline->add_variable(item_id, varscope::CURRENT_FORM, 0, object_class);
	}

	cur_dlg_item.push(item_id);
}

void CDlg::preprocess(class COutline* outline, uint32_t item_id, uint32_t* memory_item) {
	CObject::preprocess(outline, item_id, memory_item);
	memory_item[varscope::CURRENT_FORM] = item_id;
	cur_dlg_item.push(item_id);
}

void CDlg::postprocess(class COutline* outline, uint32_t item_id, uint32_t* memory_item) {
	if (cur_dlg_item.top() != item_id || cur_dlg_item.empty()) {
		throw std::exception();
	}
	cur_dlg_item.pop();
	CObject::postprocess(outline, item_id, memory_item);
}

CDlg::~CDlg() {
	CObject::~CObject();
}


CItem* tag_items[TAG_ITEMS_AMOUNT] = {
		new CItem(NULL),
		new CDlg("Form Window:"),
		new CDlg("Table Window:"),
		new CObject("Child Table:"),
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
		new CBreak(),
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
		new CItem("Export Ordinal:"),
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
		new CStatement("If"),
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
		new CStatement("Return"),
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
		new CClass("Dialog Box Class:"),
		new CClass("Form Window Class:"),
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
		new CObject("Child Grid:"),
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
		new CItem("Thread Start"),
		new CItem("Thread Before Start"),
		new CItem("Thread Report Progress"),
		new CItem("Thread Finished"),
		new CItem("Background Threads:"),
		new CItem("Thread Events"),
		new CClass("Background Worker Class:"),
		new CItem("BackgroundWorkerVar:"),
		new CItem("Protected Variable:"),
		new CItem("Protected Function:"),
		new CItem("Show Percent:"),
		new CItem("IME Mode:"),
		new CItem("Dynalink Grid Window:"),
		new CItem("Thread Report Error"),
		new CItem("Always Show Drop Button?"),
		new CItem("MDI Tabs:")
};
