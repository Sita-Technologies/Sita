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

#include "decompile.hpp"
#include "COutline.hpp"
#include "helper.hpp"
#include "item.hpp"
#include "sal_functions.hpp"
#include "SalNumber.hpp"
#include "system_variables.hpp"
#include <exception>
#include <stdio.h>
#include "commandline_args.hpp"

#define PRECEDENCE_MIN         0x00
#define PRECEDENCE_NOT         0x01 // !
#define PRECEDENCE_MUL         0x02 // *
#define PRECEDENCE_ADD         0x03 // +
#define PRECEDENCE_CONCAT      0x04 // .
#define PRECEDENCE_REL_COMPARE 0x05 // <=, >=, <, >
#define PRECEDENCE_EQ_NEQ      0x06 // ==, !=
#define PRECEDENCE_BIT_AND     0x07 // &
#define PRECEDENCE_BIT_OR      0x08 // |
#define PRECEDENCE_LOG_AND     0x09 // &&
#define PRECEDENCE_LOG_OR      0x0a // ||
#define PRECEDENCE_ASSIGN      0x0b // =
#define PRECEDENCE_MAX         0xff // ,

extern const char* DispatchArray[];
extern void (*DispatchFunction[])(struct DecompileInfo di);

datatype get_datatype_from_declaration(class COutline* outline, uint32_t item) {
	tagITEM* p_item = outline->get_item(item);
	if (!p_item) {
		return datatype::ANY;
	}
	switch (p_item->type) {
	case Item::Type::NUMBER:
	case Item::Type::RECEIVE_NUMBER:
		return datatype::NUMBER;
		break;
	case Item::Type::BOOLEAN:
	case Item::Type::RECEIVE_BOOLEAN:
		return datatype::_BOOLEAN;
		break;
	case Item::Type::DATE_TIME:
	case Item::Type::RECEIVE_DATE_TIME:
		return datatype::DATETIME;
		break;
	case Item::Type::STRING:
	case Item::Type::RECEIVE_STRING:
		return datatype::STRING;
		break;
	case Item::Type::BINARY:
	case Item::Type::RECEIVE_BINARY:
		return datatype::_BINARY;
		break;
	case Item::Type::LONG_STRING:
	case Item::Type::RECEIVE_LONG_STRING:
		return datatype::LONG_STRING;
		break;
		// TODO: add more types, especially datatype::HANDLE
	default:
		return datatype::ANY;
	}
}

void decompile_expression(struct DecompileInfo di) {
	if (di.expression == 0) {
		oputs("NULL");
		return;
	}

	if (!(di.expression->XOPType == 0x00 || di.expression->XOPType == 0xa9)
			&& (di.expression->XImmedData & 0x80)) {
		di.var_scope = (varscope)(di.expression->XImmedData & 0x1f);
	}

	if (DispatchFunction[di.expression->XOPType]) {
		DispatchFunction[di.expression->XOPType](di);
	}else{
		throw new std::exception();
	}
}


#define PRECEDENCE(p) bool print_brackets;\
		{\
	uint8_t _precedence = p;\
	print_brackets = (_precedence > di.outer_precedence);\
	di.outer_precedence = _precedence;\
		}


struct DecompileInfo adapt_dcinfo(struct DecompileInfo di, struct tagOPERATOR* expression, datatype expected_return_type) {
	di.expression = expression;
	di.expected_return_type = expected_return_type;
	return di;
}

struct tagOPERATOR* ParseGetNthOperand(struct CompileBlock* compile_block, struct tagOPERATOR* expression, uint8_t num) {
	if (expression->XOperandCount == 0) {
		return 0;
	}
	if (num == 0) {
		return (struct tagOPERATOR*)((char*)expression + sizeof(struct tagOPERATOR) + 2*(expression->XOperandCount-1));
	}
	uint16_t offset = *((uint16_t*)((char*)expression + sizeof(struct tagOPERATOR) + 2*(num-1)));
	if (offset == 0) {
		return 0;
	}
	return (struct tagOPERATOR*)((char*)compile_block + offset);
}

uint32_t print_var_name(uint16_t memory_address, varscope var_scope, uint32_t* memory_item, class COutline* outline) {
	if (var_scope == varscope::GLOBAL_SEGMENT
			&& memory_address < max_system_var
			&& system_vars[memory_address]) {
		oputs(system_vars[memory_address]);
		return 0;
	}
	uint32_t declared_at = outline->lookup_variable(memory_item[var_scope], var_scope, memory_address);
	if (var_scope == LIB_GLOBALS && !declared_at) {
		declared_at = outline->lookup_variable(CGlobalDecs::lib_globals, var_scope, memory_address);
	}
	const char16_t* var_name = outline->symbol_lookup(declared_at);
	if (var_name) {
		if (var_scope == varscope::CURRENT_OBJECT || var_scope == varscope::CURRENT_FORM) {
			 outline->lookup_variable(memory_item[var_scope], var_scope, memory_address, true);
		}
		print_utf16(var_name);
	}else{
		oprintf("sc%02x_var%04x",var_scope,memory_address);
	}
	return declared_at;
}



// fallback
void basic_operation(const char* name, struct DecompileInfo di) {
	oprintf("%s(",name);
	if (di.expression->XOperandCount > 0) {
		di.outer_precedence = PRECEDENCE_MAX;
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), datatype::ANY));
		for (uint8_t i=1; i<di.expression->XOperandCount; i++) {
			oputs(", ");
			decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, i), datatype::ANY));
		}
	}
	oputs(")");
	return;
}

void __not_implemented_yet(struct DecompileInfo di) {
	basic_operation(DispatchArray[di.expression->XOPType], di);
}

void PrintClassVar(struct DecompileInfo di) {
	uint32_t class_id = *((uint32_t*)((uint8_t*)di.compile_block + ParseGetNthOperand(di.compile_block, di.expression, 0)->XBuffer));
	uint32_t class_item = di.outline->get_class_item(class_id);
	const char16_t* class_name = di.outline->symbol_lookup(class_item);
	if (class_name) {
		print_utf16(class_name);
		oputs(".");
	}else{
		oprintf("class_0x%08x.",class_id);
	}
	uint32_t var_address = *((uint32_t*)((uint8_t*)di.compile_block + ParseGetNthOperand(di.compile_block, di.expression, 1)->XBuffer));
	const char16_t* var_name = di.outline->symbol_lookup(di.outline->lookup_variable(class_item, varscope::STATIC_CLASS_VAR, var_address));
	if (var_name) {
		print_utf16(var_name);
	}else{
		oprintf("0x%08x",var_address);
	}
}

void PrintVar(struct DecompileInfo di, datatype var_type, uint16_t remaining_operands) {
	if (di.expression->XOperandCount < remaining_operands+1) {
		//throw new std::exception();
		oputs("???");
		return;
	}
	if (di.expression->XOperandCount == 1+remaining_operands
			&& di.var_scope != varscope::STATIC_CLASS_VAR
			&& di.var_scope != varscope::DS_OF_OPERATOR
			&& di.var_scope != varscope::SCOPE_0d) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), var_type));
	}else if (di.expression->XOperandCount == 2+remaining_operands
			&& di.var_scope == varscope::STATIC_CLASS_VAR) {
		PrintClassVar(di);
	}else if (di.expression->XOperandCount == 2+remaining_operands
			&& di.var_scope == varscope::DS_OF_OPERATOR) {
		uint32_t resultinfo = 0x00;
		struct DecompileInfo di2 = adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), WINDOW_HANDLE);
		di2.result_info = &resultinfo;
		decompile_expression(di2);
		if (!resultinfo) {
			// ERROR
			oprintf("_[ERR:sc%02x]",di.var_scope);
			for (uint8_t i=1; i+remaining_operands<di.expression->XOperandCount;i++) {
				oputs("_");
				decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, i), ANY));
			}
		}else{
			oputs(".");
			uint32_t var_address = *((uint32_t*)((uint8_t*)di.compile_block + ParseGetNthOperand(di.compile_block, di.expression, 1)->XBuffer));
			if (di.result_info) {
				*di.result_info = var_address;
			}
			const char16_t* var_name = di.outline->symbol_lookup(di.outline->lookup_variable(resultinfo, varscope::CURRENT_FORM, var_address));
			if (var_name) {
				di.outline->lookup_variable(resultinfo, varscope::CURRENT_FORM, var_address, true);
				print_utf16(var_name);
			}else{
				oprintf("0x%08x",var_address);
			}
		}
	}else{
		// unsopported scope
		oprintf("sc%02x_",di.var_scope);
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), var_type));
		for (uint8_t i=1; i+remaining_operands<di.expression->XOperandCount;i++) {
			oputs("_");
			decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, i), ANY));
		}
	}
}

void PrintDlgItem(struct DecompileInfo di, uint16_t remaining_operands, uint16_t offset = 0) {
	if (di.expression->XOperandCount < remaining_operands+1) {
		//throw new std::exception();
		oputs("???");
		return;
	}
	uint32_t last_dlgitem = 0;
	if (di.expression->XOperandCount == offset+1+remaining_operands) {
		if (!CDlg::cur_dlg_item.empty()) {
				last_dlgitem = CDlg::cur_dlg_item.top();
			}
	}else if (di.expression->XOperandCount == offset+2+remaining_operands) {
		di.result_info = &last_dlgitem;
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, offset), WINDOW_HANDLE));
	}else{
		//throw std::exception();
		oputs("???");
		return;
	}

	struct DecompileInfo d = adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, di.expression->XOperandCount-remaining_operands-1), DLGITEM);
	uint32_t dlgitem = *(uint32_t*)(((uint8_t*)d.compile_block + d.expression->XBuffer));
	if (dlgitem == 0xffffffff) {
		return;
	}
	uint32_t item_ref = d.outline->get_dialog_dlgitem(last_dlgitem, dlgitem);
	const char16_t* symbol = d.outline->symbol_lookup(item_ref);
	if (di.expression->XOperandCount == offset+2+remaining_operands) {
		oputs(".");
	}
	if (symbol) {
		print_utf16(symbol);
	}else{
		oputs("dlgitem_");
		oprintf("%08x", dlgitem);
	}
}

