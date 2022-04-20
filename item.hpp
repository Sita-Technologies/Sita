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

#ifndef ITEM_HPP_
#define ITEM_HPP_
#include <stdint.h>
#include <stack>

class COutline;

enum varscope {
	NONE = 0x00,
	INTERNAL_FUNCTION_VAR = 0x01,
	INTERNAL_FUNCTION_PARAM = 0x02,
	INTERNAL_FUNCTION_PARAM_PRE = 0x03,
	CURRENT_FORM = 0x04,
	GLOBAL_SEGMENT = 0x05, // system variables
	SQL_INTO_BIND_SEGMENT = 0x06, // TODO: when is it used?
	CURRENT_OBJECT = 0x07,
	DS_OF_OPERATOR = 0x08,
	CURRENT_FORM_CLASS = 0x09, // TODO: when is it used?
	SCOPE_0a = 0x0a, // TODO: when is it used? how does the lookup work?
	SCOPE_0b = 0x0b, // TODO: when is it used? how does the lookup work?
	SCOPE_0d = 0x0d, // TODO: when is it used? how does the lookup work?
	LIB_GLOBALS = 0x0e,
	STATIC_CLASS_VAR = 0x0f, // pointer to class is stored in next parameter
	DYN_LIB = 0x10 // see OamDynLibResolveVarAddress
};

struct MatchItemsToScope {
	varscope sc;
	uint16_t item_type; // TODO: replace by tbd item-type-enum
};

/**
 * represents an item-type, i.e. a class of specific items, not just a single item!
 */
class CItem {
private:
	const char* name;

protected:
	static void addvar(class COutline* outline, uint32_t memory_item, varscope var_scope, uint32_t item);
	static void print_array_boundaries(class COutline* outline, uint32_t item_id);
	static void print_all_itembodies(class COutline*, uint32_t);
	static uint16_t itembody_elementsize(struct ItemBody* item_body);
	static struct ItemBody* itembody_next(struct ItemBody* item_body, struct tagITEM* item);

public:

	static void add_itembody(class COutline* outline, uint32_t item_id, struct ItemBody* item_body);
	static void remove_itembody(class COutline* outline, uint32_t item_id, uint8_t itembody_type);
	static void itembody_add_string(class COutline* outline, uint32_t item_id, const char* str);
	static struct ItemBody* get_itembody(class COutline* outline, uint32_t item_id, uint16_t type);
	static uint32_t get_funcvar_typedef(class COutline* outline, uint32_t item_id);

	/**
	 * name: name of item type
	 */
	CItem(const char* name);
	/**
	 * first pass without printing (e.g. for lpClassMap initialization...)
	 */
	virtual void first_pass(class COutline*, uint32_t, uint32_t* memory_item);
	/**
	 * if item->type is a local memory scope (e.g. a Function), then safe declared variables in mem-array
	 */
	virtual void preprocess(class COutline*, uint32_t, uint32_t* memory_item);
	/**
	 * print item (name of its type (see Constructor) and corresponding name/parameters/decompiled line of code/...)
	 */
	virtual void print(class COutline*, uint32_t, uint32_t* memory_item);
	/**
	 * change item in outline: remove compiled code, add decompiled code
	 */
	virtual void decompile(class COutline*, uint32_t, uint32_t* memory_item);
	/**
	 * if item->type is a local memory scope (e.g. a Function), then free corresponding mem-array (see preprocess method)
	 */
	virtual void postprocess(class COutline*, uint32_t, uint32_t* memory_item);
	virtual ~CItem();
};


class CVarScope : public CItem {
private:
	const struct MatchItemsToScope* scope;
	// process single variable node
	static void callback2(class COutline* outline, uint32_t item, void* param);

protected:
	struct Params {
		const uint16_t* type;
		const varscope* var_scope;
		uint32_t* memory_item;
	};

