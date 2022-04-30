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

#ifndef OUTLINE_DECS_HPP_
#define OUTLINE_DECS_HPP_
#include <stdint.h>

#define TD_SIGNATURE 0x5244474d // "MGDR"

#define VERSION_TD51 0x206
#define VERSION_TD52 0x209
#define VERSION_TD60 0x20b
#define VERSION_TD61 0x211
#define VERSION_TD62 0x214
#define VERSION_TD63 0x216
#define VERSION_TD70 0x217
#define VERSION_TD71 0x218
#define VERSION_TD72 0x219
#define VERSION_TD73 0x21A
#define VERSION_TD74 0x21B

// filehdr-flags
#define FLAG_COMPILED 0x01
#define FLAG_NOT_EDITABLE 0x02
#define FLAG_VISIBLE_H_ITEMS 0x04
#define FLAG_IS_EXE 0x08
#define FLAG_IS_DLL 0x10
#define FLAG_IS_64BIT 0x20

#define RUN_ONLY 0x4f4e5552 // "RUNO"

// outline-flags
#define OFLAG_APP_SYMBOLS_CURRENT 0x01 // TODO: handle flag. if this flag is set, outline->lpLibTable = OamDynLibTableStartup(); is executed
#define OFLAG_APP_IS_COMPILED 0x02
#define OFLAG_APP_CHANGED 0x04
#define OFLAG_APP_SAVE_COMPILED 0x08
#define OFLAG_FILE_IS_EXE 0x10
#define OFLAG_FILE_IS_DLL 0x20
#define OFLAG_UNTITLED 0x40
#define OFLAG_SHARE 0x80
#define OFLAG_ALL_MARKED 0x100
#define OFLAG_HIDDEN_INCLUDED 0x200
#define OFLAG_RUN_ONLY 0x400
#define OFLAG_CHILD_LINE_COUNTS_ADDED 0x800
#define OFLAG_GLMS_SIGN_MASK 0xF000 // 4bit-value
#define OFLAG_GLMS_SIGN_TESTVERSION 0xA000
// OFLAG_TARGET_OS 0x70000 // 4bit-value

#define ITEM_HAS_HANDLE_TABLE 0x200
#define ITEM_IS_RESOURCE 0x400
#define ITEM_IS_SYMBOL_ARRAY 0x800

#pragma pack(push)  /* push current alignment to stack */
#pragma pack(1)     /* set alignment to 1 byte boundary */

struct FileHdr {
	uint32_t signature;
	uint16_t version;
	uint16_t old_outline_alloc;
	uint32_t flags;
	uint32_t run_only;
	uint16_t com_version; // value 0x6f seems to be relevant, at least for TD 7.2.0
	uint16_t reserved;
	uint32_t outline_alloc;
	uint32_t build_num;
	uint32_t auto_create_count;
	uint32_t ax_lib_info_offset;
	uint32_t ax_lib_info_len;
	uint32_t co_class_list_offset;
	uint32_t co_class_list_len;
	uint32_t co_class_interface_map_len;
	uint32_t class_relationship_offset;
	uint32_t class_relationship_length;
	uint32_t header_flags; // seems to be 0x00000000 usually...
	uint32_t reserved2[3];
};

struct OutStats {
	uint32_t items;
	uint32_t dummy;
	uint32_t functions;
	uint32_t variables;
	uint32_t dialog_boxes;
	uint32_t form_windows;
	uint32_t table_windows;
	uint32_t mdi_windows;
	uint32_t child_windows;
	uint32_t sal_lines;
	uint32_t comments;
	uint32_t to_compile;
	uint32_t compile_ref;
	uint32_t reserved[3];
};

typedef uint16_t SymbolHash[0x97];
typedef uint32_t SymbolHash64[0x97];

struct tagPERMSYM {
	uint32_t hItem;
	uint32_t nItemType;
	uint32_t hItemOwner;
	uint8_t bDataType;
	uint32_t lVarInfo;
	uint32_t flags;
	uint8_t str[0]; // utf-16 coded string, \0-terminated
};

struct tagPERMSYM64 {
	uint64_t hItem;
	uint32_t nItemType;
	uint64_t hItemOwner;
	uint8_t bDataType;
	uint64_t lVarInfo;
	uint32_t flags;
	uint8_t str[0]; // utf-16 coded string, \0-terminated
};