void Const(struct DecompileInfo di) {
	if (di.expected_return_type == VARIABLE_ADDRESS || di.expected_return_type == VARIABLE_DATE
			|| di.expected_return_type == VARIABLE_HANDLE || di.expected_return_type == VARIABLE_NUMBER
			|| di.expected_return_type == VARIABLE_POINTER || di.expected_return_type == VARIABLE_STRING) {
		uint16_t memory_address = *(uint16_t*)((char*)di.compile_block + di.expression->XBuffer);

		if (di.var_scope == varscope::DYN_LIB) {
			uint16_t var_address = ((uint16_t*)((char*)di.compile_block + di.expression->XBuffer))[1];
			uint32_t item = di.outline->get_dynalib_var(memory_address, var_address);
			if (di.result_info) {
				*di.result_info = item;
			}
			if (item) {
				const char16_t* var_name = di.outline->symbol_lookup(item);
				if (var_name) {
					print_utf16(var_name);
					return;
				}
			}
			oprintf("sc10_%04x_%04x",memory_address,var_address);
		}else{
			uint32_t declared_at = print_var_name(memory_address, di.var_scope, di.memory_item, di.outline);
			if (di.result_info) {
				*di.result_info = declared_at;
			}
		}
	}else if (di.expected_return_type == NUMBER){
		print_number((struct SalNumber*)((uint8_t*)di.compile_block + di.expression->XBuffer));
	}else if (di.expected_return_type == DATETIME){
		uint8_t* number = (uint8_t*)di.compile_block + di.expression->XBuffer;
		if ((number[0] & 0xe0) == 0x00) {
			// has YYYY-MM-DD
			if (is_null((struct SalNumber*)number)) {
				oputs("DATETIME_Null");
			}else{
				print_date((struct SalNumber*)number);
			}
		}else{
			// is only daytime without date
			if (is_null((struct SalNumber*)number)) {
				oputs("DATETIME_Null");
			}else{
				print_time((struct SalNumber*)number);
			}
		}
	}else if (di.expected_return_type == _BOOLEAN){
		oputs(boolval((struct SalNumber*)((uint8_t*)di.compile_block + di.expression->XBuffer))?"TRUE":"FALSE");
	}else if (di.expected_return_type == DLGITEM){
		uint32_t dlgitem = *(uint32_t*)(((uint8_t*)di.compile_block + di.expression->XBuffer));
		oprintf("dlgitem_%08x", dlgitem);
	}else if (di.expected_return_type == STRING){
		oputs("[const string]");
	}else if (di.expected_return_type == _BINARY){
		oputs("[const binary]");
	}else if (di.expected_return_type == LONG_STRING){
		oputs("[const long string]");
	}else if (di.expected_return_type == FUNCTIONAL_CLASS_OBJECT){
		oputs("[const functional class object]");
	}else if (di.expected_return_type == FILE_HANDLE){
		oputs("[const functional file handle]");
	}else if (di.expected_return_type == _HANDLE || di.expected_return_type == UDV){
		uint32_t data = *(uint32_t*)(((uint8_t*)di.compile_block + di.expression->XBuffer));
		if (!data) {
			oprintf("OBJ_Null");
		}else{
			oprintf("[functional handle: 0x%08x]",data);
		}
	}else if (di.expected_return_type == SESSION_HANDLE){
		oputs("[const functional session handle]");
	}else if (di.expected_return_type == SQL_HANDLE){
		oputs("[const functional sql handle]");
	}else if (di.expected_return_type == WINDOW_HANDLE){
		oputs("[const functional window handle]");
	}else if (di.expected_return_type == ITEM_REFERENCE || di.expected_return_type == SCOPE_REFERENCE) {
		uint32_t item_id = *(uint32_t*)(((uint8_t*)di.compile_block + di.expression->XBuffer));
		if (!item_id && di.expected_return_type == ITEM_REFERENCE) {
			oputs("TEMPLATE_Null");
			if (di.result_info) {
				*di.result_info = 0;
			}
		}else{
			const char16_t* str = di.outline->symbol_lookup(item_id);
			if (str) {
				print_utf16(str);
				if (di.expected_return_type == SCOPE_REFERENCE) {
					oputs(".");
				}else if (di.expected_return_type == ITEM_REFERENCE && di.result_info) {
					*di.result_info = item_id;
				}
			}else if (!(item_id & 0xFFFF0000) && di.expected_return_type == SCOPE_REFERENCE) { // method of super-class
				// FIXME: reference is resolved to memory offset defined by 0x33-item-data-fields of parent classes (derived from).
				// TODO: if a class itself has size 0, but is derived from another class, which class of those is referenced here?
				if (is_verbose()) {
					oprintf("[superclass:0x%08x].",item_id);
				}
			}else{
				oprintf("[ref:0x%08x]",item_id);
				if (di.expected_return_type == SCOPE_REFERENCE) {
					oputs(".");
				}
			}
		}
	}else if (di.expected_return_type == _DWORD) {
		uint32_t value = *(uint32_t*)(((uint8_t*)di.compile_block + di.expression->XBuffer));
		oprintf("0x%08x",value);
	}else{
		oprintf("[var or const: 0x%08x @ sc0x%02x]",*(uint32_t*)(((uint8_t*)di.compile_block + di.expression->XBuffer)),di.var_scope);
	}
}

void ConstH(struct DecompileInfo di) {
	Const(di);
}

void CnvStaticString(struct DecompileInfo di) {
	if (di.expected_return_type != ANY
			&& di.expected_return_type != STRING
			&& di.expected_return_type != LONG_STRING
			&& di.expected_return_type != _BINARY) {
		//throw new std::exception();
	}
	struct tagOPERATOR* data = ParseGetNthOperand(di.compile_block, di.expression, 0);
	if (data->XOPType == 0x00) {
		// load string
		uint16_t string_id = *(uint16_t*)((char*)di.compile_block + data->XBuffer);
		const String* str = di.outline->string_lookup(string_id);
		if (str) {
			print_utf16_quoted(str->str, str->len);
		}
	}
}

struct FuncParams {
	uint8_t num;
	enum datatype* param;
};
struct Params {
	uint8_t* i;
	struct FuncParams* fp;
};

static void callback2(class COutline* outline, uint32_t item, void* param) {
	struct Params* par = (struct Params*)param;
	if (*par->i >= par->fp->num) {
		return;
	}
	par->fp->param[*par->i] = get_datatype_from_declaration(outline, item);
	(*par->i)++;
}

static void callback1(class COutline* outline, uint32_t item, void* param) {
	uint8_t i = 0;
	struct FuncParams* fp = (struct FuncParams*)param;
	struct Params par = {&i, fp};
	outline->find_children_of_type_and_run(callback2, &par, item, NULL, false);
}

static void callback4(class COutline* outline, uint32_t item, void* param) {
	uint32_t* return_type = *(uint32_t**)param;
	*return_type = item;
}

static void callback3(class COutline* outline, uint32_t item, void* param) {
	outline->find_children_of_type_and_run(callback4, param, item, NULL);
}

void IntFunction(struct DecompileInfo di) {
	struct tagOPERATOR* infun = ParseGetNthOperand(di.compile_block, di.expression, 0);

	uint32_t* return_type = di.result_info;

	struct FuncParams p;
	p.num = di.expression->XOperandCount / 2;
	if (p.num) {
		p.param = alloc<enum datatype*>(p.num * sizeof(enum datatype));
	}else{
		p.param = NULL;
	}

	uint32_t func_item = 0;
	if (!infun) {
		oputs("NULL(");
	}else if (infun->XOPType != 0x00 && infun->XOPType != 0xa9) {
		di.result_info = &func_item;
		decompile_expression(adapt_dcinfo(di, infun, datatype::INTFUNCLASS));
		oputs("(");
	}else{
		struct tagINTFUNHITEMS* intfun = (struct tagINTFUNHITEMS*)((char*)di.compile_block + infun->XBuffer);
		func_item = intfun->hItemDoActions;

		const char16_t* ret = di.outline->symbol_lookup(intfun->hItemDoActions);
		if (ret) {
			// FIXME: may refer to superclass-function, print its name to uniquely identify callee (note: class may be polymorphic!)
			// --> is used to correct the offset; -- otherwise, normal INTFUN-call is performed...
			if (is_verbose()) {
				oprintf("[FUN_%08x]",intfun->hItemDoActions);
			}
			print_utf16(ret);
		}else{
			oprintf("__FUN_NULL@0x%08x__",intfun->hItemDoActions);
		}

		oputs("(");
	}

	// get function signature
	if (func_item && p.param) {
		const uint16_t type[] = {0x89, 0}; // Parameters (intern)
		di.outline->find_children_of_type_and_run(callback1, &p, func_item, type);
	}
	if (func_item && return_type) {
		// write return type to return_type-Variable!!
		const uint16_t type[] = {0x8a, 0}; // Returns (intern function)
		di.outline->find_children_of_type_and_run(callback3, &return_type, func_item, type);
	}

	// print arguments
	di.outer_precedence = PRECEDENCE_MAX;
	for (uint8_t i=1; i<di.expression->XOperandCount; i+=2) {
		datatype expected_return_type = datatype::ANY;
		if (func_item && p.param && i/2 < p.num) {
			expected_return_type = p.param[i/2];
		}
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, i), expected_return_type));
		if (i+2<di.expression->XOperandCount) {
			oputs(", ");
		}
	}
	if (p.param) {
		free(p.param);
	}
	oputs(")");
}

void ExtFunction(struct DecompileInfo di) {
	// TODO: write declaration of return type to di.result_info as it is needed by DispatchArray.GetUDVHan
	struct tagOPERATOR* exfun = ParseGetNthOperand(di.compile_block, di.expression, 0);
	if (!exfun) {
		oputs("NULL(");
	}else if (exfun->XOPType != 0x00 && exfun->XOPType != 0xa9) {
		// TODO: handle this dynamic case!!
		oputs("DYNAMICALLY_GENERATED_EXTFUN_CALL<");
		decompile_expression(adapt_dcinfo(di, exfun, datatype::INTFUNCLASS));
		oputs(">");
	}else{
		struct tagEXFUNINFO* exfun_info = (struct tagEXFUNINFO*)((char*)di.compile_block + exfun->XBuffer);
		if (exfun_info->hItemLibrary == 0x00) {
			// embedded library
			// TODO: define expected parameter types in sal_functions.h and use them here
			if (exfun_info->AccessKey<1423) {
				oprintf("%s(",INT_LOCALS[exfun_info->AccessKey].name);
			}else{
				// invalid function
				oputs("undefined(");
			}
		}else{
			// TODO: get expected parameter types and return value!!
			const char16_t* ret = di.outline->symbol_lookup(exfun_info->hItemFun);
			if (ret) {
				print_utf16(ret, strlen_utf16(ret));
			}else{
				oprintf("__FUN_NULL@0x%08x__",exfun_info->hItemFun);
			}
			oputs("(");
		}
	}
	di.outer_precedence = PRECEDENCE_MAX;
	for (uint8_t i=1; i<di.expression->XOperandCount; i+=2) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, i), datatype::ANY));
		if (i+2<di.expression->XOperandCount) {
			oputs(", ");
		}
	}
	oputs(")");
}

void Add(struct DecompileInfo di) {
	if (di.expected_return_type != ANY
			&& di.expected_return_type != NUMBER && di.expected_return_type != _BOOLEAN) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 2) {
		throw new std::exception();
	}
	PRECEDENCE(PRECEDENCE_ADD);
	oputs(print_brackets?"(":"");
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), datatype::NUMBER));
	oputs(" + ");
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 1), datatype::NUMBER));
	oputs(print_brackets?")":"");
	return;
}

void AddDate(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != DATETIME) {
		//throw std::exception();
	}
	if (di.expression->XOperandCount != 2) {
		throw new std::exception();
	}
	PRECEDENCE(PRECEDENCE_ADD);
	oputs(print_brackets?"(":"");
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), datatype::DATETIME));
	oputs(" + ");
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 1), datatype::NUMBER));
	oputs(print_brackets?")":"");
	return;
}

void Substract(struct DecompileInfo di) {
	if (di.expected_return_type != ANY
			&& di.expected_return_type != NUMBER && di.expected_return_type != _BOOLEAN) {
		//throw std::exception();
	}
	if (di.expression->XOperandCount != 2) {
		throw new std::exception();
	}
	PRECEDENCE(PRECEDENCE_ADD);
	oputs(print_brackets?"(":"");
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), datatype::NUMBER));
	oputs(" - ");
	di.outer_precedence--; // for '-', the further arguments need brackets
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 1), datatype::NUMBER));
	oputs(print_brackets?")":"");
	return;
}

void SubstractDate(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != DATETIME) {
		//throw std::exception();
	}
	if (di.expression->XOperandCount != 2) {
		throw new std::exception();
	}
	PRECEDENCE(PRECEDENCE_ADD);
	oputs(print_brackets?"(":"");
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), datatype::DATETIME));
	oputs(" - ");
	di.outer_precedence--; // for '-', the further arguments need brackets
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 1), datatype::NUMBER));
	oputs(print_brackets?")":"");
	return;
}