	// process top node of variable scope
	static void callback1(class COutline* outline, uint32_t item, void* param);

public:
	CVarScope(const char* str, const struct MatchItemsToScope* scope);
	virtual void first_pass(class COutline*, uint32_t, uint32_t* memory_item);
	virtual void preprocess(class COutline* outline, uint32_t item_id, uint32_t* memory_item);
	virtual void postprocess(class COutline* outline, uint32_t item_id, uint32_t* memory_item);
	virtual ~CVarScope();
};

class CClass : public CVarScope {
private:
	// process top node of variable scope
	static void callback3(class COutline* outline, uint32_t item, void* param);
	// process single variable node
	static void callback4(class COutline* outline, uint32_t item, void* param);

public:
	CClass(const char* str);
	virtual void first_pass(class COutline*, uint32_t, uint32_t* memory_item);
	virtual void preprocess(class COutline* outline, uint32_t item_id, uint32_t* memory_item);

	virtual ~CClass();
};

class CObject : public CClass {
public:
	CObject (const char* str);
	static uint32_t get_class(class COutline* outline, uint32_t item_id);
	virtual void first_pass(class COutline*, uint32_t, uint32_t* memory_item);
	virtual void preprocess(class COutline* outline, uint32_t item_id, uint32_t* memory_item);
	virtual void print(class COutline* outline, uint32_t item_id, uint32_t* memory_item);
	virtual ~CObject();
};

class CDlg : public CObject {
private:
	static void callback0(class COutline* outline, uint32_t item, void* param);
public:
	static std::stack<uint32_t> cur_dlg_item;
	CDlg(const char* str);
	virtual void first_pass(class COutline* outline, uint32_t item_id, uint32_t* memory_item);
	virtual void preprocess(class COutline* outline, uint32_t item_id, uint32_t* memory_item);
	virtual void postprocess(class COutline* outline, uint32_t item_id, uint32_t* memory_item);
	virtual ~CDlg();
};

class CGlobalDecs : public CItem {
private:
	static void callback0(class COutline* outline, uint32_t item, void* param);
	static void callback1(class COutline* outline, uint32_t item, void* param);

public:
	static uint32_t lib_globals;
	CGlobalDecs(const char* str);
	virtual void first_pass(class COutline* outline, uint32_t item_id, uint32_t* memory_item);
	virtual void preprocess(class COutline* outline, uint32_t item_id, uint32_t* memory_item);
	virtual ~CGlobalDecs();
};

#define TAG_ITEMS_AMOUNT 752
extern CItem* tag_items[TAG_ITEMS_AMOUNT];

/**
 * old class; TODO: should be removed in the future
 */