//// --> An array HItem[seg_inf_limit] follows after the Outline struct. Together they form a block of total size outline_alloc.
struct HItem{
	uint32_t offset; // (in file)
	uint32_t size; // (decompressed!!!)
	uint32_t segment; // Pointer to tagOSEG -----> Item-Data is loaded there
	// flags:
	// compression (least significat byte: bitmask):
	// XXXXX10X (or 0x100 is set) --> OsReadExplode;
	// XXXXX00X --> uncompressed (copy);
	// XXXXX01X --> OsReadZeroSupp;
	// XXXXX11X --> OsReadFast;;;;
	//
	// XXXXXXX1 --> item contains data
	// XXXXXXX0 --> empty/dummy item
	//
	// item type:
	// 0x200: HANDTABLE-item
	// 0x400: resource-item
	// 0x800: symbolmap-item (string dereferences)
	uint32_t flags;
	uint32_t unknown1;
	uint32_t unknown2;
};

struct HItem64{
	uint32_t offset; // (in file)
	uint32_t size; // (decompressed!!!)
	uint64_t segment; // Pointer to tagOSEG -----> Item-Data is loaded there
	uint64_t flags;
	uint64_t unknown1;
	uint64_t unknown2;
};

struct Outline {
	uint32_t hItemTop;
	uint32_t hItemEdit;
	uint32_t hItemMarkParent;
	uint32_t lEditDataValue;
	uint32_t nEditDataValue;
	uint32_t nEditDataType;
	uint32_t nEditDataList;
	uint32_t nEditListIndex;
	uint32_t nEditLine;
	uint32_t nEditOldLineCount;
	uint32_t outline_alloc; // size of Outline-Structure
	uint16_t seg_inf_limit; // max. number of elements in SegInf (-->HITEMs)
	uint16_t scrap_list;
	uint32_t flags;
	struct OutStats statistics;
	uint32_t hOutline; // 0x08
	uint32_t process_id;
	uint32_t h_string_tables; // offset of StringTable CompressionHeader
	uint32_t lpHStringStaticTable;
	uint32_t bulk_load_start;
	uint32_t bulk_load_end;
	uint32_t nItemTypeEdit;
	uint32_t hItemAppDest;
	uint32_t lpLibTable;
	uint32_t symbol_hash;
	uint32_t lpLibGlobals;
	uint32_t unused;
	uint32_t lpIncludeInfo;
	uint16_t hResInfo;
	uint16_t nItemTypeScrapParent;
	uint32_t segfile_hFile;
	uint32_t segfile_lpszSegPathName;
	uint8_t  padding[516];
	uint32_t lpCodeBlockCache;
	uint32_t lpMessageMapCache;
	uint32_t lpSegCacheInfo;
	uint32_t header_flags; // overwritten by FileHdr.header_flags ---> they seem to be 0x00000000 usually (see above)
	uint32_t lpBrkptInfo;
	uint32_t nBrkptInfoLen;
	uint32_t reserved[2];
	struct HItem data[0];
};


struct Outline64 {
	uint64_t hItemTop;
	uint64_t hItemEdit;
	uint64_t hItemMarkParent;
	uint32_t lEditDataValue;
	uint32_t nEditDataValue;
	uint32_t nEditDataType;
	uint32_t nEditDataList;
	uint32_t nEditListIndex;
	uint32_t nEditLine;
	uint32_t nEditOldLineCount;
	uint32_t outline_alloc; // size of Outline-Structure
	uint32_t seg_inf_limit; // max. number of elements in SegInf (-->HITEMs)
	uint32_t scrap_list;
	uint32_t flags;
	struct OutStats statistics;
	uint32_t padding;
	uint64_t hOutline; // 0x08
	uint32_t process_id;
	uint32_t h_string_tables; // offset of StringTable CompressionHeader
	uint64_t lpHStringStaticTable;
	uint64_t bulk_load_start;
	uint64_t bulk_load_end;
	uint32_t nItemTypeEdit;
	uint32_t padding2;
	uint64_t hItemAppDest;
	uint64_t lpLibTable;
	uint64_t symbol_hash;
	uint64_t lpLibGlobals;
	uint64_t unused;
	uint64_t lpIncludeInfo;
	uint32_t hResInfo;
	uint16_t nItemTypeScrapParent;
	uint16_t padding3;
	uint32_t segfile_hFile;
	uint32_t padding4;
	uint64_t segfile_lpszSegPathName;
	uint8_t  padding5[512];
	uint64_t lpCodeBlockCache;
	uint64_t lpMessageMapCache;
	uint64_t lpSegCacheInfo;
	uint32_t header_flags; // overwritten by FileHdr.header_flags ---> they seem to be 0x00000000 usually (see above)
	uint32_t padding6;
	uint64_t lpBrkptInfo;
	uint32_t nBrkptInfoLen;
	uint32_t padding7;
	uint32_t reserved[2];
	struct HItem64 data[0];
};