void SubstractDateDate(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != NUMBER && di.expected_return_type != _BOOLEAN) {
		//throw std::exception();
	}
	if (di.expression->XOperandCount != 2) {
		throw new std::exception();
	}
	PRECEDENCE(PRECEDENCE_ADD);
	oputs(print_brackets?"(":"");
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), DATETIME));
	oputs(" - ");
	di.outer_precedence--; // for '-', the further arguments need brackets
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 1), DATETIME));
	oputs(print_brackets?")":"");
	return;
}

void Multiply(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != NUMBER && di.expected_return_type != _BOOLEAN) {
		//throw std::exception();
	}
	if (di.expression->XOperandCount != 2) {
		throw new std::exception();
	}
	PRECEDENCE(PRECEDENCE_MUL);
	oputs(print_brackets?"(":"");
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), NUMBER));
	oputs(" * ");
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 1), NUMBER));
	oputs(print_brackets?")":"");
	return;
}

void Divide(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != NUMBER && di.expected_return_type != _BOOLEAN) {
		//throw std::exception();
	}
	if (di.expression->XOperandCount != 2) {
		throw new std::exception();
	}
	PRECEDENCE(PRECEDENCE_MUL);
	oputs(print_brackets?"(":"");
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), NUMBER));
	oputs(" / ");
	di.outer_precedence--; // for '/', the further arguments need brackets
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 1), NUMBER));
	oputs(print_brackets?")":"");
	return;
}

void Negate(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != NUMBER && di.expected_return_type != _BOOLEAN) {
		//throw std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	PRECEDENCE(PRECEDENCE_NOT);
	oputs(print_brackets?"(":"");
	oputs("-");
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), NUMBER));
	oputs(print_brackets?")":"");
	return;
}

void Or(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _BOOLEAN && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount < 2) {
		throw new std::exception();
	}
	PRECEDENCE(PRECEDENCE_LOG_OR);
	oputs(print_brackets?"(":"");
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _BOOLEAN));
	for (uint8_t i=1; i<di.expression->XOperandCount; i++) {
		oputs(" OR ");
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, i), _BOOLEAN));
	}
	oputs(print_brackets?")":"");
	return;
}

void And(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _BOOLEAN && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount < 2) {
		throw new std::exception();
	}
	PRECEDENCE(PRECEDENCE_LOG_AND);
	oputs(print_brackets?"(":"");
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _BOOLEAN));
	for (uint8_t i=1; i<di.expression->XOperandCount; i++) {
		oputs(" AND ");
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, i), _BOOLEAN));
	}
	oputs(print_brackets?")":"");
	return;
}

void Not(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _BOOLEAN && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	PRECEDENCE(PRECEDENCE_NOT);
	oputs(print_brackets?"(":"");
	oputs("NOT ");
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _BOOLEAN));
	oputs(print_brackets?")":"");
	return;
}

void GenericCompare(struct DecompileInfo di, const char* comparator, uint8_t precedence, datatype types) {
	if (di.expected_return_type != ANY && di.expected_return_type != _BOOLEAN && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 2) {
		throw new std::exception();
	}
	PRECEDENCE(precedence);
	oputs(print_brackets?"(":"");
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), types));
	oprintf(" %s ",comparator);
	di.outer_precedence--;
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 1), types));
	oputs(print_brackets?")":"");
	return;
}

void CompareNumberLT(struct DecompileInfo di) {
	GenericCompare(di,"<",PRECEDENCE_REL_COMPARE,datatype::NUMBER);
}
void CompareNumberGT(struct DecompileInfo di) {
	GenericCompare(di,">",PRECEDENCE_REL_COMPARE,datatype::NUMBER);
}
void CompareNumberEQ(struct DecompileInfo di) {
	GenericCompare(di,"=",PRECEDENCE_EQ_NEQ,datatype::NUMBER);
}
void CompareNumberLE(struct DecompileInfo di) {
	GenericCompare(di,"<=",PRECEDENCE_REL_COMPARE,datatype::NUMBER);
}
void CompareNumberGE(struct DecompileInfo di) {
	GenericCompare(di,">=",PRECEDENCE_REL_COMPARE,datatype::NUMBER);
}
void CompareNumberNE(struct DecompileInfo di) {
	GenericCompare(di,"!=",PRECEDENCE_EQ_NEQ,datatype::NUMBER);
}

void CompareStringLT(struct DecompileInfo di) {
	GenericCompare(di,"<",PRECEDENCE_REL_COMPARE,datatype::STRING);
}
void CompareStringGT(struct DecompileInfo di) {
	GenericCompare(di,">",PRECEDENCE_REL_COMPARE,datatype::STRING);
}
void CompareStringEQ(struct DecompileInfo di) {
	GenericCompare(di,"=",PRECEDENCE_EQ_NEQ,datatype::STRING);
}
void CompareStringLE(struct DecompileInfo di) {
	GenericCompare(di,"<=",PRECEDENCE_REL_COMPARE,datatype::STRING);
}
void CompareStringGE(struct DecompileInfo di) {
	GenericCompare(di,">=",PRECEDENCE_REL_COMPARE,datatype::STRING);
}
void CompareStringNE(struct DecompileInfo di) {
	GenericCompare(di,"!=",PRECEDENCE_EQ_NEQ,datatype::STRING);
}

void CompareDateLT(struct DecompileInfo di) {
	GenericCompare(di,"<",PRECEDENCE_REL_COMPARE,datatype::DATETIME);
}
void CompareDateGT(struct DecompileInfo di) {
	GenericCompare(di,">",PRECEDENCE_REL_COMPARE,datatype::DATETIME);
}
void CompareDateEQ(struct DecompileInfo di) {
	GenericCompare(di,"=",PRECEDENCE_EQ_NEQ,datatype::DATETIME);
}
void CompareDateLE(struct DecompileInfo di) {
	GenericCompare(di,"<=",PRECEDENCE_REL_COMPARE,datatype::DATETIME);
}
void CompareDateGE(struct DecompileInfo di) {
	GenericCompare(di,">=",PRECEDENCE_REL_COMPARE,datatype::DATETIME);
}
void CompareDateNE(struct DecompileInfo di) {
	GenericCompare(di,"!=",PRECEDENCE_EQ_NEQ,datatype::DATETIME);
}

void CompareHandleLT(struct DecompileInfo di) {
	GenericCompare(di,"<",PRECEDENCE_REL_COMPARE,datatype::ANY);
}
void CompareHandleGT(struct DecompileInfo di) {
	GenericCompare(di,">",PRECEDENCE_REL_COMPARE,datatype::ANY);
}
void CompareHandleEQ(struct DecompileInfo di) {
	GenericCompare(di,"=",PRECEDENCE_EQ_NEQ,datatype::ANY);
}
void CompareHandleLE(struct DecompileInfo di) {
	GenericCompare(di,"<=",PRECEDENCE_REL_COMPARE,datatype::ANY);
}
void CompareHandleGE(struct DecompileInfo di) {
	GenericCompare(di,">=",PRECEDENCE_REL_COMPARE,datatype::ANY);
}
void CompareHandleNE(struct DecompileInfo di) {
	GenericCompare(di,"!=",PRECEDENCE_EQ_NEQ,datatype::ANY);
}

void CompareBinaryLT(struct DecompileInfo di) {
	GenericCompare(di,"<",PRECEDENCE_REL_COMPARE,datatype::_BINARY);
}
void CompareBinaryGT(struct DecompileInfo di) {
	GenericCompare(di,">",PRECEDENCE_REL_COMPARE,datatype::_BINARY);
}
void CompareBinaryEQ(struct DecompileInfo di) {
	GenericCompare(di,"=",PRECEDENCE_EQ_NEQ,datatype::_BINARY);
}
void CompareBinaryLE(struct DecompileInfo di) {
	GenericCompare(di,"<=",PRECEDENCE_REL_COMPARE,datatype::_BINARY);
}
void CompareBinaryGE(struct DecompileInfo di) {
	GenericCompare(di,">=",PRECEDENCE_REL_COMPARE,datatype::_BINARY);
}
void CompareBinaryNE(struct DecompileInfo di) {
	GenericCompare(di,"!=",PRECEDENCE_EQ_NEQ,datatype::_BINARY);
}

void Concat(struct DecompileInfo di) {
	if (di.expected_return_type != ANY
			&& di.expected_return_type != STRING
			&& di.expected_return_type != LONG_STRING
			&& di.expected_return_type != _BINARY) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount < 2) {
		throw new std::exception();
	}
	PRECEDENCE(PRECEDENCE_CONCAT);
	oputs(print_brackets?"(":"");
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), STRING));
	for (uint8_t i=1; i<di.expression->XOperandCount; i++) {
		oputs(" || ");
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, i), STRING));
	}
	oputs(print_brackets?")":"");
	return;
}

void LAnd(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != NUMBER && di.expected_return_type != _BOOLEAN) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount < 2) {
		throw new std::exception();
	}
	PRECEDENCE(PRECEDENCE_BIT_AND);
	oputs(print_brackets?"(":"");
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), NUMBER));
	for (uint8_t i=1; i<di.expression->XOperandCount; i++) {
		oputs(" & ");
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, i), NUMBER));
	}
	oputs(print_brackets?")":"");
	return;
}

void LOr(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != NUMBER && di.expected_return_type != _BOOLEAN) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount < 2) {
		throw new std::exception();
	}
	PRECEDENCE(PRECEDENCE_BIT_OR);
	oputs(print_brackets?"(":"");
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), NUMBER));
	for (uint8_t i=1; i<di.expression->XOperandCount; i++) {
		oputs(" | ");
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, i), NUMBER));
	}
	oputs(print_brackets?")":"");
	return;
}

void GetVarDate(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != DATETIME) {
		//throw new std::exception();
	}
	PrintVar(di,VARIABLE_DATE,0);
}

void GetVarHandle(struct DecompileInfo di) {
	// TODO: what does it mean if expected_type is VARIABLE_HANDLE, i.e. if this function is nested

	//di.expression->XOperandCount
	uint16_t expected_params = di.expression->XOperandCount;
	switch(di.var_scope) {
	case varscope::CURRENT_OBJECT:
	case varscope::CURRENT_FORM:
	case varscope::DYN_LIB:
	case varscope::GLOBAL_SEGMENT:
	case varscope::INTERNAL_FUNCTION_PARAM:
	case varscope::INTERNAL_FUNCTION_PARAM_PRE:
	case varscope::INTERNAL_FUNCTION_VAR:
	case varscope::LIB_GLOBALS:
	case varscope::CURRENT_FORM_CLASS:
		expected_params = 1;
		break;
	case varscope::STATIC_CLASS_VAR:
	case varscope::DS_OF_OPERATOR:
	case varscope::SCOPE_0d:
		expected_params = 2;
		break;
	default:
		break;
	}
	if (di.expression->XOperandCount > expected_params) {
		// FIXME: why does this occur??
		// seems to be a problem especially if this function is called inside of
		if (is_verbose()) {
			oputs("[WARNING: GetVarHandle: wrong number of parameters!]");
		}
		PrintVar(di,VARIABLE_HANDLE,di.expression->XOperandCount-expected_params);
	}else{
		PrintVar(di,VARIABLE_HANDLE,0);
	}
}

void GetVarNumber(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != NUMBER && di.expected_return_type != _BOOLEAN) {
		//throw new std::exception();
	}
	PrintVar(di,VARIABLE_NUMBER,0);
}

void GetVarString(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != STRING && di.expected_return_type != LONG_STRING && di.expected_return_type != _BINARY) {
		//throw new std::exception();
	}
	PrintVar(di,VARIABLE_STRING,0);
}

void GetVarPointer(struct DecompileInfo di) {
	/*
	if (di.expected_return_type != ANY && di.expected_return_type != ???) {
		throw new std::exception();
	}
	 */
	PrintVar(di,VARIABLE_POINTER,0);
}