class Item {

public:
	//       maybe keep this enum outside of the Item class, but maybe reduce to needed values
	//       if the enum is not reduced, note that it is incomplete compared to the tag_items array.
	enum Type {
		POINTER = 0x00,
		FORM_WINDOW = 0x01,
		DATA_FIELD = 0x04,
		PUSHBUTTON = 0x06,
		APPLICATION_ACTIONS = 0x1c,
		BACKGROUND_COLOR = 0x22,
		BOOLEAN = 0x25,
		BORDER_COLOR = 0x28,
		BREAK = 0x2b,
		CHECKED_WHEN = 0x2d,
		CONSTANTS = 0x34,
		DATE_TIME = 0x3a,
		DESCRIPTION = 0x3f,
		ACTIONS = 0x46,
		ELSE_IF = 0x48,
		ELSE = 0x49,
		ENABLED_WHEN = 0x4a,
		EXTERNAL_FUNCTIONS = 0x51,
		EXT_FUNCTION = 0x52,
		EXT_PARAMETERS = 0x56,
		FILE_HANDLE = 0x67,
		CONTENTS = 0x72,
		WINDOW_VARIABLES = 0x76,
		CALL = 0x7b,
		GLOBAL_DECLARATIONS = 0x7c,
		IF = 0x81,
		LIBRARIES = 0x82,
		FILE_INCLUDE = 0x83,
		INTERNAL_FUNCTIONS = 0x86,
		INT_FUNCTION = 0x87,
		LOCAL_VARIABLES = 0x88, // KEEP
		INT_PARAMETERS = 0x89,
		RETURNS = 0x8a,
		CASE = 0x8b,
		DEFAULT = 0x8c,
		SELECT_CASE = 0x8d,
		LIBRARY_NAME = 0x91,
		LINE_COLOR = 0x93,
		WINDOW_DEFAULTS_LINE = 0x94,
		LONG_STRING = 0x9a,
		LOOP = 0x9b,
		MENU = 0x9f, // vs. _MENU = 0x128
		MENU_ACTIONS = 0xa0,
		MENU_ITEM = 0xa2,
		MENU_SETTINGS = 0xa3,
		MENU_SEPARATOR = 0xa5,
		NUMBER = 0xac,
		MESSAGE_ACTIONS = 0xad,
		ON = 0xae,
		WHEN_SQLERROR = 0xaf,
		RETURN = 0xbe,
		RECEIVE_STRING = 0xc5,
		SET = 0xc9,
		SQL_HANDLE = 0xcc,
		STRING = 0xce,
		SYSTEM = 0xd0,
		USER = 0xde,
		VARIABLES = 0xdf,
		WHILE = 0xe3,
		WINDOW_DEFAULTS = 0xe4,
		WINDOW_HANDLE = 0xea,
		FORMATS = 0xee,
		NUMBER_FORMAT = 0xef,
		DATE_TIME_FORMAT = 0xf0,
		DERIVED_FROM = 0xf3,
		CLASS_DEFINITIONS = 0xf4,
		FUNCTIONAL_CLASS_OBJECT = 0x105,
		INSTANCE_VARIABLES = 0x109,
		DIALOG_TOOLBAR = 0x10e,
		FUNCTIONS = 0x116,
		METHODS = 0x117, // also named "Functions" in SQLWindows
		STATIC_VARIABLES = 0x119,
		NAMED_MENUS = 0x12b,
		INPUT = 0x153,
		WINDOW_PARAMETERS = 0x191,
		RESOURCES = 0x196,
		DYNALIB = 0x1c9,
		GUID = 0x1f0,
		HELP_STRING = 0x1fc,
		_HELP_CONTEXT = 0x1fd,
		ATTRIBUTES = 0x204,
		SESSION_HANDLE = 0x209,
		ENUMERATIONS = 0x20d,
		ENUM = 0x20e,
		ENUM_ITEM = 0x20f,
		THREAD_SAFE = 0x213,
		WHEN_SESSIONERROR = 0x21e,
		BINARY = 0x253,
		WINDOW_DEFAULTS_PANE_SEPARATOR = 0x284,
		EXTERNAL_ASSEMBLIES = 0x28e,
		NAMED_TOOLBARS = 0x29a,
		WHEN_EXCEPTION = 0x2aa,
		END_EXCEPTION = 0x2ab,
		RETHROW = 0x2ac,
		WINDOW_DEFAULTS_PROGRESS_BAR = 0x2b6,
		RIBBON = 0x2bc,
		THROW = 0x2cc,
		NAMED_EXCEPTIONS = 0x2cd,
		THREAD_START = 0x2e0,
		BACKGROUND_THREADS = 0x2e4,
		BACKGROUND_WORKER_CLASS = 0x2e6,
		BACKGROUND_WORKER_VAR = 0x2e7,

