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
#ifndef OUTLINE_HPP_
#define INC_ITEM_HPP_
#define OUTLINE_HPP_
#endif
#endif

#ifdef TDx64
#ifndef OUTLINE64_HPP_
#define INC_ITEM_HPP_
#define OUTLINE64_HPP_
#endif
#endif

#ifdef INC_ITEM_HPP_
#include "outline_decs.hpp"
#include "item.hpp"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <map>

#include "def64.inc"

#ifdef TDx64
#undef HANDTABLE_ITEMSIZE_MASK
#define HANDTABLE_ITEMSIZE_MASK 0x03ffffff
#undef ITEM_ID_WIDTH
#define ITEM_ID_WIDTH 32
#else
#define HANDTABLE_ITEMSIZE_MASK 0x3fff
#define ITEM_ID_WIDTH 16
#endif


#ifndef TDx64
struct SymbolLookup{
	uint32_t hitem;
	uint8_t* str;
	struct SymbolLookup* next;
};
#endif

class COutline {
private:
	FILE* handle = NULL;
	struct FileHdr file_hdr;
	struct Outline* outline = NULL;
	SymbolHash symbol_hash;
	char* ax_lib_info = NULL;
	char* class_relationships = NULL;
	char* co_class_list = NULL;
	struct CompressionHeader cmphdr;
	struct StringTable* string_table = NULL;
	struct tagOSEG** tag_oseg = NULL;
	struct HandTable** hand_table = NULL;
	struct tagPERMSYM*** symbols = NULL;
	char* str_data = NULL;
	struct ClassMap {
		uint32_t size;
		uint64_t* item;
	} class_map = {0, NULL};
	struct OrdinalMap {
		uint32_t size;
		uint64_t* item;
	};
	struct DynalibMap {
		uint32_t size;
		struct OrdinalMap* ordinal_map;
	} dynamlib_map = {0, NULL};
	std::map<uint64_t, uint64_t> item_loop_info = std::map<uint64_t, uint64_t>();
	std::map<uint32_t, std::map<uint32_t, uint32_t>> dialog_dlgitems = std::map<uint32_t, std::map<uint32_t, uint32_t>>();

	long OsReadFast(unsigned long length, char* result);
	// if compressed == NULL: read from file this->handle
	unsigned long OsDeCompress(unsigned long output_len, void* decompressed, unsigned long input_len, void* compressed = NULL);
	struct HandTable* create_handtable(struct tagOSEG* item_content, uint64_t item_id);
	void init_symbol_lookup();

	uint8_t is_null(struct SalNumber* num);
	void print_flag(uint32_t flag, const char* flag_name);
	void print_stat(uint32_t value, const char* name);

	// helper function for find-children-call
	uint32_t find_siblings_of_type_and_run(void (*callback)(class COutline* outline, uint64_t item, void* param), void* param, uint64_t item, const uint16_t* type, bool only_one_match);

	struct RuntimeMemoryScope* get_memory(uint64_t item_id, varscope scope);
public:
	COutline(FILE* handle);

	uint64_t top_item();
	/**
	 * get next sibling
	 */
	uint64_t next_item(uint64_t item_id);
	/**
	 * get child
	 */
	uint64_t child_item(uint64_t item_id);
	tagITEM* get_item(uint64_t item_id);
	uint64_t item_pointer_dereference(uint64_t item);

	void add_class_item(uint64_t class_id, uint64_t item_id);
	uint64_t get_class_item(uint64_t class_id);

	void add_dynalib_var(uint16_t libsal, uint16_t ordinal, uint64_t item);
	uint64_t get_dynalib_var(uint16_t libsal, uint16_t ordinal);

	void set_item_loop_info(uint64_t item, uint64_t data);
	uint64_t get_item_loop_info(uint64_t item);

	void set_dialog_dlgitem(uint32_t dialog, uint32_t dlgitem, uint32_t item);
	uint32_t get_dialog_dlgitem(uint32_t dialog, uint32_t dlgitem);

	uint64_t insert_item(uint32_t seginf);

	bool add_variable(uint64_t item_id, enum varscope scope, uint16_t offset, uint64_t reference);
	uint64_t lookup_variable(uint64_t item_id, enum varscope scope, uint16_t offset, bool print_namespace = false);
	bool has_any_variable(uint64_t item_id, varscope scope);

	/**
	 * only direct children (not recursive)
	 * type: 0-terminated array
	 * returns number of performed callback-calls
	 */
	uint32_t find_children_of_type_and_run(void (*callback)(class COutline* outline, uint64_t item, void* param), void* param, uint64_t item, const uint16_t* type, bool only_one_match = true);

	const char16_t* symbol_lookup(uint64_t item_id);
	const struct String* string_lookup(uint32_t string_id);
	void sprint_number(char out[300], struct SalNumber* num);
	void sprint_date(char out[32], struct SalNumber* num);

	bool change_item_size(uint64_t item_id, uint32_t new_size);

	// handle must be a handle to a file opened in "w+b" or "r+b" mode;
	// writing starts at current stream position
	// retruns number of bytes written
	uint32_t save(FILE* handle);

	void print_stats();
	struct FileHdr get_file_hdr();
};

#endif /* OUTLINE_HPP_ */
#undef INC_ITEM_HPP_