void GetVarAddress(struct DecompileInfo di) {
	/*
	if (di.expected_return_type != ANY && di.expected_return_type != ???) {
		throw new std::exception();
	}
	 */
	PrintVar(di,VARIABLE_ADDRESS,0);
}

void PutVarDate(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != DATETIME) {
		//throw new std::exception();
	}
	PRECEDENCE(PRECEDENCE_ASSIGN);
	oputs(print_brackets?"(":"");
	PrintVar(di,VARIABLE_DATE,1);
	oputs(" = ");
	di.outer_precedence--; // for '=', the further arguments need brackets
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, di.expression->XOperandCount-1), DATETIME));
	oputs(print_brackets?")":"");
	return;
}

void PutVarHandle(struct DecompileInfo di) {
	// what does it mean if expected_type is VARIABLE_HANDLE, i.e. if this function is nested
	if (di.expected_return_type != ANY && di.expected_return_type != SQL_HANDLE && di.expected_return_type != FILE_HANDLE && di.expected_return_type != WINDOW_HANDLE && di.expected_return_type != SESSION_HANDLE && di.expected_return_type != FUNCTIONAL_CLASS_OBJECT && di.expected_return_type != VARIABLE_HANDLE) {
		//throw new std::exception();
	}
	PRECEDENCE(PRECEDENCE_ASSIGN);
	oputs(print_brackets?"(":"");
	PrintVar(di,VARIABLE_HANDLE,1);
	oputs(" = ");
	di.outer_precedence--; // for '=', the further arguments need brackets
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, di.expression->XOperandCount-1), ANY));
	oputs(print_brackets?")":"");
	return;
}

void PutVarNumber(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != NUMBER && di.expected_return_type != _BOOLEAN) {
		//throw new std::exception();
	}
	PRECEDENCE(PRECEDENCE_ASSIGN);
	oputs(print_brackets?"(":"");
	PrintVar(di,VARIABLE_NUMBER,1);
	oputs(" = ");
	di.outer_precedence--; // for '=', the further arguments need brackets
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, di.expression->XOperandCount-1), NUMBER));
	oputs(print_brackets?")":"");
	return;
}

void PutVarString(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != STRING && di.expected_return_type != _BINARY) {
		//throw new std::exception();
	}
	PRECEDENCE(PRECEDENCE_ASSIGN);
	oputs(print_brackets?"(":"");
	PrintVar(di,di.expected_return_type==_BINARY?VARIABLE_BINARY:VARIABLE_STRING,1);
	oputs(" = ");
	di.outer_precedence--; // for '=', the further arguments need brackets
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, di.expression->XOperandCount-1), di.expected_return_type==_BINARY?_BINARY:STRING));
	oputs(print_brackets?")":"");
	return;
}

void GetUDVHan(struct DecompileInfo di) {
	if (di.expression->XOperandCount == 2) {
		//oputs("GetUDVHan(");
		// TODO: we need the concrete type/class-definition of the object reference returned by this call!! otherwise we couldn't resolve memory-address to identifier
		uint32_t var_decl = 0;
		di.result_info = &var_decl;
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), ANY)); // TODO: Handle type??
		uint32_t class_def = 0;
		struct ItemBody* item_body = CItem::get_itembody(di.outline, var_decl, 0x14);
		if (item_body) {
			if (item_body->data[0] == 0x05) {
				class_def = (*(uint32_t*)&item_body->data[4]);
			}
		}
		oputs(".");
		struct tagOPERATOR* op = ParseGetNthOperand(di.compile_block, di.expression, di.expression->XOperandCount-1);
		uint32_t offset = *(uint32_t*)(((uint8_t*)di.compile_block + op->XBuffer));
		uint32_t vardef = di.outline->lookup_variable(class_def, varscope::CURRENT_OBJECT, offset, false);
		const char16_t* varname = di.outline->symbol_lookup(vardef);

		if (varname) {
			print_utf16(varname);
		}else{
			oprintf("[GetUDVHan]offset0x%08x",offset);
		}
		//oputs(")");
		return;
	}
	basic_operation("GetUDVHan",di);
	return;
}

void New(struct DecompileInfo di) {
	if (di.expression->XOperandCount == 1) {
		struct tagOPERATOR* op = ParseGetNthOperand(di.compile_block, di.expression, 0);
		uint32_t class_type = *(uint32_t*)(((uint8_t*)di.compile_block + op->XBuffer));
		const char16_t* var_name = di.outline->symbol_lookup(class_type);
		oputs("new ");
		if (var_name) {
			print_utf16(var_name);
		}else{
			oprintf("0x%08x",class_type);
		}
		return;
	}
	basic_operation("New",di);
	return;
}

void IntConstructor(struct DecompileInfo di) {
	if (di.expression->XOperandCount >= 2) {
		// New statement
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), ANY));

		// reference to Constructor
		struct tagOPERATOR* infun = ParseGetNthOperand(di.compile_block, di.expression, 1);
		uint32_t func_item = *(uint32_t*)(((uint8_t*)di.compile_block + infun->XBuffer));

		struct FuncParams p;
		p.num = di.expression->XOperandCount - 2;
		if (p.num) {
			p.param = alloc<enum datatype*>(p.num * sizeof(enum datatype));
		}else{
			p.param = NULL;
		}

		// get constructor's function signature
		if (func_item && p.param) {
			const uint16_t type[] = {0x89, 0}; // Parameters (intern)
			di.outline->find_children_of_type_and_run(callback1, &p, func_item, type);
		}

		// print arguments
		oputs("(");
		di.outer_precedence = PRECEDENCE_MAX;
		for (uint8_t i=2; i<di.expression->XOperandCount; i++) {
			datatype expected_return_type = datatype::ANY;
			if (func_item && p.param && i-2 < p.num) {
				expected_return_type = p.param[i-2];
			}
			decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, i), expected_return_type));
			if (i+1<di.expression->XOperandCount) {
				oputs(", ");
			}
		}
		if (p.param) {
			free(p.param);
		}

		oputs(")");
		return;
	}
	basic_operation("IntConstructor",di);
	return;
}


void PutUDVHan(struct DecompileInfo di) {
	/*
	if (di.expected_return_type != ANY && di.expected_return_type != UDV && di.expected_return_type != HANDLE) {
		throw new std::exception();
	}
	*/
	PRECEDENCE(PRECEDENCE_ASSIGN);
	oputs(print_brackets?"(":"");
	PrintVar(di,VARIABLE_HANDLE,1);
	oputs(" = ");
	di.outer_precedence--; // for '=', the further arguments need brackets
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, di.expression->XOperandCount-1), UDV));
	oputs(print_brackets?")":"");
	return;
}

void AdjUDVHan(struct DecompileInfo di) {
	if (di.expression->XOperandCount == 2) {
		uint32_t var_decl = 0;
		di.result_info = &var_decl;
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), UDV));
		uint32_t var_type = CItem::get_funcvar_typedef(di.outline, var_decl);
		oputs(".");
		struct tagOPERATOR* op = ParseGetNthOperand(di.compile_block, di.expression, 1);
		uint32_t offset = *(uint32_t*)(((uint8_t*)di.compile_block + op->XBuffer));
		uint32_t var_item = di.outline->lookup_variable(var_type, varscope::CURRENT_OBJECT, offset, 0);
		const char16_t* var_name = di.outline->symbol_lookup(var_item);
		if (var_name) {
			print_utf16(var_name);
		}else{
			oprintf("0x%08x",offset);
		}
		return;
	}
	basic_operation("AdjUDVHan",di);
}

void MakeUDVRef(struct DecompileInfo di) {
	if (di.expression->XOperandCount == 2 || di.expression->XOperandCount == 3 || di.expression->XOperandCount == 4) {
		PrintVar(di,VARIABLE_HANDLE,1);
		if (di.result_info) {
			struct tagOPERATOR* op = ParseGetNthOperand(di.compile_block, di.expression, di.expression->XOperandCount-1);
			uint32_t offset = *(uint32_t*)(((uint8_t*)di.compile_block + op->XBuffer));
			if (offset) {
				*di.result_info = offset;
			}
		}
		return;
	}
	if (di.expression->XOperandCount == 6 || di.expression->XOperandCount == 7 || di.expression->XOperandCount == 8) {
		PrintVar(di,VARIABLE_HANDLE,5);
		// NULL, NULL. NULL, NULL parameters in between?? --> omit
		if (di.result_info) {
			struct tagOPERATOR* op = ParseGetNthOperand(di.compile_block, di.expression, di.expression->XOperandCount-1);
			uint32_t offset = *(uint32_t*)(((uint8_t*)di.compile_block + op->XBuffer));
			if (offset) {
				*di.result_info = offset;
			}
		}
		return;
	}
	basic_operation("MakeUDVRef",di);
}

void GetVarUDVRef(struct DecompileInfo di) {
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), VARIABLE_HANDLE));
		return;
	}
	basic_operation("GetVarUDVRef",di);
	return;
}

void CnvUdvRefUDVREF(struct DecompileInfo di) {
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _HANDLE));
		return;
	}
	basic_operation("CnvUdvRefUDVREF",di);
	return;
}

void MakeUDVRf(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != UDV && di.expected_return_type != _HANDLE) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 2) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _HANDLE));
		if (di.result_info) {
			struct tagOPERATOR* op = ParseGetNthOperand(di.compile_block, di.expression, 1);
			uint32_t offset = *(uint32_t*)(((uint8_t*)di.compile_block + op->XBuffer));
			if (offset) {
				*di.result_info = offset;
			}
		}
		return;
	}
	if (di.expression->XOperandCount == 3) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _HANDLE));
		if (is_verbose()) {
			oputs(".[[");
			decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), ANY));
			oputs(".");
			decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), ANY));
			oputs("]]");
		}
		return;
	}
	basic_operation("MakeUDVRf",di);
	return;
}

void MakeUDV(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != UDV && di.expected_return_type != _HANDLE) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 2) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _HANDLE));
		if (di.result_info) {
			struct tagOPERATOR* op = ParseGetNthOperand(di.compile_block, di.expression, 1);
			uint32_t offset = *(uint32_t*)(((uint8_t*)di.compile_block + op->XBuffer));
			if (offset) {
				*di.result_info = offset;
			}
		}
		return;
	}
	basic_operation("MakeUDV",di);
	return;
}

void CnvUDVToHandle(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != UDV && di.expected_return_type != _HANDLE) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), UDV));
		return;
	}
	if (di.expression->XOperandCount == 2) {
		// second parameter is data type
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), UDV));
		return;
	}
	basic_operation("CnvUDVToHandle",di);
	return;
}

void PutReturnUDV(struct DecompileInfo di) {
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _HANDLE));
		return;
	}
	basic_operation("PutReturnUDV",di);
	return;
}

void IntFunSetupClassObject(struct DecompileInfo di) {
	if (di.expected_return_type != INTFUNCLASS) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 3) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 2), SCOPE_REFERENCE)); // TODO: Handle type??
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), ITEM_REFERENCE));
		return;
	}else if (di.expression->XOperandCount == 2) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 1), SCOPE_REFERENCE)); // TODO: Handle type??
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), ITEM_REFERENCE));
		return;
	}
	//throw new std::exception();
	//oputs("[[IntFunSetupClassObject doesn't have expected number of arguments...]]");
	basic_operation("IntFunSetupClassObject",di);
	return;
}

void IntFunSetupClassIndirect(struct DecompileInfo di) {
	if (di.expected_return_type != INTFUNCLASS) {
		//throw new std::exception();
	}

	if (di.expression->XOperandCount == 5) {
		PrintDlgItem(di, 2, 1);
		oputs(".");
		if (is_verbose()) {
			oputs("[[");
			decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 3), ANY));
			oputs("]].");
		}
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 4), SCOPE_REFERENCE));
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), ITEM_REFERENCE));
		return;
	}
	basic_operation("IntFunSetupClassIndirect",di);
	return;
}