		CHECK_BOX_CLASS = 0xfe,
		INTERFACE = 0x202,
		CLASS_VARIABLES = 0x118,
		CONSTRUCTOR_DESTRUCTOR = 0x2d1,
		CONSTRUCTOR = 0x2d2,
		DESTRUCTOR = 0x2d3,
		CONSTRUCTOR_PARAMETERS = 0x2d4,
		INTERFACE_METHODS = 0x205,
		INTERFACE_METHOD = 0x206,
		INTERFACE_ATTRIBUTES = 0x207,
		DISPATCH_NUMBER = 0x208,
		DERIVED_FROM_INTERFACE = 0x214,
		FUNCTIONAL_CLASS = 0xf5,
		CLASS_DERIVED_FROM = 0x106,
		INTERFACE_OBJECT = 0x203,
		MENU_ITEM_NAME = 0x1bc,
		ACTIVEX_CLASS = 0x1ee,
		RECEIVE_DATE_TIME = 0xc0,
		RECEIVE_FILE_HANDLE = 0xc1,
		RECEIVE_LONG_STRING = 0xc2,
		RECEIVE_NUMBER = 0xc3,
		RECEIVE_SQL_HANDLE = 0xc4,
		RECEIVE_WINDOW_HANDLE = 0xc6,
		RECEIVE_SESSION_HANDLE = 0x20a,
		RECEIVE_BINARY = 0x254,
		RECEIVE_BOOLEAN = 0xbf,
		MENU_ROW = 0xa4,
		POPUP_MENU = 0xb8,
		NAMED_MENU = 0x12a,
		CHECK_BOX = 0x08,
		GROUP_BOX = 0x09,
		FRAME = 0x10,
		ACTIVEX = 0x1ed,
		WPF_CUSTOM = 0x293,
		NAVIGATION_BAR = 0x275,
		NAVBAR_CONTENTS = 0x276,
		PANE = 0x277,
		LINE = 0x11,
		LINE_CLASS = 0x146,
		SEPARATOR_CLASS = 0x269,
		CO_CLASS = 0x1f9,
		CO_CLASS_ATTRIBUTES = 0x1fb,
		CREATABLE = 0x1fe,
		CO_CLASS_EVENTS = 0x200,
		CO_CLASS_OBJECT = 0x1fa,
		MDI_WINDOW_CLASS = 0x120,
		CHILD_GRID = 0x235,
		CHILD_GRID_CONTENTS = 0xd3,
		COLUMN = 0x0d,
		LIST_VALUES = 0x1d3,
		TEXT = 0x1d4,
		DIALOG_BOX = 0x42,
		MDI_Window = 0x13,
		MDI_WINDOW_CONTENTS = 0x9d,
		GRID_WINDOW = 0x25c,
		TABLE_WINDOW = 0x02,
		COM_PROXY_CLASS = 0x1f7,
		WPFCUSTOM_CLASS = 0x294,
		DATE_PICKER = 0x225,
		THREAD_EVENTS = 0x2e5,
		EVENT_PARAMETERS = 0x2df,
		THREAD_BEFORE_START = 0x2e1,
		THREAD_REPORT_PROGRESS = 0x2e2,
		THREAD_FINISHED = 0x2e3,
		THREAD_REPORT_ERROR = 0x2ed,
		BACKGROUND_TEXT_CLASS = 0x144,
		CUSTOM_CONTROL_CLASS = 0x11a,
		EXPORT_ORDINAL = 0x4d,
		EXT_RETURNS = 0x57,
		EXT_BOOLEAN = 0x4e,
		EXT_WINDOW_HANDLE = 0x63,
		EXT_RECEIVE_BOOLEAN = 0x58,
		DIALOG_BOX_CLASS = 0xf6,
		EXT_NUMBER = 0x55,
		EXT_RECEIVE_STRING = 0x5e,
		EXT_FUNCTIONAL_CLASS_OBJECT = 0x1db,