// if the App is "compiled" (corresponding to its Outline header): call FesSetAllClassDefaults(0) after loading the data.

// after everything has been loaded, the App -- or at least its OnLoad function -- is started by calling
//     int ComSetUserMode(void)

struct CompressionHeader { // CompressedStringTable: Header
	uint16_t comp_type;
	uint16_t stringtable_type;
	uint32_t comp_size;
	uint32_t uncomp_size;
	uint32_t hstring_size; // size of the string area.
	uint16_t magic; // 0x8899
	uint16_t reserved; // 0x0000
}; // followed by HStringTable-Header (struct) and the char*[]-Array containing the pointers to the strings.

struct StringTable {
	uint32_t total_num_entries;
	uint32_t num_free_entries;
	uint32_t free_list;
	uint32_t str[0]; // offset in decompressed data
};

struct StringTable64 {
	uint32_t total_num_entries;
	uint32_t num_free_entries;
	uint64_t free_list;
	uint64_t str[0]; // offset in decompressed data // TODO: uint64_t??
};

struct String {
	uint32_t len; // in bytes
	uint32_t reserved;
	const char16_t str[0]; // utf-16 coded string
};


// located at tagOSEG->data field of hResInfo-Item
struct ResInfo {
	uint16_t res_seg; // pointer to first tagRESSEG; they are chained together by their hNext entries
	uint16_t res_hash_names[30]; // pointer to tagRRES-elements
};

// a chain of these structs follow ResInfo; terminated by size==0, id==0 struct
struct ResItemStruct{ // name of struct in cdlli??.dll??
	uint16_t size; // including this struct-Header
	uint16_t id;
	uint8_t data[0];
};

struct tagRESSEG{
	uint16_t hNext; // res_seg-chain... terminated by 0x00
	uint16_t wSegType;
	uint16_t hSegInf; // reference to res-item for res_seg-id, e.g. 0xab???
	uint16_t wUseCount;
	uint16_t flags; // bShrunk
};

struct tagRESNAME {
	uint16_t hNext; // list of entries for same res_hash_name... terminated by 0x00
	uint16_t wResType;
	uint16_t wUseCount;
	uint32_t lResLong;
	uint16_t hResSeg; // pointer to tagRESSEG
	uint16_t hResHdr;
	uint16_t wHash; // how is it computed?
	uint32_t flags; // bLoaded, bMarked
	char16_t szFilename[1];
};

struct ResHdr {
	uint32_t uncompressed_len;
	uint32_t compressed_len;
	uint32_t timestamp;
	uint32_t crc32;
	uint16_t compression_type; // 0: copy; 1: OamConvResData --> starts 16bit PE file from TD folder: system("swcomp.exe -u compressed.bin decompressed.bin"); --> fails for 64bit Windows 2: OsDeCompress
	uint8_t data[0]; // (compressed) ResData
};

// parse HItem and return a CompileBlock: OamItemData(...)
struct CompileBlock {
	uint8_t flags;
	uint16_t start;
	uint16_t size;
	uint16_t data_size;
};


struct ItemBody { // contains data of item, e.g. a CompileBlock or a String reference
	uint8_t type;
	uint16_t size; // size of dynamically-sized item elements (for fixed sized elements, data starts here already)
	uint8_t data[0]; // data (e.g. a CompileBlock if ItemBody.type == 0x09)
};

// tree-structure of items. each item contains a chain of ItemBody elements
struct tagITEM {
	uint16_t type;
	uint16_t parent;
	// flags:
	// 0xff0000: number of lines in item if displayed in TD GUI
	// 0x001000: !__exported
	// 0x000400: hide item in TD // imported
	// 0x000100: has CODE block
	// 0x000040: CLONE item (pointer)
	uint32_t flags;
	uint16_t next_sibling;
	uint16_t first_child;
	uint16_t data_length;
	uint8_t data[0]; // one or more ItemBody elements
};

struct tagITEM64 {
	uint16_t type;
	uint16_t data_length;
	uint32_t parent;
	uint32_t next_sibling;
	uint32_t first_child;
	uint32_t flags;
	uint8_t data[0]; // one or more ItemBody elements
};