void IntFunSetupClassArray(struct DecompileInfo di) {
	if (di.expected_return_type != INTFUNCLASS) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 4) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 1), ANY));
		oputs(".");
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), ITEM_REFERENCE));
		return;
	}
	basic_operation("IntFunSetupClassArray",di);
	return;
}

void IntFunSetupUDVRef(struct DecompileInfo di) {
	if (di.expected_return_type != INTFUNCLASS) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 3) {
		// TODO: unknown role of thrid parameter -- it is ignored for now
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 1), UDV));
		oputs(".");
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), ITEM_REFERENCE));
		return;
	}
	basic_operation("IntFunSetupUDVRef",di);
	return;
}

void GethItemhWnd(struct DecompileInfo di) {
	if (di.expected_return_type != VARIABLE_HANDLE && di.expected_return_type != WINDOW_HANDLE && di.expected_return_type != ANY) {
		basic_operation("GethItemhWnd",di);
		// throw new std::exception(); // TODO: why is VARIABLE_NUMBER an expected return type?
		return;
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), ITEM_REFERENCE));
		return;
	}
	basic_operation("GethItemhWnd",di);
	return;
}

void CnvHItemTEMPLATE(struct DecompileInfo di) {
	if (di.expected_return_type != TEMPLATE && di.expected_return_type != ANY) {
		basic_operation("CnvHItemTEMPLATE",di);
		// throw new std::exception(); // TODO: why is VARIABLE_NUMBER an expected return type?
		return;
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), ITEM_REFERENCE));
		return;
	}
	basic_operation("CnvHItemTEMPLATE",di);
	return;
}

void GetParenthWndByhItem(struct DecompileInfo di) {
	GethItemhWnd(di);
	return;
}

void GethWndMDI(struct DecompileInfo di) {
	uint32_t item = di.memory_item[varscope::CURRENT_FORM]; // this is dirty, but should work
	const char16_t* name = di.outline->symbol_lookup(item);
	if (name) {
		print_utf16(name);
	}else{
		oprintf("0x%08x",item);
	}
	if (di.result_info) {
		*di.result_info = item;
	}
	return;
}

void GethWndForm(struct DecompileInfo di) {
	// TODO: if called from PrintDlgItem,
	// the current item shouldn't be printed
	// - and PrintDlgItem shouldn't print the scope seperator "."
	if (di.expected_return_type != WINDOW_HANDLE) {
		// throw exception?
	}
	uint32_t item = 0;
	if (!CDlg::cur_dlg_item.empty()) {
		item = CDlg::cur_dlg_item.top();
	}
	const char16_t* name = di.outline->symbol_lookup(item);
	if (name) {
		print_utf16(name);
	}else{
		oprintf("0x%08x",item);
	}
	if (di.result_info) {
		*di.result_info = item;
	}
	return;
}

void IntFunSetupIndirect(struct DecompileInfo di) {
	if (di.expected_return_type != INTFUNCLASS) { /// expected return type by Function Return Value!!
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 2) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 1), WINDOW_HANDLE));
		oputs(".");
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), ITEM_REFERENCE));
		return;
	}
	basic_operation("IntFunSetupIndirect",di);
	return;
}

void IntFunSetupLate(struct DecompileInfo di) {
	if (di.expected_return_type != INTFUNCLASS) { /// expected return type by Function Return Value!!
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		oputs("..");
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), ITEM_REFERENCE));
		return;
	}
	if (di.expression->XOperandCount == 3) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 1), ANY));
		oputs(".");
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 2), ITEM_REFERENCE));
		oputs("..");
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), ITEM_REFERENCE));
		return;
	}
	basic_operation("IntFunSetupLate",di);
	return;
}

void CnvHItemTaggedTEMPTAGGED(struct DecompileInfo di) {
	/*
	if (di.expected_return_type != TEMPTAGGED) { /// expected return type by Function Return Value!!
		throw new std::exception();
	}
	 */
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), ITEM_REFERENCE));
		return;
	}
	basic_operation("CnvHItemTaggedTEMPTAGGED",di);
	return;
}

void CnvPointerLPSTR(struct DecompileInfo di) {
	/*
	if (di.expected_return_type != _LPVOID && di.expected_return_type != ANY) { /// or other type???
		throw new std::exception();
	}
	 */
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _LPSTR));
		return;
	}
	basic_operation("CnvPointerLPSTR",di);
	return;
}

void CheckIndexList(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	di.outer_precedence = PRECEDENCE_MAX;
	for (uint8_t i=0;i<di.expression->XOperandCount;i++) {
		if (i) {
			oputs(",");
		}
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, i), NUMBER));
	}
	return;
}

void GetArrayString(struct DecompileInfo di) {
	if (di.expected_return_type != ANY
			&& di.expected_return_type != STRING
			&& di.expected_return_type != LONG_STRING
			&& di.expected_return_type != _BINARY) {
		//throw new std::exception();
	}
	PrintVar(di,VARIABLE_HANDLE,1);
	oputs("[");
	di.outer_precedence = PRECEDENCE_MAX;
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, di.expression->XOperandCount-1), NUMBER));
	oputs("]");
}

void GetArrayNumber(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != NUMBER && di.expected_return_type != _BOOLEAN) {
		//throw new std::exception();
	}
	PrintVar(di,VARIABLE_HANDLE,1);
	oputs("[");
	di.outer_precedence = PRECEDENCE_MAX;
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, di.expression->XOperandCount-1), NUMBER));
	oputs("]");
}

void GetArrayDate(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != DATETIME) {
		//throw new std::exception();
	}
	PrintVar(di,VARIABLE_HANDLE,1);
	oputs("[");
	di.outer_precedence = PRECEDENCE_MAX;
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, di.expression->XOperandCount-1), NUMBER));
	oputs("]");
}

void GetArrayHandle(struct DecompileInfo di) {
	PrintVar(di,VARIABLE_HANDLE,1);
	oputs("[");
	di.outer_precedence = PRECEDENCE_MAX;
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, di.expression->XOperandCount-1), NUMBER));
	oputs("]");
}

void PutArrayString(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != STRING && di.expected_return_type != _BINARY) {
		//throw new std::exception();
	}
	PRECEDENCE(PRECEDENCE_ASSIGN);
	oputs(print_brackets?"(":"");
	PrintVar(di,VARIABLE_HANDLE,2);
	oputs("[");
	di.outer_precedence = PRECEDENCE_MAX;
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, di.expression->XOperandCount-2), NUMBER));
	oputs("] = ");
	di.outer_precedence = PRECEDENCE_ASSIGN - 1;
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, di.expression->XOperandCount-1), di.expected_return_type==_BINARY?_BINARY:STRING));
	oputs(print_brackets?")":"");
}

void PutArrayNumber(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != NUMBER && di.expected_return_type != _BOOLEAN) {
		//throw new std::exception();
	}
	PRECEDENCE(PRECEDENCE_ASSIGN);
	oputs(print_brackets?"(":"");
	PrintVar(di,VARIABLE_HANDLE,2);
	oputs("[");
	di.outer_precedence = PRECEDENCE_MAX;
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, di.expression->XOperandCount-2), NUMBER));
	oputs("] = ");
	di.outer_precedence = PRECEDENCE_ASSIGN - 1;
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, di.expression->XOperandCount-1), NUMBER));
	oputs(print_brackets?")":"");
}

void CastUdv(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != UDV && di.expected_return_type != _HANDLE) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 2) {
		// second parameter is data type
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), UDV));
		return;
	}
	basic_operation("CastUdv",di);
	return;
}

void PutArrayUDV(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _HANDLE && di.expected_return_type != UDV) {
		//throw new std::exception();
	}
	PRECEDENCE(PRECEDENCE_ASSIGN);
	oputs(print_brackets?"(":"");
	PrintVar(di,VARIABLE_HANDLE,2);
	oputs("[");
	di.outer_precedence = PRECEDENCE_MAX;
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, di.expression->XOperandCount-2), NUMBER));
	oputs("] = ");
	di.outer_precedence = PRECEDENCE_ASSIGN - 1;
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, di.expression->XOperandCount-1), _HANDLE));
	oputs(print_brackets?")":"");
}

void GetArayUDV(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _HANDLE && di.expected_return_type != UDV) {
		//throw new std::exception();
	}
	PrintVar(di,VARIABLE_HANDLE,1);
	oputs("[");
	di.outer_precedence = PRECEDENCE_MAX;
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, di.expression->XOperandCount-1), NUMBER));
	oputs("]");
}

void GetFieldNumber(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != NUMBER && di.expected_return_type != _BOOLEAN) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount < 1) {
		// FIXME: why does this occur?
		basic_operation("GetFieldNumber",di);
		return;
	}
	PrintDlgItem(di, 0);
}

void GetFieldString(struct DecompileInfo di) {
	if (di.expected_return_type != ANY
			&& di.expected_return_type != STRING
			&& di.expected_return_type != LONG_STRING
			&& di.expected_return_type != _BINARY) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount < 1) {
		// FIXME: why does this occur?
		basic_operation("GetFieldString",di);
		return;
	}
	PrintDlgItem(di, 0);
}

void GetFieldDate(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != DATETIME) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount < 1) {
		// FIXME: why does this occur?
		basic_operation("GetFieldDate",di);
		return;
	}
	PrintDlgItem(di, 0);
}

void GetFieldHandle(struct DecompileInfo di) {
	/*
	if (di.expected_return_type != ANY && di.expected_return_type != HANDLE) {
		throw new std::exception();
	}
	*/
	if (di.expression->XOperandCount < 1) {
		// FIXME: why does this occur?
		basic_operation("GetFieldHandle",di);
		return;
	}
	PrintDlgItem(di, 0);
}

void PutFieldNumber(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != NUMBER && di.expected_return_type != _BOOLEAN) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 0) {
		throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		// FIXME: why does this occur?
		oputs("PutFieldNumber(");
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, di.expression->XOperandCount-1), NUMBER));
		oputs(")");
		return;
	}
	PRECEDENCE(PRECEDENCE_ASSIGN);
	oputs(print_brackets?"(":"");
	di.outer_precedence = PRECEDENCE_MAX;
	PrintDlgItem(di, 1);
	oputs(" = ");
	di.outer_precedence = PRECEDENCE_ASSIGN - 1;
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, di.expression->XOperandCount-1), NUMBER));
	oputs(print_brackets?")":"");
}

void PutFieldString(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != STRING) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 0) {
		throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		// FIXME: why does this occur?
		oputs("PutFieldString(");
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, di.expression->XOperandCount-1), STRING));
		oputs(")");
		return;
	}
	PRECEDENCE(PRECEDENCE_ASSIGN);
	oputs(print_brackets?"(":"");
	di.outer_precedence = PRECEDENCE_MAX;
	PrintDlgItem(di, 1);
	oputs(" = ");
	di.outer_precedence = PRECEDENCE_ASSIGN - 1;
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, di.expression->XOperandCount-1), STRING));
	oputs(print_brackets?")":"");
}

void PutFieldDate(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != DATETIME) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 0) {
		throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		// FIXME: why does this occur?
		oputs("PutFieldDate(");
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, di.expression->XOperandCount-1), DATETIME));
		oputs(")");
		return;
	}
	PRECEDENCE(PRECEDENCE_ASSIGN);
	oputs(print_brackets?"(":"");
	di.outer_precedence = PRECEDENCE_MAX;
	PrintDlgItem(di, 1);
	oputs(" = ");
	di.outer_precedence = PRECEDENCE_ASSIGN - 1;
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, di.expression->XOperandCount-1), DATETIME));
	oputs(print_brackets?")":"");
}

void NoOp(struct DecompileInfo di) {
}