		VERTICAL_SCROLL_BAR_CLASS = 0x100,
		TREE_CONTROL_CLASS = 0x26c,
		TABLE_WINDOW_CLASS = 0xf8,
		TAB_BAR_CLASS = 0x23b,
		TAB_BAR_CONTENTS = 0x23f,
		TAB = 0x240,
		RICH_TEXT_CONTROL_CLASS = 0x246,
		RADIO_BUTTON_CLASS = 0xfd,
		PUSHBUTTON_CLASS = 0xfc,
		PROGRESS_BAR_CLASS = 0x2ba,
		PICTURE_CLASS = 0x104,
		OPTION_BUTTON_CLASS = 0x11c,
		NAVIGATION_BAR_CLASS = 0x279,
		MULTILINE_FIELD_CLASS = 0xfb,
		LIST_BOX_CLASS = 0x102,
		LIST_INITIALIZATION = 0x97,
		LIST_INIT_TEXT = 0x98,
		HORIZONTAL_SCROLL_BAR_CLASS = 0xff,
		GROUP_BOX_CLASS = 0x145,
		GRID_WINDOW_CLASS = 0x25d,
		GENERAL_WINDOW_CLASS = 0x1c8,
		FRAME_CLASS = 0x147,
		FORM_WINDOW_CLASS = 0xf7,
		DATE_TIME_PICKER_CLASS = 0x22d,
		DATE_PICKER_CLASS = 0x226,
		DATA_FIELD_CLASS = 0xfa,
		COMBO_BOX_CLASS = 0x103,
		COLUMN_CLASS = 0x101,
		CHILD_TABLE_CLASS = 0xf9,
		CHILD_GRID_CLASS = 0x236,
		BACKGROUND_TEXT = 0x0c,
		COMBO_BOX = 0x0f,
		DATE_TIME_PICKER = 0x22c,
		HORIZONTAL_SCROLL_BAR = 0x0a,
		CHILD_TABLE = 0x03,
		GROUP_SEPARATOR = 0x7e,
		LIST_BOX = 0x0e,
		MULTILINE_FIELD = 0x05,
		OPTION_BUTTON = 0x14,
		PICTURE = 0x12,
		PROGRESS_BAR = 0x2b9,
		RADIO_BUTTON = 0x07,
		RICH_TEXT_CONTROL = 0x245,
		SEPARATOR = 0x268,
		TAB_BAR = 0x23a,
		TAB_CHILD = 0x241,
		TREE_CONTROL = 0x26b,
		TREEITEM = 0x26f,
		VERTICAL_SCROLL_BAR = 0x0b,
		NAMED_TOOLBAR_TOOLBAR = 0x29b,
		TITLE = 0x129,
		TOOLBAR_BUTTON = 0x29c,
		STATUS_TEXT = 0x12d,
		PICTURE_FILE_NAME = 0xf2,
		TOOLBAR_BUTTON_ACTIONS = 0x29d,
		PANE_CHILD = 0x278,
		PANE_SEPARATOR = 0x282,
		BITMAP = 0x197,
		ICON = 0x198,
		RES_FILE_NAME = 0x19a,
		EXT_DATE_TIME = 0x4f,
		EXT_STRING = 0x61,
		EXT_LIBRARY = 0x28f, // not existent in source
		EXT_FILE_HANDLE = 0x50,
		EXT_RECEIVE_FILE_HANDLE = 0x5a,
		EXT_RECEIVE_NUMBER = 0x5c,
		EXT_RECEIVE_DATE_TIME = 0x59,
		EXT_BINARY = 0x256,
		EXT_RECEIVE_BINARY = 0x257,
		CUSTOM_CONTROL = 0x16,
		OUTLINE_WINDOW_STATE = 0xb2,
		OUTLINE_WINDOW_LOCATION_AND_SIZE = 0xb1,
		OPTIONS_BOX_LOCATION = 0xb0,
		CLASS_EDITOR_LOCATION = 0x12e,
		TOOL_PALETTE_LOCATION = 0xdc,
		FULLY_QUALIFIED_EXTERNAL_REFERENCES = 0xba,
		REJECT_MULTIPLE_WINDOW_INSTANCES = 0x107,
		ENABLE_RUNTIME_CHECKS_OF_EXTERNAL_REFERENCES = 0x108,
		USE_RELEASE_4_0_SCOPE_RULES = 0x1b7,
		EDIT_FIELDS_READ_ONLY_ON_DISABLE = 0x21f,
		ASSEMBLY_SYMBOL_FILE = 0x28d,
		WINDOW_DEFAULTS_TOOL_BAR = 0x110,
		WINDOW_DEFAULTS_FORM_WINDOW = 0x78,
		WINDOW_DEFAULTS_DIALOG_BOX = 0x43,
		WINDOW_DEFAULTS_TABLE_WINDOW = 0xdd,
		WINDOW_DEFAULTS_TOP_LEVEL_GRID_WINDOW = 0x260,
		WINDOW_DEFAULTS_DATA_FIELD = 0x65,
		WINDOW_DEFAULTS_MULTILINE_FIELD = 0xaa,
		WINDOW_DEFAULTS_SPIN_FIELD = 0x175,
		WINDOW_DEFAULTS_BACKGROUND_TEXT = 0x24,
		WINDOW_DEFAULTS_PUSHBUTTON = 0xb9,
		WINDOW_DEFAULTS_RADIO_BUTTON = 0xbb,
		WINDOW_DEFAULTS_CHECK_BOX = 0x2c,
		WINDOW_DEFAULTS_OPTION_BUTTON = 0x176,
		WINDOW_DEFAULTS_GROUP_BOX = 0x7d,
		WINDOW_DEFAULTS_CHILD_TABLE_WINDOW = 0x2f,
		WINDOW_DEFAULTS_LIST_BOX = 0x96,
		WINDOW_DEFAULTS_COMBO_BOX = 0x33,
		WINDOW_DEFAULTS_FRAME = 0x7a,
		WINDOW_DEFAULTS_PICTURE = 0xb3,
		WINDOW_DEFAULTS_DATE_TIME_PICKER = 0x234,
		WINDOW_DEFAULTS_CHILD_GRID_WINDOW = 0x239,
		WINDOW_DEFAULTS_RICH_TEXT_CONTROL = 0x24a,
		WINDOW_DEFAULTS_DATE_PICKER = 0x262,
		WINDOW_DEFAULTS_TREE_CONTROL = 0x26d,
		WINDOW_DEFAULTS_NAVIGATION_BAR = 0x27c,
		WINDOW_DEFAULTS_TAB_BAR = 0x23e,
		GROUPBOX_STYLE = 0x265,
		DISPLAY_STYLE = 0x143,
		DISPLAY_STYLE_ROOT = 0x267,
		FONT_NAME = 0x6c,
		FONT_NAME_ROOT = 0x6d,
		FONT_SIZE = 0x6f,
		FONT_SIZE_ROOT = 0x70,
		FONT_ENHANCEMENT = 0x69,
		FONT_ENHANCEMENT_ROOT = 0x6a,
		TEXT_COLOR = 0xd9,
		TEXT_COLOR_ROOT = 0xda,
		BACKGROUND_COLOR_ROOT = 0x23,
		FLOW_DIRECTION = 0x2a9,
		PROTECTED_VARIABLE = 0x2e8,
		XML_NUMBERTYPE = 0x220,
		XML_DATETIMETYPE = 0x221,
		XML_DATATYPE = 0x222,
		XML_SERIALIZE = 0x223,
		XML_NULLS_ALLOWED = 0x224,
		EXT_SQL_HANDLE = 0x60,
		EXT_SESSION_HANDLE = 0x20b,
		EXT_STRUCTPOINTER = 0x1ba,
		EXT_STRUCT = 0x1c5,
		EXT_STRUCT_RECEIVE_BOOLEAN = 0x1bd,
		EXT_STRUCT_RECEIVE_DATE_TIME = 0x1be,
		EXT_STRUCT_RECEIVE_FILE_HANDLE = 0x1bf,
		EXT_STRUCT_RECEIVE_NUMBER = 0x1c0,
		EXT_STRUCT_RECEIVE_SQL_HANDLE = 0x1c1,
		EXT_STRUCT_RECEIVE_STRING = 0x1c4,
		EXT_STRUCT_RECEIVE_WINDOW_HANDLE = 0x1c2,
		EXT_STRUCT_TEMPLATE = 0x62,
		EXT_STRUCT_STRING = 0x1c3,
		EXT_RECEIVE_SQL_HANDLE = 0x5d,
		EXT_RECEIVE_SESSION_HANDLE = 0x20c,
		EXT_RECEIVE_WINDOW_HANDLE = 0x5f,
		COM_PROXY_CLASS_OBJECT = 0x1f8,
		PROTECTED_FUNCTION = 0x2e9,
		CURSOR = 0x199,
		RESOURCE_DICTIONARY = 0x2a0,
		BRUSH = 0x2a4,
		XAML = 0x2a5,