struct tagHEAPBLK {
	uint16_t value; // if high bit 0x8000 is set, a "free list" follows in data field... see OamAllocateHandleTable -> call of OamCoalesce(0,????)... not supported here;
	// if bit 0x8000 is not set: apply 0x3fff-mask and multiply this value with 4 to get real size of item
	// 0x4000: OamHpTagged flag: --> tagITEM header follows in data field
	// 0x0000: raw data without header... a uint16_t size info may follow, at least for raw utf16-string-data
	uint16_t handle_id; // at most maxUsedHandle and at least 0x01; otherwise, the entry is ignored
	uint8_t data[0]; //tagItem-chain
};

struct tagHEAPBLK64 {
	uint32_t value; // if high bit 0x8000000 is set, a "free list" follows in data field... see OamAllocateHandleTable -> call of OamCoalesce(0,????)... not supported here;
	// if bit 0x8000000 is not set: apply 0x3ffffff-mask and multiply this value with 4 to get real size of item
	// 0x4000000: OamHpTagged flag: --> tagITEM header follows in data field
	// 0x0000000: raw data without header... a uint16_t size info may follow, at least for raw utf16-string-data
	uint32_t handle_id; // at most maxUsedHandle and at least 0x01; otherwise, the entry is ignored
	uint8_t data[0]; //tagItem-chain
};


/// The tagHEAPBLK are chained together as well...

// Header-Structure of a single SEGMENT (SegInf), followed by chain of tagHEAPBLK or other, depending on HItem-type
struct tagOSEG{
	uint32_t seghd_lpHandMap;
	uint32_t seghd_shFreeList;
	uint16_t seghd_maxUsedHandle; ///// ----> Handles in HandTable; defaults to 10 if maxUsedHandle is 0x00
	uint16_t seghd_shStartDynamic; ////// Address of first HandMapItem (offset from tagOSEG's offset)
	uint32_t seghd_padding;
	uint32_t ohCloneItem; // pointer to HITEM__
	uint32_t ohItemCount;
	uint32_t ohhOutline; // pointer to HOUTLINE__
	uint16_t ohSegInf;
	uint8_t data[0]; // chain of HandMapItems
};

struct tagOSEG64{
	uint64_t seghd_lpHandMap;
	uint32_t seghd_shFreeList;
	uint32_t seghd_maxUsedHandle; ///// ----> Handles in HandTable; defaults to 10 if maxUsedHandle is 0x00
	uint32_t seghd_shStartDynamic; ////// Address of first HandMapItem (offset from tagOSEG's offset)
	uint32_t seghd_padding;
	uint64_t ohCloneItem; // pointer to HITEM__
	uint32_t ohItemCount;
	uint32_t padding;
	uint64_t ohhOutline; // pointer to HOUTLINE__
	uint32_t ohSegInf;
	uint32_t padding2;
	uint8_t data[0]; // chain of HandMapItems
};

struct RuntimeMemoryScope {
	uint16_t current_size;
	uint32_t* item_id;
};

struct RuntimeMemory {
	struct RuntimeMemoryScope scope[0x11];
};

struct HandTable {
	uint16_t size;
	struct tagITEM* handle_data;
	struct RuntimeMemory* memory;
};

struct HandTable64 {
	uint32_t size;
	struct tagITEM64* handle_data;
	struct RuntimeMemory* memory;
};

struct tagOPERATOR {
	uint16_t XBuffer;
	uint8_t  XOPType;
	uint8_t  XImmedData;
	uint8_t  XOperandCount;
};

struct tagEXFUNINFO {
	uint32_t hItemLibrary; // if the value is 0x00, load function pointer from cdlli72.dll's _INT_LOCALS array. AccessKey contains the array index in this case.
	uint32_t hItemFun;
	uint32_t AccessKey;
	uint32_t lpProc;
	uint8_t bReturnType;
	uint8_t flags;
};

struct tagINTFUNHITEMS {
	uint32_t hItemDoActions;
	uint32_t hItemParameters;
	uint32_t hItemLocals;
	uint32_t nReturnDataType;
	uint32_t nStackSizeVars;
	uint32_t nStackSiteParams;
};

struct SalNumber {
	uint8_t size;
	uint8_t payload[0x18];
};

#pragma pack(pop)   /* restore original alignment from stack */



#endif /* OUTLINE_DECS_HPP_ */