void GetCheck(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _BOOLEAN && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount < 1) {
		// FIXME: why does this occur?
		basic_operation("GetCheck",di);
		return;
	}
	PrintDlgItem(di, 0);
}

void PutCheck(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _BOOLEAN && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 0) {
		throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		// FIXME: why does this occur?
		oputs("PutCheck(");
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, di.expression->XOperandCount-1), _BOOLEAN));
		oputs(")");
		return;
	}
	PRECEDENCE(PRECEDENCE_ASSIGN);
	oputs(print_brackets?"(":"");
	di.outer_precedence = PRECEDENCE_MAX;
	PrintDlgItem(di, 1);
	oputs(" = ");
	di.outer_precedence = PRECEDENCE_ASSIGN - 1;
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, di.expression->XOperandCount-1), _BOOLEAN));
	oputs(print_brackets?")":"");
}

void GetScroll(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _BOOLEAN && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount < 1) {
		// FIXME: why does this occur?
		basic_operation("GetCheck",di);
		return;
	}
	PrintDlgItem(di, 0);
}

void PutScroll(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _BOOLEAN && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 0) {
		throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		// FIXME: why does this occur?
		oputs("PutScroll(");
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, di.expression->XOperandCount-1), NUMBER));
		oputs(")");
		return;
	}
	PRECEDENCE(PRECEDENCE_ASSIGN);
	oputs(print_brackets?"(":"");
	di.outer_precedence = PRECEDENCE_MAX;
	PrintDlgItem(di, 1);
	oputs(" = ");
	di.outer_precedence = PRECEDENCE_ASSIGN - 1;
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, di.expression->XOperandCount-1), NUMBER));
	oputs(print_brackets?")":"");
}

void PutArrayDate(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != DATETIME) {
		//throw new std::exception();
	}
	PRECEDENCE(PRECEDENCE_ASSIGN);
	oputs(print_brackets?"(":"");
	PrintVar(di,VARIABLE_HANDLE,2);
	oputs("[");
	di.outer_precedence = PRECEDENCE_MAX;
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, di.expression->XOperandCount-2), NUMBER));
	oputs("] = ");
	di.outer_precedence = PRECEDENCE_ASSIGN - 1;
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, di.expression->XOperandCount-1), DATETIME));
	oputs(print_brackets?")":"");
}

void PutArrayHandle(struct DecompileInfo di) {
	// what does it mean if expected_type is VARIABLE_HANDLE, i.e. if this function is nested
	if (di.expected_return_type != ANY && di.expected_return_type != SQL_HANDLE && di.expected_return_type != FILE_HANDLE && di.expected_return_type != WINDOW_HANDLE && di.expected_return_type != SESSION_HANDLE && di.expected_return_type != FUNCTIONAL_CLASS_OBJECT && di.expected_return_type != VARIABLE_HANDLE) {
		//throw new std::exception();
	}
	PRECEDENCE(PRECEDENCE_ASSIGN);
	oputs(print_brackets?"(":"");
	PrintVar(di,VARIABLE_HANDLE,2);
	oputs("[");
	di.outer_precedence = PRECEDENCE_MAX;
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, di.expression->XOperandCount-2), NUMBER));
	oputs("] = ");
	di.outer_precedence = PRECEDENCE_ASSIGN - 1;
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, di.expression->XOperandCount-1), ANY));
	oputs(print_brackets?")":"");
}

void CnvStringLPWSTR(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _LPWSTR) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), STRING));
}

void CnvRecStringLPWSTR(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _LPWSTR) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), RECEIVE_STRING));
}

void PutReturnNumber(struct DecompileInfo di) {
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), NUMBER));
}

void PutReturnDate(struct DecompileInfo di) {
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), DATETIME));
}

void PutReturnHandle(struct DecompileInfo di) {
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), ANY));
}

void PutReturnString(struct DecompileInfo di) {
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	try {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), STRING));
	}catch(...) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _BINARY));
	}
}

void CnvBooleanBOOL(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _BOOL) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _BOOLEAN));
}

void CnvDateTimeDATETIME(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != DATE_TIME) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), DATETIME));
}


void CnvNumberBYTE(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _BYTE) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), NUMBER));
}

void CnvNumberCHAR(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _CHAR) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), NUMBER));
}

void CnvNumberDOUBLE(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _DOUBLE) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), NUMBER));
}

void CnvNumberDWORD(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _DWORD) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), NUMBER));
}

void CnvNumberFLOAT(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _FLOAT) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), NUMBER));
}

void CnvNumberINT(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _INT) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), NUMBER));
}

void CnvNumberLONG(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _LONG) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), NUMBER));
}

void CnvNumberNUMBER(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), NUMBER));
}

void CnvNumberWORD(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _WORD) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), NUMBER));
}

void CnvNumberWCHAR(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _WCHAR) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), NUMBER));
}

void CnvBOOLBoolean(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _BOOLEAN && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _BOOL));
}

void CnvBYTENumber(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _BOOLEAN && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _BYTE));
}

void CnvWORDNumber(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _BOOLEAN && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _WORD));
}

void CnvDOUBLENumber(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _BOOLEAN && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _DOUBLE));
}

void CnvNUMBERNum(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _BOOLEAN && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), NUMBER));
}

void CnvFLOATNumber(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _BOOLEAN && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _FLOAT));
}

void CnvLONGNumber(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _BOOLEAN && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _LONG));
}

void CnvDATETIMEDate(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != DATETIME) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), DATE_TIME));
}

void CnvHANDLEHan(struct DecompileInfo di) {
	/*
	if (di.expected_return_type != ANY && di.expected_return_type != VARIABLE_HANDLE) {
		throw new std::exception();
	}
	*/
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), ANY));
}

void CnvINTNumber(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _BOOLEAN && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _INT));
}


void CnvCHARNumber(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _BOOLEAN && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _CHAR));
}

void CnvDWORDNumber(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _BOOLEAN && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _DWORD));
}

void CnvSHORTNumber(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _BOOLEAN && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _SHORT));
}

void CnvWCHARNumber(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _BOOLEAN && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _WCHAR));
}

void CnvLPSTRString(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != STRING) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _LPSTR));
}



void CnvLPSHORTRecNumber(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _LPSHORT));
		return;
	}
	basic_operation("CnvLPSHORTRecNumber", di);
}

void CnvRecNumberLPSHORT(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _LPSHORT) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), NUMBER));
		return;
	}
	basic_operation("CnvRecNumberLPSHORT", di);
}

void CnvNumberSHORT(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _SHORT) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), NUMBER));
		return;
	}
	basic_operation("CnvNumberSHORT", di);
}

void CnvHandleHANDLE(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _HANDLE) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), VARIABLE_HANDLE));
		return;
	}
	basic_operation("CnvHandleHANDLE", di);
}

void CnvRecBooleanLPBOOL(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _LPBOOL) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _BOOLEAN));
		return;
	}
	basic_operation("CnvRecBooleanLPBOOL", di);
}

void CnvRecDateTimeLPDATETIME(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != LPDATETIME) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), DATETIME));
		return;
	}
	basic_operation("CnvRecDateTimeLPDATETIME", di);
}

void CnvRecNumberLPBYTE(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _LPBYTE) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), NUMBER));
		return;
	}
	basic_operation("CnvRecNumberLPBYTE", di);
}

void CnvRecNumberLPCHAR(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _LPCHAR) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), NUMBER));
		return;
	}
	basic_operation("CnvRecNumberLPCHAR", di);
}

void CnvRecNumberLPDOUBLE(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _LPDOUBLE) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), NUMBER));
		return;
	}
	basic_operation("CnvRecNumberLPDOUBLE", di);
}

void CnvRecNumberLPDWORD(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _LPDWORD) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), NUMBER));
		return;
	}
	basic_operation("CnvRecNumberLPDWORD", di);
}

void CnvRecNumberLPFLOAT(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _LPFLOAT) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), NUMBER));
		return;
	}
	basic_operation("CnvRecNumberLPFLOAT", di);
}

void CnvRecNumberLPINT(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _LPINT) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), NUMBER));
		return;
	}
	basic_operation("CnvRecNumberLPINT", di);
}

void CnvRecNumberLPLONG(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _LPLONG) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), NUMBER));
		return;
	}
	basic_operation("CnvRecNumberLPLONG", di);
}

void CnvRecNumberLPNUMBER(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != LPNUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), NUMBER));
		return;
	}
	basic_operation("CnvRecNumberLPNUMBER", di);
}

void CnvRecNumberLPWORD(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _LPWORD) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), NUMBER));
		return;
	}
	basic_operation("CnvRecNumberLPWORD", di);
}

void CnvRecStringHSTRING(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != HSTRING) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), STRING));
		return;
	}
	basic_operation("CnvRecStringHSTRING", di);
}

void CnvRecHandleLPHANDLE(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _LPHANDLE) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _HANDLE));
		return;
	}
	basic_operation("CnvRecHandleLPHANDLE", di);
}

void CnvLPHANDLERecHandle(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _HANDLE) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _LPHANDLE));
		return;
	}
	basic_operation("CnvLPHANDLERecHandle", di);
}

void CnvRecStringLPSTR(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _LPSTR) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), STRING));
		return;
	}
	basic_operation("CnvRecStringLPSTR", di);
}

void CnvRecStringLPHSTRING(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != LPHSTRING) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), STRING));
		return;
	}
	basic_operation("CnvRecStringLPHSTRING", di);
}

void CnvRecStringLPVOID(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _LPVOID) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), STRING));
		return;
	}
	basic_operation("CnvRecStringLPVOID", di);
}

void CnvStringHSTRING(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != HSTRING && di.expected_return_type != HBINARY) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		datatype expected = STRING;
		if (di.expected_return_type == HBINARY) {
			expected = _BINARY;
		}
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), expected));
		return;
	}
	basic_operation("CnvStringHSTRING", di);
}

void CnvHSTRINGString(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != STRING && di.expected_return_type != _BINARY) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		datatype expected = HSTRING;
		if (di.expected_return_type == _BINARY) {
			expected = HBINARY;
		}
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), expected));
		return;
	}
	basic_operation("CnvHSTRINGString", di);
}

void CnvStringLPSTR(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _LPSTR) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), STRING));
		return;
	}
	basic_operation("CnvStringLPSTR", di);
}

void CnvStringLPVOID(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _LPVOID) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), STRING));
		return;
	}
	basic_operation("CnvStringLPVOID", di);
}

void CnvLPBOOLRecBoolean(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _BOOLEAN && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _LPBOOL));
		return;
	}
	basic_operation("CnvLPBOOLRecBoolean", di);
}

void CnvLPDATETIMERectDateTime(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != DATETIME) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), LPDATETIME));
		return;
	}
	basic_operation("CnvLPDATETIMERectDateTime", di);
}

void CnvLPBYTERecNumber(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _LPBYTE));
		return;
	}
	basic_operation("CnvLPBYTERecNumber", di);
}

void CnvLPCHARRecNumber(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _LPCHAR));
		return;
	}
	basic_operation("CnvLPCHARRecNumber", di);
}

void CnvLPDOUBLERecNumber(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _LPDOUBLE));
		return;
	}
	basic_operation("CnvLPDOUBLERecNumber", di);
}

void CnvLPDWORDRecNumber(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _LPDWORD));
		return;
	}
	basic_operation("CnvLPDWORDRecNumber", di);
}

void CnvLPFLOATRecNumber(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _LPFLOAT));
		return;
	}
	basic_operation("CnvLPFLOATRecNumber", di);
}

void CnvLPINTRecNumber(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _LPINT));
		return;
	}
	basic_operation("CnvLPINTRecNumber", di);
}