		APPLICATION_DESCRIPTION = 0x1d,
		OUTLINE_VERSION = 0xe0,
		DESIGNTIME_SETTINGS = 0x40,
		_MENU = 0x128, // vs. MENU = 0x9f ???
		WINDOWS_MENU = 0x12c,
		DEFAULT_CLASSES = 0x12f,
		//MENU_ITEM_NAME = 0x1bc

		// default classes
		DEFAULT_CLASS_MDI_WINDOW = 0x141,
		DEFAULT_CLASS_FORM_WINDOW = 0x130,
		DEFAULT_CLASS_DIALOG_BOX = 0x131,
		DEFAULT_CLASS_TABLE_WINDOW = 0x132,
		DEFAULT_CLASS_GRID_WINDOW = 0x25f,
		DEFAULT_CLASS_QUEST_WINDOW = 0x133,
		DEFAULT_CLASS_DATA_FIELD = 0x134,
		DEFAULT_CLASS_SPIN_FIELD = 0x172,
		DEFAULT_CLASS_MULTILINE_FIELD = 0x135,
		DEFAULT_CLASS_PUSHBUTTON = 0x136,
		DEFAULT_CLASS_RADIO_BUTTON = 0x137,
		DEFAULT_CLASS_OPTION_BUTTON = 0x173,
		DEFAULT_CLASS_CHILD_GRID = 0x237,
		DEFAULT_CLASS_RICH_TEXT_CONTROL = 0x247,
		DEFAULT_CLASS_SEPARATOR = 0x26a,
		DEFAULT_CLASS_TREE_CONTROL = 0x26e,
		DEFAULT_CLASS_NAVIGATION_BAR = 0x27a,
		DEFAULT_CLASS_PANE_SEPARATOR = 0x285,
		DEFAULT_CLASS_PROGRESS_BAR = 0x2b7,
		DEFAULT_CLASS_CHECK_BOX = 0x138,
		DEFAULT_CLASS_CHILD_TABLE = 0x139,
		DEFAULT_CLASS_QUEST_CHILD_WINDOW = 0x13a,
		DEFAULT_CLASS_LIST_BOX = 0x13b,
		DEFAULT_CLASS_COMBO_BOX = 0x13c,
		DEFAULT_CLASS_PICTURE = 0x13d,
		DEFAULT_CLASS_VERTICAL_SCROLL_BAR = 0x13e,
		DEFAULT_CLASS_HORIZONTAL_SCROLL_BAR = 0x13f,
		DEFAULT_CLASS_COLUMN = 0x140,
		DEFAULT_CLASS_BACKGROUND_TEXT = 0x148,
		DEFAULT_CLASS_GROUP_BOX = 0x149,
		DEFAULT_CLASS_LINE = 0x14a,
		DEFAULT_CLASS_FRAME = 0x14b,
		DEFAULT_CLASS_CUSTOM_CONTROL = 0x174,
		DEFAULT_CLASS_ACTIVEX = 0x1ef,
		DEFAULT_CLASS_DATE_PICKER = 0x227,
		DEFAULT_CLASS_DATE_TIME_PICKER = 0x22e,
		DEFAULT_CLASS_TAB_BAR = 0x23c
	};

	// static const char* type_name(enum Item::Type type);
};

#endif