void CnvLPLONGRecNumber(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _LPLONG));
		return;
	}
	basic_operation("CnvLPLONGRecNumber", di);
}

void CnvLPNUMBERRecNumber(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), LPNUMBER));
		return;
	}
	basic_operation("CnvLPNUMBERRecNumber", di);
}

void CnvLPWORDRecNumber(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _LPWORD));
		return;
	}
	basic_operation("CnvLPWORDRecNumber", di);
}

void CnvHSTRINGRecString(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != STRING) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), HSTRING));
		return;
	}
	basic_operation("CnvHSTRINGRecString", di);
}

void CnvLPSTRRecString(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != STRING) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _LPSTR));
		return;
	}
	basic_operation("CnvLPSTRRecString", di);
}

void CnvLPHSTRINGRecString(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != STRING) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), LPHSTRING));
		return;
	}
	basic_operation("CnvLPHSTRINGRecString", di);
}

void CnvLPVOIDRecString(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != STRING) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _LPVOID));
		return;
	}
	basic_operation("CnvLPVOIDRecString", di);
}

void CnvHSTRINGhString(struct DecompileInfo di) {
	if (di.expected_return_type != ANY
			&& di.expected_return_type != STRING
			&& di.expected_return_type != LONG_STRING
			&& di.expected_return_type != _BINARY) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	datatype expected = HSTRING;
	if (di.expected_return_type == _BINARY) {
		expected = HBINARY;
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), expected));
}

void CnvLPWSTRString(struct DecompileInfo di) {
	if (di.expected_return_type != ANY
			&& di.expected_return_type != STRING
			&& di.expected_return_type != LONG_STRING
			&& di.expected_return_type != _BINARY) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _LPWSTR));
}

void CastToUDV(struct DecompileInfo di) {
	if (di.expected_return_type != ANY
			&& di.expected_return_type != UDV
			&& di.expected_return_type != _HANDLE) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 2) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _HANDLE));
}

void CompareUDVEQ(struct DecompileInfo di) {
	GenericCompare(di,"=",PRECEDENCE_EQ_NEQ,datatype::_HANDLE);
}

void CompareUDVNE(struct DecompileInfo di) {
	GenericCompare(di,"!=",PRECEDENCE_EQ_NEQ,datatype::_HANDLE);
}

void CnvLPWSTRRecString(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != STRING) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _LPWSTR));
}

void CnvRecStringLPASCSTR(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != LPASCSTR) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), STRING));
}

void CnvStringLPASCSTR(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != LPASCSTR) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), STRING));
}

void CnvLPASCSTRString(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != STRING) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), LPASCSTR));
		return;
	}
	basic_operation("CnvLPASCSTRString", di);
}

void CnvLPASCSTRRecString(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != STRING) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), LPASCSTR));
		return;
	}
	basic_operation("CnvLPASCSTRRecString", di);
}

void CnvLPWCHARRecNumber(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), _LPWCHAR));
		return;
	}
	basic_operation("CnvLPWCHARRecNumber", di);
}

void CnvRecNumberLPWCHAR(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _LPWCHAR) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount == 1) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), NUMBER));
		return;
	}
	basic_operation("CnvRecNumberLPWCHAR", di);
}

void CnvToBoolean(struct DecompileInfo di) {
	if (di.expected_return_type != ANY && di.expected_return_type != _BOOLEAN && di.expected_return_type != NUMBER) {
		//throw new std::exception();
	}
	if (di.expression->XOperandCount != 1) {
		throw new std::exception();
	}
	decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), ANY));
}

void ArrayObjectVar(struct DecompileInfo di) {
	// may occur in Set statement with 4 parameters or in other statements with 3 parameters
	if (di.expression->XOperandCount == 3 || di.expression->XOperandCount == 4) {

		PRECEDENCE(PRECEDENCE_ASSIGN);
		oputs((di.expression->XOperandCount == 4 && print_brackets)?"(":"");

		// TODO: type?? --> array-reference
		uint32_t resultinfo = 0;
		struct DecompileInfo di2 = adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), ANY);
		di2.result_info = &resultinfo;
		decompile_expression(di2);
		oputs("[");
		di.outer_precedence = PRECEDENCE_MAX;
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 1), NUMBER));
		oputs("].");
		bool printed = false;
		if (resultinfo) {
			struct ItemBody* item_body = CItem::get_itembody(di.outline, resultinfo, 0x14);
			if (item_body) {
				if (item_body->data[0] == 0x05) {
					uint32_t class_type = *(uint32_t*)&item_body->data[4];
					struct tagOPERATOR* op = ParseGetNthOperand(di.compile_block, di.expression, 2);
					uint32_t offset = *(uint32_t*)(((uint8_t*)di.compile_block + op->XBuffer));
					uint32_t var = di.outline->lookup_variable(class_type, varscope::CURRENT_OBJECT, offset, false);
					if (var) {
						// TODO: extract variable type
						const char16_t* str = di.outline->symbol_lookup(var);
						if (str) {
							print_utf16(str);
							printed = true;
						}
						if (di.result_info) {
							*di.result_info = var;
						}
					}
				}
			}
		}
		if (!printed) {
			oputs("[ArrayObjectVar]offset");
			decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 2), _DWORD));
		}
		if (di.expression->XOperandCount == 4) {
			oputs(" = ");
			di.outer_precedence = PRECEDENCE_ASSIGN - 1;
			// TODO: pass variable type!!!
			decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 3), ANY));
			oputs(print_brackets?")":"");
		}
		return;
	}
	basic_operation("ArrayObjectVar", di);
}

void ArrayObjectAddress(struct DecompileInfo di) {
	if (di.expression->XOperandCount == 3) {
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 0), ANY));
		oputs("[");
		decompile_expression(adapt_dcinfo(di, ParseGetNthOperand(di.compile_block, di.expression, 1), ANY));
		oputs("]");
		return;
	}
	basic_operation("ArrayObjectVar", di);
}

// TODO: implement missing functions and complete this array
void (*DispatchFunction[])(struct DecompileInfo di) = {
		Const,
		Add,
		AddDate,
		Substract,
		SubstractDate,
		SubstractDateDate,
		Multiply,
		Divide,
		Negate,
		ExtFunction,
		Or,
		And,
		Not,
		CompareNumberLT,
		CompareNumberGT,
		CompareNumberEQ,
		CompareNumberLE,
		CompareNumberGE,
		CompareNumberNE,
		CompareStringLT,
		CompareStringGT,
		CompareStringEQ,
		CompareStringLE,
		CompareStringGE,
		CompareStringNE,
		CompareDateLT,
		CompareDateGT,
		CompareDateEQ,
		CompareDateLE,
		CompareDateGE,
		CompareDateNE,
		CompareHandleLT,
		CompareHandleGT,
		CompareHandleEQ,
		CompareHandleLE,
		CompareHandleGE,
		CompareHandleNE,
		Concat,
		LAnd,
		LOr,
		GetVarDate,
		GetVarHandle,
		GetVarNumber,
		GetVarString,
		GetVarPointer,
		GetVarAddress,
		PutVarDate,
		PutVarHandle,
		PutVarNumber,
		PutVarString,
		GetArrayDate,
		GetArrayHandle,
		GetArrayNumber,
		GetArrayString,
		IntFunction,
		GetFieldNumber,
		GetFieldString,
		GetFieldDate,
		PutFieldNumber,
		PutFieldString,
		PutFieldDate,
		GetScroll,
		PutScroll,
		NoOp,
		PutReturnDate,
		PutReturnHandle,
		PutReturnNumber,
		PutReturnString,
		GetCheck,
		PutCheck,
		GetFieldHandle,
		GethItemhWnd,
		__not_implemented_yet, // GethItem
		PutArrayDate,
		PutArrayHandle,
		PutArrayNumber,
		PutArrayString,
		CnvBooleanBOOL,
		CnvDateTimeDATETIME,
		CnvHandleHANDLE,
		CnvNumberBYTE,
		CnvNumberCHAR,
		CnvNumberDOUBLE,
		CnvNumberDWORD,
		CnvNumberFLOAT,
		CnvNumberINT,
		CnvNumberLONG,
		CnvNumberNUMBER,
		CnvNumberWORD,
		CnvRecHandleLPHANDLE,
		CnvRecBooleanLPBOOL,
		CnvRecDateTimeLPDATETIME,
		CnvRecNumberLPBYTE,
		CnvRecNumberLPCHAR,
		CnvRecNumberLPDOUBLE,
		CnvRecNumberLPDWORD,
		CnvRecNumberLPFLOAT,
		CnvRecNumberLPINT,
		CnvRecNumberLPLONG,
		CnvRecNumberLPNUMBER,
		CnvRecNumberLPWORD,
		CnvRecStringHSTRING,
		CnvRecStringLPSTR,
		CnvRecStringLPHSTRING,
		CnvRecStringLPVOID,
		CnvStringHSTRING,
		CnvStringLPSTR,
		CnvStringLPVOID,
		CnvHItemTEMPLATE,
		CnvLPHANDLERecHandle,
		CnvLPBOOLRecBoolean,
		CnvLPDATETIMERectDateTime,
		CnvLPBYTERecNumber,
		CnvLPCHARRecNumber,
		CnvLPDOUBLERecNumber,
		CnvLPDWORDRecNumber,
		CnvLPFLOATRecNumber,
		CnvLPINTRecNumber,
		CnvLPLONGRecNumber,
		CnvLPNUMBERRecNumber,
		CnvLPWORDRecNumber,
		CnvHSTRINGRecString,
		CnvLPSTRRecString,
		CnvLPHSTRINGRecString,
		CnvLPVOIDRecString,
		CnvDOUBLENumber,
		CnvNUMBERNum,
		CnvFLOATNumber,
		CnvLONGNumber,
		CnvDATETIMEDate,
		CnvHANDLEHan,
		CnvHSTRINGString,
		__not_implemented_yet, // CnvTEMPLATEHItem
		CnvINTNumber,
		CnvCHARNumber,
		CnvDWORDNumber,
		__not_implemented_yet, // CnvUnRef
		CnvHSTRINGhString,
		__not_implemented_yet, // GetItemViaSymAndhWnd
		__not_implemented_yet, // CheckWindowshItem
		__not_implemented_yet, // CheckSqlContext
		GetParenthWndByhItem,
		__not_implemented_yet, // GetParenthWndByhItemIndirect
		__not_implemented_yet, // CheckSqlObject
		__not_implemented_yet, // GetColumnDlgId
		__not_implemented_yet, // GetDlgId
		IntFunSetupIndirect,
		IntFunSetupLate,
		__not_implemented_yet, // NULL
		IntFunSetupClassIndirect,
		IntFunSetupClassArray,
		IntFunSetupClassObject,
		GethWndMDI,
		GethWndForm,
		ArrayObjectVar,
		ArrayObjectAddress,
		__not_implemented_yet, // CnvUnlockUnRef
		CnvToBoolean,
		IntFunSetupUDVRef,
		MakeUDVRef,
		GetVarUDVRef,
		CnvUdvRefUDVREF,
		__not_implemented_yet, // GetHItemOfDlgId
		__not_implemented_yet, // GetParenthWndByLevel
		CheckIndexList,
		CnvHItemTaggedTEMPTAGGED,
		CnvPointerLPSTR,
		__not_implemented_yet, // CnvTEMPTAGGEDHItemTagged
		CnvStaticString,
		ConstH,
		CnvBOOLBoolean,
		CnvBYTENumber,
		CnvWORDNumber,
		CnvSHORTNumber,
		CnvNumberSHORT,
		CnvLPSTRString,
		CnvLPSHORTRecNumber,
		CnvRecNumberLPSHORT,
		New,
		PutUDVHan,
		GetUDVHan,
		AdjUDVHan,
		MakeUDVRf,
		CnvUDVToHandle,
		PutReturnUDV,
		__not_implemented_yet, // NewExpr
		CastUdv,
		PutArrayUDV,
		GetArayUDV,
		CompareUDVEQ,
		CompareUDVNE,
		CastToUDV,
		__not_implemented_yet, // AdjustUDVRef
		MakeUDV,
		__not_implemented_yet, // ResetUDV
		__not_implemented_yet, // PutUDVREF
		__not_implemented_yet, // GetUDVREF
		__not_implemented_yet, // CnvExtUDVREF
		CnvStringLPWSTR,
		CnvRecStringLPWSTR,
		CnvLPWSTRRecString,
		CnvLPWSTRString,
		CnvNumberWCHAR,
		CnvWCHARNumber,
		CnvLPWSTRString, // [duplicate] ; works on BINARY instead of STRING
		CnvLPWSTRRecString, // [duplicate] ; works on BINARY instead of STRING
		CnvRecStringLPASCSTR,
		CnvStringLPASCSTR,
		CnvLPASCSTRString,
		CnvLPASCSTRRecString,
		CnvLPWCHARRecNumber,
		CnvRecNumberLPWCHAR,
		__not_implemented_yet, // GethWndFrame
		GetArrayString, // [duplicate] ; works on BINARY instead of STRING
		PutArrayString, // [duplicate] ; works on BINARY instead of STRING
		PutVarString, // [duplicate] ; works on BINARY instead of STRING
		GetVarString, // [duplicate] ; works on BINARY instead of STRING
		PutReturnString, // [duplicate] ; works on BINARY instead of STRING
		CnvHSTRINGhString, // [duplicate] ; works on BINARY instead of STRING
		CnvRecStringLPHSTRING, // [duplicate] ; works on BINARY instead of STRING
		CnvLPHSTRINGRecString, // [duplicate] ; works on BINARY instead of STRING
		CnvRecStringHSTRING, // [duplicate] ; works on BINARY instead of STRING
		CnvHSTRINGRecString, // [duplicate] ; works on BINARY instead of STRING
		CnvStringHSTRING, // [duplicate] ; works on BINARY instead of STRING
		CompareBinaryLT,
		CompareBinaryGT,
		CompareBinaryEQ,
		CompareBinaryLE,
		CompareBinaryGE,
		CompareBinaryNE,
		CnvRecStringLPVOID, // [duplicate] ; works on BINARY instead of STRING
		CnvLPVOIDRecString, // [duplicate] ; works on BINARY instead of STRING
		CnvStringLPVOID, // [duplicate] ; works on BINARY instead of STRING
		New, // New2 (for use with IntConstructor)
		IntConstructor,
		__not_implemented_yet, // Return
		__not_implemented_yet, // CnvLONGLONGNumber
		__not_implemented_yet, // CnvNumberLONGLONG
		__not_implemented_yet, // CnvRecNumberLPLONGLONG
		__not_implemented_yet, // CnvLPLONGLONGRecNumber
		__not_implemented_yet, // CnvDWORDLONGNumber
		__not_implemented_yet, // CnvNumberDWORDLONG
		__not_implemented_yet, // CnvRecNumberLPDWORDLONG
		__not_implemented_yet, // CnvLPDWORDLONGRecNumber
		__not_implemented_yet, // CnvUDVHanToUDVREF
		__not_implemented_yet, // PutUDVHanWinParm
		__not_implemented_yet, // NULL
		__not_implemented_yet, // undefined
		__not_implemented_yet, // undefined
		__not_implemented_yet, // undefined
		__not_implemented_yet, // undefined
		__not_implemented_yet, // undefined
		__not_implemented_yet, // undefined
		__not_implemented_yet, // undefined
		__not_implemented_yet, // undefined
		__not_implemented_yet  // undefined
};

const char* DispatchArray[] = {
		"Const",
		"Add",
		"AddDate",
		"Substract",
		"SubstractDate",
		"SubstractDateDate",
		"Multiply",
		"Divide",
		"Negate",
		"ExtFunction",
		"Or",
		"And",
		"Not",
		"CompareNumber",
		"CompareNumber",
		"CompareNumber",
		"CompareNumber",
		"CompareNumber",
		"CompareNumber",
		"CompareString",
		"CompareString",
		"CompareString",
		"CompareString",
		"CompareString",
		"CompareString",
		"CompareDate",
		"CompareDate",
		"CompareDate",
		"CompareDate",
		"CompareDate",
		"CompareDate",
		"CompareHandle",
		"CompareHandle",
		"CompareHandle",
		"CompareHandle",
		"CompareHandle",
		"CompareHandle",
		"Concat",
		"LAnd",
		"LOr",
		"GetVarDate",
		"GetVarHandle",
		"GetVarNumber",
		"GetVarString",
		"GetVarPointer",
		"GetVarAddress",
		"PutVarDate",
		"PutVarHandle",
		"PutVarNumber",
		"PutVarString",
		"GetArrayDate",
		"GetArrayHandle",
		"GetArrayNumber",
		"GetArrayString",
		"IntFunction",
		"GetFieldNumber",
		"GetFieldString",
		"GetFieldDate",
		"PutFieldNumber",
		"PutFieldString",
		"PutFieldDate",
		"GetScroll",
		"PutScroll",
		"NoOp",
		"PutReturnDate",
		"PutReturnHandle",
		"PutReturnNumber",
		"PutReturnString",
		"GetCheck",
		"PutCheck",
		"GetFieldHandle",
		"GethItemhWnd",
		"GethItem",
		"PutArrayDate",
		"PutArrayHandle",
		"PutArrayNumber",
		"PutArrayString",
		"CnvBooleanBOOL",
		"CnvDateTimeDATETIME",
		"CnvHandleHANDLE",
		"CnvNumberBYTE",
		"CnvNumberCHAR",
		"CnvNumberDOUBLE",
		"CnvNumberDWORD",
		"CnvNumberFLOAT",
		"CnvNumberINT",
		"CnvNumberLONG",
		"CnvNumberNUMBER",
		"CnvNumberWORD",
		"CnvRecHandleLPHANDLE",
		"CnvRecBooleanLPBOOL",
		"CnvRecDateTimeLPDATETIME",
		"CnvRecNumberLPBYTE",
		"CnvRecNumberLPCHAR",
		"CnvRecNumberLPDOUBLE",
		"CnvRecNumberLPDWORD",
		"CnvRecNumberLPFLOAT",
		"CnvRecNumberLPINT",
		"CnvRecNumberLPLONG",
		"CnvRecNumberLPNUMBER",
		"CnvRecNumberLPWORD",
		"CnvRecStringHSTRING",
		"CnvRecStringLPSTR",
		"CnvRecStringLPHSTRING",
		"CnvRecStringLPVOID",
		"CnvStringHSTRING",
		"CnvStringLPSTR",
		"CnvStringLPVOID",
		"CnvHItemTEMPLATE",
		"CnvLPHANDLERecHandle",
		"CnvLPBOOLRecBoolean",
		"CnvLPDATETIMERectDateTime",
		"CnvLPBYTERecNumber",
		"CnvLPCHARRecNumber",
		"CnvLPDOUBLERecNumber",
		"CnvLPDWORDRecNumber",
		"CnvLPFLOATRecNumber",
		"CnvLPINTRecNumber",
		"CnvLPLONGRecNumber",
		"CnvLPNUMBERRecNumber",
		"CnvLPWORDRecNumber",
		"CnvHSTRINGRecString",
		"CnvLPSTRRecString",
		"CnvLPHSTRINGRecString",
		"CnvLPVOIDRecString",
		"CnvDOUBLENumber",
		"CnvNUMBERNum",
		"CnvFLOATNumber",
		"CnvLONGNumber",
		"CnvDATETIMEDate",
		"CnvHANDLEHan",
		"CnvHSTRINGString",
		"CnvTEMPLATEHItem",
		"CnvINTNumber",
		"CnvCHARNumber",
		"CnvDWORDNumber",
		"CnvUnRef",
		"CnvHSTRINGhString",
		"GetItemViaSymAndhWnd",
		"CheckWindowshItem",
		"CheckSqlContext",
		"GetParenthWndByhItem",
		"GetParenthWndByhItemIndirect",
		"CheckSqlObject",
		"GetColumnDlgId",
		"GetDlgId",
		"IntFunSetupIndirect",
		"IntFunSetupLate",
		"NULL",
		"IntFunSetupClassIndirect",
		"IntFunSetupClassArray",
		"IntFunSetupClassObject",
		"GethWndMDI",
		"GethWndForm",
		"ArrayObjectVar",
		"ArrayObjectAddress",
		"CnvUnlockUnRef",
		"CnvToBoolean",
		"IntFunSetupUDVRef",
		"MakeUDVRef",
		"GetVarUDVRef",
		"CnvUdvRefUDVREF",
		"GetHItemOfDlgId",
		"GetParenthWndByLevel",
		"CheckIndexList",
		"CnvHItemTaggedTEMPTAGGED",
		"CnvPointerLPSTR",
		"CnvTEMPTAGGEDHItemTagged",
		"CnvStaticString",
		"ConstH",
		"CnvBOOLBoolean",
		"CnvBYTENumber",
		"CnvWORDNumber",
		"CnvSHORTNumber",
		"CnvNumberSHORT",
		"CnvLPSTRString",
		"CnvLPSHORTRecNumber",
		"CnvRecNumberLPSHORT",
		"New",
		"PutUDVHan",
		"GetUDVHan",
		"AdjUDVHan",
		"MakeUDVRf",
		"CnvUDVToHandle",
		"PutReturnUDV",
		"NewExpr",
		"CastUdv",
		"PutArrayUDV",
		"GetArayUDV",
		"CompareUDV",
		"CompareUDV",
		"CastToUDV",
		"AdjustUDVRef",
		"MakeUDV",
		"ResetUDV",
		"PutUDVREF",
		"GetUDVREF",
		"CnvExtUDVREF",
		"CnvStringLPWSTR",
		"CnvRecStringLPWSTR",
		"CnvLPWSTRRecString",
		"CnvLPWSTRString",
		"CnvNumberWCHAR",
		"CnvWCHARNumber",
		"CnvLPWSTRString",
		"CnvLPWSTRRecString",
		"CnvRecStringLPASCSTR",
		"CnvStringLPASCSTR",
		"CnvLPASCSTRString",
		"CnvLPASCSTRRecString",
		"CnvLPWCHARRecNumber",
		"CnvRecNumberLPWCHAR",
		"GethWndFrame",
		"GetArrayString",
		"PutArrayString",
		"PutVarString",
		"GetVarString",
		"PutReturnString",
		"CnvHSTRINGhString",
		"CnvRecStringLPHSTRING",
		"CnvLPHSTRINGRecString",
		"CnvRecStringHSTRING",
		"CnvHSTRINGRecString",
		"CnvStringHSTRING",
		"CompareBinary",
		"CompareBinary",
		"CompareBinary",
		"CompareBinary",
		"CompareBinary",
		"CompareBinary",
		"CnvRecStringLPVOID",
		"CnvLPVOIDRecString",
		"CnvStringLPVOID",
		"New2",
		"IntConstructor",
		"Return",
		"CnvLONGLONGNumber",
		"CnvNumberLONGLONG",
		"CnvRecNumberLPLONGLONG",
		"CnvLPLONGLONGRecNumber",
		"CnvDWORDLONGNumber",
		"CnvNumberDWORDLONG",
		"CnvRecNumberLPDWORDLONG",
		"CnvLPDWORDLONGRecNumber",
		"CnvUDVHanToUDVREF",
		"PutUDVHanWinParm",
		"NULL",
		"undefined",
		"undefined",
		"undefined",
		"undefined",
		"undefined",
		"undefined",
		"undefined",
		"undefined",
		"undefined",
};
