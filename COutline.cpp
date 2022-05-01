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

#include "COutline.hpp"
#include "helper.hpp"
#include "item.hpp"
#include "commandline_args.hpp"
#include <exception>
#include <string.h>
#include <time.h>
#include <locale.h>
#ifdef __unix__ 
#include <iconv.h> // utf16-conversion of filename when dumping resources
#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
#include <windows.h> // utf16-conversion of filename when dumping resources
#else
#error "neither Unix nor Windows environment defined"
#endif

uint64_t COutline::insert_item(uint32_t seginf) {
	if (!seginf) {
		return 0;
	}
	if (seginf > this->outline->seg_inf_limit) {
		return 0;
	}
	if (!tag_oseg[seginf] || !hand_table[seginf]) {
		return 0;
	}

	tag_oseg[seginf]->seghd_maxUsedHandle++;
	struct HandTable* newht = (struct HandTable*)realloc(hand_table[seginf],sizeof(struct HandTable)*(tag_oseg[seginf]->seghd_maxUsedHandle+1));
	if (!newht) {
		tag_oseg[seginf]->seghd_maxUsedHandle--;
		return 0;
	}
	hand_table[seginf] = newht;
	newht[tag_oseg[seginf]->seghd_maxUsedHandle].size = ((HANDTABLE_ITEMSIZE_MASK+1) | (1+(sizeof(struct tagITEM)+4-1)/4));
	newht[tag_oseg[seginf]->seghd_maxUsedHandle].handle_data = alloc<struct tagITEM*>(((newht[tag_oseg[seginf]->seghd_maxUsedHandle].size&HANDTABLE_ITEMSIZE_MASK)-1)*4);
	newht[tag_oseg[seginf]->seghd_maxUsedHandle].memory = alloc<struct RuntimeMemory*>(sizeof(struct RuntimeMemory));
	return ((uint64_t)tag_oseg[seginf]->seghd_maxUsedHandle) | (((uint64_t)seginf)<<ITEM_ID_WIDTH);
}

COutline::COutline(FILE* handle) : handle(handle) {
	if (!handle) {
		throw new std::is_null_pointer<FILE*>();
	}
	long int offset = 0;

	// search for MAGIC BYTE sequence and read header
	/**
	 * Skipped data in PE file should only contain:
	 * * Manifest
	 * * App Icon
	 * * Version Information
	 * * DLL dependencies
	 * * Machine code that calls cdlliXX.dll, which then runs the Outline
	 */
	try {
		while (true) {
			fseek_or_throw(handle, offset);
			fread_or_throw(&this->file_hdr, sizeof(struct FileHdr), handle);
			if (this->file_hdr.signature == TD_SIGNATURE) {
				break;
			}
			offset += 0x200;
			continue;
		}
	}catch(...){
		fprintf(stderr,"error: did not find magic bytes while scanning the input file\n");
		fprintf(stderr,"maybe not a Gupta Team Developer binary?\n");
		exit(1);
	}

	if (is_verbose()) {
		printf("Offset: 0x%08lx\n",offset);
	}

	if (this->file_hdr.version < VERSION_TD51) {
		fprintf(stderr,"error: binaries created with TD before 5.1 are not supported (yet)\n");
		exit(1); // 64bit not supported
	}

#ifndef TDx64
	if (this->file_hdr.flags & FLAG_IS_64BIT) {
		if (is_verbose()) {
			printf("stopped 32bit loading of binary with 64bit flag set\n");
		}
		return;
	}
#endif

	// read outline
	this->outline = alloc<struct Outline*>(this->file_hdr.outline_alloc);
	fread_or_throw(this->outline, this->file_hdr.outline_alloc, handle);
	if (this->outline->outline_alloc != this->file_hdr.outline_alloc) {
		fprintf(stderr,"warning: size mismatch of outline structure\n");
	}
	this->outline->outline_alloc = this->file_hdr.outline_alloc;

	// read symbol hash table
	fread_or_throw(&this->symbol_hash, sizeof(SymbolHash), handle);

	// read list of forms/Windows that should be loaded on startup
	if (this->file_hdr.run_only == RUN_ONLY) {
#ifdef TDx64
		uint64_t form_item;
#else
		uint32_t form_item;
#endif
		do {
			fread_or_throw(&form_item, sizeof(form_item), handle);
			/*
			if (form_item) {
				// TODO: store list of active windows somewhere...?
			}
			*/
		}while(form_item);
	}

	// read CGAXLibInfo [see cdlli72.dll:0x1040a39a]
	// FileHdr: uint32_t ax_lib_info_offset;
	// Length: see FileHdr: uint32_t ax_lib_info_len;
	if (this->file_hdr.ax_lib_info_offset && this->file_hdr.ax_lib_info_len) {
		this->ax_lib_info = alloc<char*>(this->file_hdr.ax_lib_info_len);
		fseek_or_throw(handle,offset+this->file_hdr.ax_lib_info_offset);
		fread_or_throw(this->ax_lib_info, this->file_hdr.ax_lib_info_len, handle);
	}

	// read CClassRelationships [see cdlli72.dll:0x1040a3d3]
	// CCLassRelationships: uint32_t, (size 4/ptr:)CArray*<CClsRelation,CClsRelation> clsRelationList, uint32_t bool_Compacted
	// CClsRelation: uint32_t, HItem*, (size 4/ptr:)CArray*<CClsRelation,CClsRelation> devivedList
	if (this->file_hdr.class_relationship_offset && this->file_hdr.class_relationship_length) {
		this->class_relationships = alloc<char*>(this->file_hdr.class_relationship_length);
		fseek_or_throw(handle,offset+this->file_hdr.class_relationship_offset);
		fread_or_throw(this->class_relationships, this->file_hdr.class_relationship_length, handle);
	}

	// read co_class_list (seems only to be present if "RUNO" flag is set)
	if (this->file_hdr.co_class_list_offset && this->file_hdr.co_class_list_len) {
		this->co_class_list = alloc<char*>(this->file_hdr.co_class_list_len);
		fseek_or_throw(handle,offset+this->file_hdr.co_class_list_offset);
		fread_or_throw(this->co_class_list, this->file_hdr.co_class_list_len, handle);
	}

	if (is_verbose()) {
		// seems to be always ZERO...
		printf("co_class_interface_map_len: -> 0x%08x\n",this->file_hdr.co_class_interface_map_len);
		printf("hResInfo: -> 0x%04x\n",this->outline->hResInfo); // item_id of hResInfo struct
		printf("hStringTables: -> 0x%08x\n",this->outline->h_string_tables);
		printf("\n");
	}

	// TODO: CGComServerInfo may follow?? [cdlli72.dll:0x1040a4ad]

	// process all items from the HItem-Array following the Outline struct
	// each of them may refer to a HandTable
	this->hand_table = alloc<struct HandTable**>(sizeof(void*)*(outline->seg_inf_limit+1));
	this->tag_oseg = alloc<struct tagOSEG**>(sizeof(void*)*(outline->seg_inf_limit+1));
	uint64_t item_id = 1;
	if (is_verbose()) {
		oputs("===== HITEMS =====\n");
	}
	uint32_t items_dumped = 0;
	for (
			struct HItem* item = this->outline->data;
			(char*)item + sizeof(struct HItem) - (char*)this->outline <= this->outline->outline_alloc
					&& item - this->outline->data <= this->outline->seg_inf_limit;
			item++
	) {
		this->tag_oseg[item_id] = 0;
		if (!item->offset || !item->size) {
			item->size = 0;
			item->offset = 0;
			item_id++;
			continue; // better use "break;" instead?
		}

		this->tag_oseg[item_id] = alloc<struct tagOSEG*>(item->size);
		fseek_or_throw(handle,offset+item->offset);

		if (is_verbose()) {
			oprintf("item 0x%04x: size %u, flags 0x%08x\n",item_id,item->size,item->flags);
		}

		uint32_t compression_method = ((item->flags & 0x6) >> 1);
		if (item->flags & 0x100) {
			compression_method = 2;
		}

		switch (compression_method) {
		case 0:
			// uncompressed
			fread_or_throw(this->tag_oseg[item_id], item->size, handle);
			break;
		case 1:
			// not supported (see below)
			break;
		case 2:
			// OsReadExplode
			if (this->OsDeCompress(item->size, this->tag_oseg[item_id], -1)!=item->size) {
				throw new std::exception();
			}
			break;
		case 3:
			if (this->OsReadFast(item->size, (char*)this->tag_oseg[item_id])!=item->size) {
				throw new std::exception();
			}
			break;
		}
		if (compression_method == 1) {
			// TODO case 1 in switch statement [cdlli72.dll, offset 0x10351a17]
			fprintf(stderr,"unsupported flag 0x%08x at item %u. skipping item (%u bytes)\n",item->flags,item_id,item->size);
			item_id++;
			continue;
		}

		if (item->size < sizeof(struct tagOSEG)) {
			fprintf(stderr,"warning:item 0x%04x is smaller than sizeof(tagOSEG)\n",item_id);
		}else{
			if (this->tag_oseg[item_id]->ohSegInf != item_id) {
				fprintf(stderr,"warning: ohSegInf 0x%04x doesn't match item-id 0x%04x\n",this->tag_oseg[item_id]->ohSegInf,item_id);
			}
		}

		if (item->flags & ITEM_HAS_HANDLE_TABLE) {
			if (get_item_dump_dir()) {
				size_t s = strlen(get_item_dump_dir());
				char* fn = alloc<char*>(s+16);
				char slash[2] = {0x00, 0x00};
				if (s > 0 && get_item_dump_dir()[s-1] != '/') {
					slash[0] = '/';
				}
				sprintf(fn,"%s%sitem_%04x.bin",get_item_dump_dir(),slash,item_id);
				FILE* fh = fopen(fn,"wb");
				if (fh) {
					items_dumped++;
					fwrite(this->tag_oseg[item_id],item->size,1,fh);
					fclose(fh);
				}else{
					fprintf(stderr,"cannot write to file %s\n",fn);
				}
				free(fn);
			}
			this->hand_table[item_id] = create_handtable(this->tag_oseg[item_id], item_id);
		}

		if (get_item_dump_dir() && (item->flags & ITEM_IS_RESOURCE)) {
			// dump the file...
			size_t s = strlen(get_item_dump_dir());
			char* fn = alloc<char*>(s+20);
			char slash[2] = {0x00, 0x00};
			if (s > 0 && get_item_dump_dir()[s-1] != '/') {
				slash[0] = '/';
			}
			sprintf(fn,"%s%sresource_%04x.bin",get_item_dump_dir(),slash,item_id);
			FILE* res = fopen(fn,"wb");
			if (res) {
				items_dumped++;
				fwrite(this->tag_oseg[item_id], item->size, 1, res);
				fclose(res);
			}else{
				fprintf(stderr,"cannot write to file %s\n",fn);
			}
			free(fn);
		}

		item_id++;
	}

	if (get_item_dump_dir()) {
		printf("%u item%s dumped into directory %s\n",items_dumped,items_dumped==1?"":"s",get_item_dump_dir());
	}

	this->init_symbol_lookup();

	// read HStringTable /// seems to be padded to an offset modulo 4 == 0
	this->string_table = 0;
	if (this->outline->h_string_tables) {
		fseek_or_throw(handle,offset+this->outline->h_string_tables);
		if (file_hdr.version >= VERSION_TD70) {
			fread_or_throw(&this->cmphdr, sizeof(struct CompressionHeader), handle);
		}else{
			fread_or_throw(&this->cmphdr, sizeof(struct CompressionHeader)-2, handle);
		}
		if (this->cmphdr.uncomp_size != 0) {
			this->str_data = alloc<char*>(this->cmphdr.uncomp_size);
			this->OsReadFast(this->cmphdr.uncomp_size, str_data);
			this->string_table = (struct StringTable*)(&str_data[this->cmphdr.hstring_size]);
		}
	}

	if (is_verbose() || get_resource_dump_dir()) {
		uint32_t resources_dumped = 0;
		if (this->outline->hResInfo) {
			if (is_verbose()) {
				oputs("\n===== RESOURCES =====\n");
			}
			HItem* item = &this->outline->data[this->outline->hResInfo-1];
			if (!(item->flags & ITEM_IS_RESOURCE)) {
				fprintf(stderr,"error: resource flag not set for hResInfo item\n");
			}else if (item->size < sizeof(struct tagOSEG) + sizeof(struct ResInfo)){
				fprintf(stderr,"error: size of hResInfo item too small\n");
			}else{
				// TODO: check if item->size is large enough to hold all references...
				uint8_t* data = (uint8_t*)this->tag_oseg[this->outline->hResInfo];
				struct ResInfo* info = (struct ResInfo*)&data[sizeof(struct tagOSEG)];
				for (int i=0; i<30; i++) {
					uint16_t it = info->res_hash_names[i];
					while (it) {
						if (it + sizeof(uint16_t) > item->size) {
							break;
						}
						uint16_t ptr = *(uint16_t*)&data[it];
						if (!ptr || ptr + sizeof(struct tagRESNAME) > item->size) {
							break;
						}
						struct tagRESNAME* rn = (struct tagRESNAME*)&data[ptr];

						uint16_t resseg = 0;
						ptr = 0;
						if (rn->hResSeg && rn->hResSeg <= item->size + sizeof(uint16_t)) {
							ptr = *(uint16_t*)&data[rn->hResSeg];
						}
						if (ptr && ptr + sizeof(struct tagRESSEG) <= item->size) {
							struct tagRESSEG* rs = (struct tagRESSEG*)&data[ptr];
							resseg = rs->hSegInf;
						}

						if (is_verbose()) {
							oprintf("%04x.%04x: ",resseg, rn->hResHdr);
							print_utf16(rn->szFilename);
							oputs("\n");
						}

						// extract data
						if (get_resource_dump_dir() && resseg && resseg <= this->outline->seg_inf_limit) {
							HItem* item = &this->outline->data[resseg-1];
							if (!(item->flags & ITEM_IS_RESOURCE)) {
								fprintf(stderr,"error: resource flag not set for hResInfo item\n");
							}else{
								uint8_t* data = (uint8_t*)this->tag_oseg[resseg];
								struct ResHdr* reshdr = NULL;
								if (!rn->hResHdr && item->size >= sizeof(tagOSEG)+sizeof(ResHdr)) {
									reshdr = (struct ResHdr*)&data[sizeof(struct tagOSEG)];
								}else if (rn->hResHdr && item->size >= (uint32_t)rn->hResHdr+2){
									uint16_t ptr = *(uint16_t*)&data[rn->hResHdr];
									if (ptr && item->size >= ptr + sizeof(struct ResHdr)) {
										reshdr = (struct ResHdr*)&data[ptr];
									}
								}
								if (!reshdr) {
									fprintf(stderr,"invalid hResInfo ptr\n");
								}else{
									// decompress resource data (if necessary)
									char* resdata = NULL;
									switch (reshdr->compression_type) {
									case 0:
										// copy
										if (reshdr->uncompressed_len != reshdr->compressed_len) {
											fprintf(stderr,"size mismatch for uncompressed resource %04x.%04x\n",resseg, rn->hResHdr);
											break;
										}
										resdata = (char*)reshdr->data;
										break;
									case 2:
										// OsDeCompress
										resdata = alloc<char*>(reshdr->uncompressed_len);
										if (reshdr->uncompressed_len != this->OsDeCompress(reshdr->uncompressed_len, resdata, reshdr->compressed_len, reshdr->data)) {
											fprintf(stderr,"size mismatch for compressed resource %04x.%04x\n",resseg, rn->hResHdr);
										}
										break;
									case 1:
										// call to 16-bit swcomp.exe
										fprintf(stderr,"unsupported outdated compression method (MS-DOS PKWARE 1.02) in resource %04x.%04x\n", resseg, rn->hResHdr);
										break;
									default:
										// unknown compression method
										fprintf(stderr,"unknown compression method 0x%04x in resource %04x.%04x\n",reshdr->compression_type, resseg, rn->hResHdr);
										break;
									}

									// write to file
									if (resdata) {
										// open question: how is the checksum computed? can/should we verify it?
										char* resfilename = NULL;
										size_t filename_len = strlen_utf16(rn->szFilename);
										size_t path_len = strlen(get_resource_dump_dir());
										char slash[2] = {0x00, 0x00};
										if (path_len > 0 && get_resource_dump_dir()[path_len-1] != '/') {
											slash[0] = '/';
											path_len++;
										}
										if (filename_len) {
											size_t max_out_len = 2*filename_len+1;
											resfilename = alloc<char*>(path_len+max_out_len);
											sprintf(resfilename,"%s%s",get_resource_dump_dir(),slash);
											char* out_buffer = resfilename+path_len;
											char16_t* fn = rn->szFilename;
#ifdef __unix__ 
											iconv_t str_convert = iconv_open("UTF-8", "UTF-16LE");
											iconv(str_convert, (char**)&fn, &filename_len, &out_buffer, &max_out_len);
											iconv_close(str_convert);
#else
											out_buffer += WideCharToMultiByte(CP_ACP, 0, (LPCWCH)fn, (int)filename_len/2, out_buffer, (int)max_out_len, NULL, NULL);
#endif
											*out_buffer = 0;
										}else{
											resfilename = alloc<char*>(path_len+22);
											sprintf(resfilename,"%s%sresource_%04x%04x.bin", get_resource_dump_dir(), slash, resseg, rn->hResHdr);
										}
										if (is_verbose()) {
											FILE* resfile = fopen(resfilename,"rb");
											if (resfile) {
												fprintf(stderr,"dumping resource %04x%04x to file %s: already exists\n",resseg, rn->hResHdr,resfilename);
												fclose(resfile);
											}
										}
										FILE* resfile = fopen(resfilename,"wb");
										if (resfile) {
											resources_dumped++;
											fwrite(resdata, reshdr->uncompressed_len, 1, resfile);
											fclose(resfile);
										}else{
											fprintf(stderr,"cannot dump resource %04x%04x to file %s\n",resseg, rn->hResHdr,resfilename);
										}
										free(resfilename);
									}

									if (resdata && reshdr->compression_type == 2) {
										free(resdata);
									}
								}
							}
						}
						it = rn->hNext;
					}
				}
			}
		}
		if (get_resource_dump_dir()) {
			printf("%u resource%s dumped into directory %s\n",resources_dumped,resources_dumped==1?"":"s",get_resource_dump_dir());
		}
		if (is_verbose()) {
			oputs("\n");
		}
	}
}

uint32_t COutline::save(FILE* handle) {
	long int offset = ftell(handle);

	// modify FileHdr
	FileHdr hdr;
	memcpy(&hdr,&this->file_hdr,sizeof(FileHdr));
	hdr.run_only = 0x00000000; // .app file
	hdr.flags &= ((~FLAG_IS_DLL) & (~FLAG_IS_EXE)
			& (~FLAG_VISIBLE_H_ITEMS) & (~FLAG_COMPILED)); // .app file
	hdr.class_relationship_length = 0; // .app file
	hdr.co_class_list_offset = 0; // .app file
	hdr.co_class_interface_map_len = 0; // .app file

	// adapt offsets in FileHdr
	uint32_t off = sizeof(FileHdr) + hdr.outline_alloc + sizeof(SymbolHash);
	if (hdr.ax_lib_info_len) {
		hdr.ax_lib_info_offset = off;
		off += hdr.ax_lib_info_len;
	}else{
		hdr.ax_lib_info_offset = 0;
	}
	if (hdr.class_relationship_length) {
		hdr.class_relationship_offset = off;
		off += hdr.class_relationship_length;
	}else{
		hdr.class_relationship_offset = 0;
	}
	if (hdr.co_class_list_len) {
		hdr.co_class_list_offset = off;
		off += hdr.co_class_list_len;
	}else{
		hdr.co_class_list_offset = 0;
	}

	hdr.outline_alloc = sizeof(Outline) + this->outline->seg_inf_limit*sizeof(HItem);
	Outline* outl = alloc<Outline*>(hdr.outline_alloc);
	memset(outl,0,hdr.outline_alloc);
	memcpy(outl,this->outline,sizeof(Outline));
	outl->outline_alloc = hdr.outline_alloc;
	outl->h_string_tables = 0; // remove HStringTable


	outl->flags &= ((~OFLAG_APP_IS_COMPILED) &
			(~OFLAG_APP_CHANGED) & (~OFLAG_APP_SAVE_COMPILED) &
			(~OFLAG_FILE_IS_EXE) & (~OFLAG_FILE_IS_DLL) &
			(~OFLAG_UNTITLED) & (~OFLAG_RUN_ONLY) &
			(~OFLAG_CHILD_LINE_COUNTS_ADDED));


	// write header data
	fwrite(&hdr, sizeof(FileHdr), 1, handle);
	fwrite(outl, outl->outline_alloc, 1, handle);

	// write empty symbol hash for .app file
	SymbolHash s;
	memset(&s,0,sizeof(SymbolHash));
	fwrite(&s, sizeof(SymbolHash),1,handle);

	// write some generic information...
	fwrite(this->ax_lib_info, hdr.ax_lib_info_len, 1, handle);

	if (hdr.class_relationship_length) {
		fwrite(this->class_relationships, hdr.class_relationship_length, 1, handle);
	}
	if (hdr.co_class_list_len) {
		fwrite(this->co_class_list, hdr.co_class_list_len, 1, handle);
	}

	// write HItem / tagOSEG data
	for (uint32_t i = 1; i<=this->outline->seg_inf_limit; i++) {
		HItem item;
		memcpy(&item,&this->outline->data[i-1],sizeof(HItem));

		item.offset = off;
		item.flags &= (~0x106); // uncompressed

		struct tagOSEG* oseg = NULL;

		if (!this->tag_oseg[i] && item.size) {
			fprintf(stderr,"unexpected NULL pointer while saving item 0x%04x of size 0x%04x with flags 0x%08x...\n",i,item.size,item.flags);
			item.size = 0;
		}else if (item.size) {
			oseg = this->tag_oseg[i];
		}

		if ((item.flags & ITEM_HAS_HANDLE_TABLE) && item.size) {
			// rebuild HandTable: realloc this->tag_oseg[i]; update item.size

			// determine needed heap size
			uint32_t size = 0;
			if (this->hand_table[i]) {
				for (uint16_t j=1; j<=this->tag_oseg[i]->seghd_maxUsedHandle; j++) {
					if (this->hand_table[i][j].handle_data) {
						if ((this->hand_table[i][j].size & HANDTABLE_ITEMSIZE_MASK) < (sizeof(struct tagHEAPBLK)+4-1)/4) {
							fprintf(stderr,"error: handtable[0x%04x][0x%04x].size too small\n",i,j);
							size += (sizeof(struct tagHEAPBLK)+4-1)/4;
						}else{
							size += (this->hand_table[i][j].size & HANDTABLE_ITEMSIZE_MASK);
						}
					}else{
						this->hand_table[i][j].size = 0;
					}
				}
			}
			uint32_t header_size = (sizeof(struct tagOSEG) + 4-1)/4;
			uint32_t footer_size = (sizeof(struct tagHEAPBLK)+4-1)/4 + 1;

			// allocate memory and update item size
			item.size = 4*(size + header_size + footer_size);
			oseg = alloc<struct tagOSEG*>(item.size);
			if (!oseg) {
				throw new std::bad_alloc();
			}

			// fill tagOSEG header
			memcpy(oseg,this->tag_oseg[i],sizeof(struct tagOSEG));
			oseg->seghd_shStartDynamic = header_size*4;

			// copy data from handtable items to tagOSEG body
			uint64_t offset = header_size;
			if (this->hand_table[i]) {
				for (uint32_t j=1; j<=this->tag_oseg[i]->seghd_maxUsedHandle; j++) {
					if (this->hand_table[i][j].handle_data) {
						if (offset + (sizeof(struct tagHEAPBLK)+4-1)/4 > size + header_size) {
							fprintf(stderr,"size counting failure\n");
							break;
						}
						struct tagHEAPBLK* ptr = (struct tagHEAPBLK*)&((char*)oseg)[4*offset];
						ptr->handle_id = j;
						ptr->value = this->hand_table[i][j].size;
						uint32_t copy_size = 0;
						if (this->hand_table[i][j].size & (HANDTABLE_ITEMSIZE_MASK+1)) {
							copy_size = this->hand_table[i][j].handle_data->data_length + sizeof(struct tagITEM);
						}else{
							copy_size = (this->hand_table[i][j].size & HANDTABLE_ITEMSIZE_MASK) * 4;
							if (copy_size < sizeof(struct tagHEAPBLK)) {
								copy_size = sizeof(struct tagHEAPBLK);
								fprintf(stderr,"item size failure\n");
								break;
							}
							copy_size -= sizeof(struct tagHEAPBLK);
						}
						if (copy_size+sizeof(struct tagHEAPBLK) > 4*(this->hand_table[i][j].size & HANDTABLE_ITEMSIZE_MASK)) {
							fprintf(stderr,"size counting failure\n");
							continue;
						}
						memcpy(&ptr->data,this->hand_table[i][j].handle_data,copy_size);

						// correct item flags -- note that only items with flag (HANDTABLE_ITEMSIZE_MASK+1) set have a tagITEM header structure
						if ((this->hand_table[i][j].size & (HANDTABLE_ITEMSIZE_MASK+1))
								&& (this->hand_table[i][j].size & (HANDTABLE_ITEMSIZE_MASK))*4 >= sizeof(struct tagHEAPBLK) + sizeof(struct tagITEM)) {

							if ((((struct tagITEM*)&ptr->data)->flags & 0x00ff0000)) {
								// count number of lines and set line number flag (display height)
								((struct tagITEM*)&ptr->data)->flags &= 0xff00ffff;
								size_t lines = 1;
								ItemBody* str = CItem::get_itembody(this, (((uint64_t)i<<ITEM_ID_WIDTH)|(uint64_t)j), 0x01);
								if (str) {
									//str->size
									lines += count_linebreaks((const char16_t*)str->data,str->size);
								}
								if (lines > 0xff) {
									// FIXME: handle items with huge amount of lines (overflow)
									lines = 0xff;
								}
								((struct tagITEM*)&ptr->data)->flags |= (lines<<16);
							}

							// 0x100-flag seems to indicate presence of compiled code (0x09) itembody -> remove flag
							((struct tagITEM*)&ptr->data)->flags &= 0xfffffeff;

							if (is_remove_importflag()) {
								// remove 0x400-flag (import flag)
								((struct tagITEM*)&ptr->data)->flags &= 0xfffffbff;
							}
						}

						offset += (this->hand_table[i][j].size & HANDTABLE_ITEMSIZE_MASK);
						if (offset > size + header_size) {
							fprintf(stderr,"size counting failure\n");
						}
					}
				}
			}
			// footer:
			//   1.: size==0-item (e.g.: 0x00 0x00 0x00 0x00 item)
			//   2.: 0x83 0x7f 0x00 0x00 item (for whatever reason...)
			struct tagHEAPBLK* ptr = (struct tagHEAPBLK*)&((char*)oseg)[4*offset];
			memset(ptr,0,sizeof(struct tagHEAPBLK));
			ptr->data[0] = 0x83;
			ptr->data[1] = 0x7f;
			ptr->data[2] = 0x00;
			ptr->data[3] = 0x00;

		}else if ((item.flags & ITEM_IS_RESOURCE) && item.size){
			// just copy
		}else if ((item.flags & ITEM_IS_SYMBOL_ARRAY) && item.size){
			// Symbol entries: unused for decompiled app --> set to size zero (don't reorder items since it's too complicated)
			item.size = 0;
			item.offset = 0;
			item.flags = 0;
		}else if (item.size){
			// unknown item type...
		}

		if (item.size && oseg) {
			fseek(handle, offset+off, SEEK_SET);
			fwrite(oseg,item.size,1,handle);
			off += item.size;
		}

		if (oseg && (item.flags & ITEM_HAS_HANDLE_TABLE) && item.size) {
			free(oseg);
		}

		uint32_t hitem_off = sizeof(FileHdr) + sizeof(Outline) + (i-1)*sizeof(HItem);
		fseek(handle, offset + hitem_off, SEEK_SET);
		fwrite(&item,sizeof(HItem),1,handle);
	}

	// add padding before HStringTable starts
	fseek(handle, offset + off, SEEK_SET);
	uint32_t padding = (4 - (off % 4)) % 4;
	uint32_t padd = 0x00;
	fwrite(&padd, padding, 1, handle);
	off += padding;

	return off;
}

bool COutline::add_variable(uint64_t item_id, enum varscope scope, uint16_t offset, uint64_t reference) {
	if (!item_id) {
		return false;
	}
	uint32_t item = (item_id>>ITEM_ID_WIDTH);
	if (item == 0 || item > this->outline->seg_inf_limit) {
		return false;
	}
	uint32_t handle = (item_id&((1LL<<ITEM_ID_WIDTH)-1));
	if (handle == 0 || this->tag_oseg[item] == 0 || this->hand_table == 0 || this->hand_table[item] == 0 || handle > this->tag_oseg[item]->seghd_maxUsedHandle) {
		return false;
	}
	if (!this->hand_table[item][handle].memory) {
		this->hand_table[item][handle].memory = alloc<struct RuntimeMemory*>(sizeof(struct RuntimeMemory));
		if (!this->hand_table[item][handle].memory) {
			throw std::bad_alloc();
		}
	}
	struct RuntimeMemory* rms = this->hand_table[item][handle].memory;
	if (!rms->scope[scope].item_id) {
		rms->scope[scope].item_id = alloc<uint64_t*>(sizeof(uint64_t)*(offset+1));
		if (!rms->scope[scope].item_id) {
			throw std::bad_alloc();
		}
		rms->scope[scope].current_size = offset+1;
	}else if (rms->scope[scope].current_size <= offset) {
		uint64_t* newmem = (uint64_t*)realloc(rms->scope[scope].item_id,sizeof(uint64_t)*(offset+1));
		if (!newmem) {
			throw std::bad_alloc();
		}
		rms->scope[scope].item_id = newmem;
		memset(newmem+rms->scope[scope].current_size,0,sizeof(uint64_t)*(offset+1-rms->scope[scope].current_size));
		rms->scope[scope].current_size = offset+1;
	}
	rms->scope[scope].item_id[offset] = reference;
	return true;
}

uint64_t COutline::lookup_variable(uint64_t item_id, enum varscope scope, uint16_t offset, bool print_namespace) {
	struct RuntimeMemoryScope* rms = get_memory(item_id, scope);
	if (!rms) {
		return 0;
	}
	uint32_t off = offset;
	if (!rms->current_size) {
		return 0;
	}
	if (rms->current_size <= off) {
		off = rms->current_size - 1;
	}
	do {
		if (rms->item_id[off]) {
			break;
		}
		if (!off) {
			return 0;
		}
		off--;
	}while(1);

	if (get_memory(rms->item_id[off], scope)) {
		if (print_namespace) {
			const char16_t* _namespace = this->symbol_lookup(rms->item_id[off]);
			if (_namespace) {
				print_utf16(_namespace);
				oputs(".");
			}
		}
		return lookup_variable(rms->item_id[off], scope, offset-off);
	}else if (scope == varscope::CURRENT_FORM && get_memory(rms->item_id[off], varscope::CURRENT_OBJECT)) {
		return lookup_variable(rms->item_id[off], varscope::CURRENT_OBJECT, offset-off);
	}else if (offset == off) {
		return rms->item_id[off];
	}else{
		return 0;
	}
}

void COutline::add_class_item(uint64_t class_id, uint64_t item_id) {
	if (!this->class_map.item) {
		this->class_map.item = alloc<uint64_t*>(sizeof(uint64_t)*(class_id+1));
		this->class_map.size = class_id+1;
	}else if (this->class_map.size <= class_id) {
		uint64_t* tmp = (uint64_t*)realloc(this->class_map.item, sizeof(uint64_t) * (class_id + 1));
		if (!tmp) {
			throw new std::bad_alloc();
		}
		this->class_map.item = tmp;
		for (uint64_t i=this->class_map.size;i<class_id+1;i++) {
			this->class_map.item[i] = 0;
		}
		this->class_map.size = class_id+1;
	}
	this->class_map.item[class_id] = item_id;
}

uint64_t COutline::get_class_item(uint64_t class_id) {
	if (class_id < this->class_map.size) {
		return this->class_map.item[class_id];
	}
	return 0;
}

void COutline::add_dynalib_var(uint16_t libsal, uint16_t ordinal, uint64_t item) {
	if (is_verbose()) {
		oprintf("HLIBSAL 0x%04x, DYNALIB_ORDINAL 0x%04x: item 0x%08x\n",libsal,ordinal,item);
	}

	// allocate enough space for libsal
	if (!this->dynamlib_map.ordinal_map) {
		this->dynamlib_map.ordinal_map = (struct OrdinalMap*)alloc<char*>(sizeof(struct OrdinalMap)*(libsal+1));
		this->dynamlib_map.size = libsal+1;
	}else if (this->dynamlib_map.size <= libsal) {
		struct OrdinalMap* tmp = (struct OrdinalMap*)realloc(this->dynamlib_map.ordinal_map, sizeof(struct OrdinalMap) * (libsal + 1));
		if (!tmp) {
			throw std::bad_alloc();
		}
		this->dynamlib_map.ordinal_map = tmp;
		for (uint32_t i=this->dynamlib_map.size;i<(uint32_t)libsal+1;i++) {
			this->dynamlib_map.ordinal_map[i].size = 0;
			this->dynamlib_map.ordinal_map[i].item = NULL;
		}
		this->dynamlib_map.size = libsal+1;
	}

	// allocate enough space for ordinal
	if (!this->dynamlib_map.ordinal_map[libsal].item) {
		this->dynamlib_map.ordinal_map[libsal].item = alloc<uint64_t*>(sizeof(uint64_t)*(ordinal+1));
		if (!this->dynamlib_map.ordinal_map[libsal].item) {
			throw std::bad_alloc();
		}
		this->dynamlib_map.ordinal_map[libsal].size = ordinal+1;
	}else if (this->dynamlib_map.ordinal_map[libsal].size <= ordinal) {
		uint64_t* tmp = (uint64_t*)realloc(this->dynamlib_map.ordinal_map[libsal].item, sizeof(uint64_t) * (ordinal + 1));
		if (!tmp) {
			throw std::bad_alloc();
		}
		this->dynamlib_map.ordinal_map[libsal].item = tmp;
		for (uint32_t i=this->dynamlib_map.ordinal_map[libsal].size;i<(uint32_t)ordinal+1;i++) {
			this->dynamlib_map.ordinal_map[libsal].item[i] = 0;
		}
		this->dynamlib_map.ordinal_map[libsal].size = ordinal+1;
	}
	this->dynamlib_map.ordinal_map[libsal].item[ordinal] = item;
}

uint64_t COutline::get_dynalib_var(uint16_t libsal, uint16_t ordinal) {
	if (!this->dynamlib_map.ordinal_map) {
		return 0;
	}
	if (this->dynamlib_map.size <= libsal) {
		return 0;
	}
	if (!this->dynamlib_map.ordinal_map[libsal].item) {
		return 0;
	}
	if (this->dynamlib_map.ordinal_map[libsal].size <= ordinal) {
		return 0;
	}
	return this->dynamlib_map.ordinal_map[libsal].item[ordinal];
}

uint32_t COutline::find_siblings_of_type_and_run(void (*callback)(class COutline*, uint64_t, void*), void* param, uint64_t item, const uint16_t* type, bool only_one_match) {
	uint32_t callbacks = 0;
	if (!callback) {
		return 0;
	}
	while (item) {
		tagITEM* p_item = this->get_item(item);
		if (!p_item) {
			return 0;
		}
		uint64_t deref = this->item_pointer_dereference(item);
		if (deref && deref != item) {
			callbacks += this->find_siblings_of_type_and_run(callback,param,deref,type,only_one_match);
			if (only_one_match && callbacks) {
				return callbacks;
			}
		}else if (!type) {
			callback(this, item, param);
			callbacks++;
			if (only_one_match) {
				return callbacks;
			}
		}else{
			for (uint16_t i=0; type[i]; i++) {
				if (p_item->type == type[i]) {
					callback(this, item, param);
					callbacks++;
					if (only_one_match) {
						return callbacks;
					}
				}
			}
		}
		item = this->next_item(item);
	}
	return callbacks;
}

uint32_t COutline::find_children_of_type_and_run(void (*callback)(class COutline*, uint64_t, void*), void* param, uint64_t item, const uint16_t* type, bool only_one_match) {
	if (!item) {
		return 0;
	}
	if (!callback) {
		return 0;
	}
	tagITEM* p_item = this->get_item(item);
	if (!p_item) {
		return 0;
	}
	uint64_t deref = this->item_pointer_dereference(item);
	if (deref && deref != item) {
		return this->find_children_of_type_and_run(callback,param,deref,type,only_one_match);
	}
	uint64_t child = this->child_item(item);
	if (child) {
		return find_siblings_of_type_and_run(callback,param,child,type,only_one_match);
	}
	return 0;
}

uint64_t COutline::top_item() {
	return outline->hItemTop;
}

uint64_t COutline::item_pointer_dereference(uint64_t item) {
	tagITEM* p_item = get_item(item);
	if (!p_item) {
		return 0;
	}
	if (p_item->type == Item::Type::POINTER && p_item->data_length >= item_bodies[0x32].size && p_item->data[0] == 0x32) {
		// is pointer
		uint64_t ptr = 0;
		memcpy(&ptr,&p_item->data[1],item_bodies[0x32].size);
		return this->item_pointer_dereference(ptr);
	}
	return item;
}

uint64_t COutline::next_item(uint64_t item_id){
	tagITEM* item = this->get_item(item_id);
	if (!item) {
		return 0;
	}
	uint32_t sibling = item->next_sibling;
	if (!sibling) {
		return 0;
	}
	return (sibling | (item_id&(((1LL<<ITEM_ID_WIDTH)-1LL)<<ITEM_ID_WIDTH)));
}

uint64_t COutline::child_item(uint64_t item_id) {
	tagITEM* item = this->get_item(item_id);
	if (!item) {
		return 0;
	}
	uint32_t child = item->first_child;
	if (!child) {
		return 0;
	}
	return (child | (item_id&(((1LL<<ITEM_ID_WIDTH)-1LL)<<ITEM_ID_WIDTH)));
}

tagITEM* COutline::get_item(uint64_t item_id) {
	if (!item_id) {
		return NULL;
	}
	uint32_t item = (item_id>>ITEM_ID_WIDTH);
	if (item == 0 || item > this->outline->seg_inf_limit) {
		return NULL;
	}
	uint32_t handle = (item_id&((1LL<<ITEM_ID_WIDTH)-1LL));
	if (handle == 0 || this->tag_oseg[item] == 0 || this->hand_table == 0 || this->hand_table[item] == 0 || handle > this->tag_oseg[item]->seghd_maxUsedHandle) {
		return NULL;
	}
	return this->hand_table[item][handle].handle_data;
}

struct RuntimeMemoryScope* COutline::get_memory(uint64_t item_id, varscope scope) {
	if (!item_id) {
		return NULL;
	}
	uint32_t item = (item_id>>ITEM_ID_WIDTH);
	if (item == 0 || item > this->outline->seg_inf_limit) {
		return NULL;
	}
	uint32_t handle = (item_id&((1LL<<ITEM_ID_WIDTH)-1));
	if (handle == 0 || this->tag_oseg[item] == 0 || this->hand_table == 0 || this->hand_table[item] == 0 || handle > this->tag_oseg[item]->seghd_maxUsedHandle) {
		return NULL;
	}
	struct RuntimeMemory* rms = this->hand_table[item][handle].memory;
	if (rms && rms->scope && rms->scope[scope].current_size && rms->scope[scope].item_id) {
		return &rms->scope[scope];
	}
	return NULL;
}

bool COutline::has_any_variable(uint64_t item_id, varscope scope) {
	struct RuntimeMemoryScope* sc = get_memory(item_id, scope);
	if (!sc) {
		return false;
	}
	if (!sc->item_id) {
		return false;
	}
	return sc->current_size!=0;
}

void COutline::set_item_loop_info(uint64_t item, uint64_t data) {
	try {
		auto search = this->item_loop_info.find(item);
		while (search != this->item_loop_info.end()) {
			if (search->first != item) {
				break;
			}
			search = this->item_loop_info.erase(search);
		}
	}catch (...) {
	}
	this->item_loop_info.insert({item, data});
}

uint64_t COutline::get_item_loop_info(uint64_t item)  {
	try {
		auto search = this->item_loop_info.find(item);
		if (search != this->item_loop_info.end()) {
			return search->second;
		}
		return 0;
	}catch (...) {
		return 0;
	}
}

void COutline::set_dialog_dlgitem(uint32_t dialog, uint32_t dlgitem, uint32_t item) {
	std::map<uint32_t, uint32_t> map;
	bool found = false;
	try {
		auto search = this->dialog_dlgitems.find(dialog);
		if (search != this->dialog_dlgitems.end()) {
			if (search->first != dialog) {
				throw std::exception();
			}
			map = search->second;
			found = true;
		}
		if (!found) {
			throw std::exception();
		}
	}catch (...) {
		map = std::map<uint32_t, uint32_t>();
	}

	try {
		auto search = map.find(dlgitem);
		while (search != map.end()) {
			if (search->first != dlgitem) {
				break;
			}
			search = map.erase(search);
		}
	}catch (...) {
	}
	map.insert({dlgitem, item});

	if (found) {
		try {
			auto search = this->dialog_dlgitems.find(dialog);
			while (search != this->dialog_dlgitems.end()) {
				if (search->first != dialog) {
					break;
				}
				search = this->dialog_dlgitems.erase(search);
			}
		}catch (...) {
			map = std::map<uint32_t, uint32_t>();
		}
	}
	this->dialog_dlgitems.insert({dialog, map});
}

uint32_t COutline::get_dialog_dlgitem(uint32_t dialog, uint32_t dlgitem) {
	try {
		auto search = this->dialog_dlgitems.find(dialog);
		if (search == this->dialog_dlgitems.end()) {
			return 0;
		}
		search->second;
		auto search2 = search->second.find(dlgitem);
		if (search2 == search->second.end()) {
			return 0;
		}
		return search2->second;
	}catch (...) {
		return 0;
	}
}

void COutline::init_symbol_lookup() {
	this->symbols = alloc<struct tagPERMSYM***>(sizeof(void*)*(this->outline->seg_inf_limit+1));
	for (uint32_t item_id = 1;item_id <= this->outline->seg_inf_limit;item_id++) {
		struct HItem* item = &this->outline->data[item_id-1];
		if ((item->flags & ITEM_HAS_HANDLE_TABLE) && this->tag_oseg[item_id] && this->tag_oseg[item_id]->seghd_maxUsedHandle) {
			this->symbols[item_id] = alloc<struct tagPERMSYM**>(sizeof(void*)*(this->tag_oseg[item_id]->seghd_maxUsedHandle+1));
		}
	}
	for (int i=0;i<0x97;i++) {
		if (!this->symbol_hash[i]) {
			continue;
		}
		if (this->symbol_hash[i] > this->outline->seg_inf_limit) {
			fprintf(stderr,"warning: symbol hash reference invalid: 0x%02x->0x%04x\n",i,this->symbol_hash[i]);
			continue;
		}
		struct HItem* hitem = &this->outline->data[this->symbol_hash[i]-1];
		if (!(hitem->flags & ITEM_IS_SYMBOL_ARRAY)) {
			fprintf(stderr,"warning: symbol hash reference to non-symbol-array item: 0x%02x->0x%04x\n",i,this->symbol_hash[i]);
			continue;
		}
		if (this->tag_oseg[this->symbol_hash[i]] == 0) {
			fprintf(stderr,"warning: tagOSEG not loaded for symbol hash reference 0x%02x->0x%04x\n",i,this->symbol_hash[i]);
			continue;
		}

		size_t offset = 0;
		uint8_t* data = &this->tag_oseg[this->symbol_hash[i]]->data[offset];
		uint16_t count = *((uint16_t*)&data[0]);
		uint32_t* offsets = (uint32_t*)&data[2];
		if (2+(uint32_t)count*4 > hitem->size) {
			fprintf(stderr,"warning: symbol hash item 0x%02x->0x%04x way too small\n",i,this->symbol_hash[i]);
			continue;
		}
		for (uint16_t j=0; j<count; j++) {
			if (offsets[j] + sizeof(struct tagPERMSYM) > hitem->size) {
				fprintf(stderr,"warning: symbol hash item 0x%02x->0x%04x too small\n",i,this->symbol_hash[i]);
				fprintf(stderr,"count: %u, j: %u, size: %u, offsets[j]: %u, sizeof(tagPERMSYM): %lu\n",count,j,hitem->size,offsets[j],(unsigned long)sizeof(struct tagPERMSYM));
				continue;
			}
			struct tagPERMSYM* permsym = (struct tagPERMSYM*)&data[offsets[j]];
			uint32_t item = permsym->hItem>>ITEM_ID_WIDTH;
			uint32_t handle = permsym->hItem&((1LL<<ITEM_ID_WIDTH)-1LL);
			if (item && item <= outline->seg_inf_limit
					&& handle && handle <= this->tag_oseg[item]->seghd_maxUsedHandle
					&& this->symbols[item]) {
				this->symbols[item][handle] = permsym;
			}
		}
	}
}

const char16_t* COutline::symbol_lookup(uint64_t item_id) {
	uint32_t item = item_id>>ITEM_ID_WIDTH;
	uint32_t handle = item_id&((1LL<<ITEM_ID_WIDTH)-1LL);
	if (item && item <= outline->seg_inf_limit && this->tag_oseg[item] && handle && handle <= this->tag_oseg[item]->seghd_maxUsedHandle) {
		if (this->symbols && this->symbols[item] && this->symbols[item][handle]) {
			return (const char16_t*)this->symbols[item][handle]->str;
		}
	}
	return NULL;
}

const struct String* COutline::string_lookup(uint32_t string_id) {
	if (this->string_table && this->string_table->str && string_id < this->string_table->total_num_entries) {
		uint32_t offset = this->string_table->str[string_id];
		if (offset != 0) {
			struct String* string = (struct String*)(&this->str_data[offset]);
			return string;
		}
	}
	return NULL;
}

long COutline::OsReadFast(unsigned long uncomp_size, char* decompressed) {
	int success = 0;
	if (uncomp_size > 0) {
		unsigned long comp_size = 0;
		if (fread(&comp_size, 4, 1, handle)==1) {
			unsigned long dec_len = this->OsDeCompress(-1, decompressed, comp_size);
			if (dec_len == uncomp_size) {
				success = 1;
			}
		}
	}
	return success?uncomp_size:0;
}


#define IN_BYTE(var) \
		{ \
	if (compressed) { \
		var = *((unsigned char*)compressed); \
		compressed = ((unsigned char*)compressed) + 1; \
	}else if (fread(&var, 1, 1, this->handle) != 1) { \
		return cur_output_len; /* error */ \
		}\
remaining_input_len--; \
}

unsigned long COutline::OsDeCompress(unsigned long expected_output_len, void* decompressed, unsigned long remaining_input_len, void* compressed) {

	char* buffer;
	unsigned long cur_output_len = 0;

	unsigned char cntrl;
	unsigned char tmp;
	unsigned char old_payload = 0;
	unsigned char old_old_payload = 0;

	buffer = (char*)malloc(0x8000);
	if (!buffer) { // TD 7.2.0 does not check this
		fprintf(stderr,"error: out of memory\n");
		throw new std::bad_alloc();
	}
	memset(buffer,0x20,0x8000);
	while (remaining_input_len != 0) {
		IN_BYTE(cntrl)
		for (unsigned long i=0; i<8; i++) {
			if ((cntrl & (1 << i)) == 0) {
				// read from input stream
				if (remaining_input_len == 0) {
					return cur_output_len;
				}
				IN_BYTE(tmp)
				// store in lookup table
				buffer[(unsigned long)old_old_payload << 7 ^ (unsigned long)old_payload] = tmp;
			}else{
				// read from lookup table
				tmp = buffer[(unsigned long)old_old_payload << 7 ^ (unsigned long)old_payload];
			}
			// byte decoded, write to output stream
			*((uint8_t*)decompressed) = tmp;
			decompressed = (uint8_t*)decompressed + 1;
			cur_output_len++;
			if (cur_output_len == expected_output_len){
				return cur_output_len;
			}
			old_old_payload = old_payload;
			old_payload = tmp;
		}
	}
	free(buffer);
	return cur_output_len;
}
#undef IN_BYTE


struct HandTable* COutline::create_handtable(struct tagOSEG* item_content, uint64_t item_id) {
	if (item_id > this->outline->seg_inf_limit || !item_id) {
		fprintf(stderr,"error: called create_handtable with invalid item 0x%04x\n",item_id);
		return NULL;
	}
	HItem* item = &this->outline->data[item_id-1];
	struct HandTable* hand_table;
	hand_table = alloc<struct HandTable*>((item_content->seghd_maxUsedHandle+1) * sizeof(struct HandTable));

	// extract sub-handles of item!!
	uint32_t offset = item_content->seghd_shStartDynamic;
	struct tagHEAPBLK* iterator = (struct tagHEAPBLK*)((char*)item_content + item_content->seghd_shStartDynamic);
	while (iterator->value & HANDTABLE_ITEMSIZE_MASK) {
		if (item->size < offset + sizeof(tagHEAPBLK)) {
			free(hand_table);
			fprintf(stderr,"error: iterator ran outside of tagOSEG.data (in item 0x%04x)\n",item_id);
			throw new std::exception();
		}
		if (iterator->value & ((HANDTABLE_ITEMSIZE_MASK+1)<<1)) {
			free(hand_table);
			fprintf(stderr,"unsupported handle table type in item %u at 0x%08x\n",item_id,offset);
			throw new std::exception();
		}else{
			if (iterator->handle_id != 0 && iterator->handle_id <= item_content->seghd_maxUsedHandle) {
				if (offset + 4*(iterator->value&HANDTABLE_ITEMSIZE_MASK) > item->size) {
					free(hand_table);
					fprintf(stderr,"error: iterator ran outside of tagOSEG.data (in item 0x%04x)\n",item_id);
					throw new std::exception();
				}else /* if (iterator->size & (HANDTABLE_ITEMSIZE_MASK+1)) */ {
					uint32_t size = 4 * ((iterator->value & HANDTABLE_ITEMSIZE_MASK)-1);
					hand_table[iterator->handle_id].handle_data = alloc<struct tagITEM*>(size);
					memcpy(hand_table[iterator->handle_id].handle_data, iterator->data, size);
					// hand_table[iterator->handle_id].handle_data = (struct tagITEM*)iterator->data;
					hand_table[iterator->handle_id].size = iterator->value;
					hand_table[iterator->handle_id].memory = alloc<struct RuntimeMemory*>(sizeof(struct RuntimeMemory));
				} /* else{
					// TODO: unsupported data type...???
					// empty?? reserved??
					//fprintf(stderr,"info: item 0x%04x: unsupported flag 0x00 in HandMapItem.size field (size: 0x%04x, handle_id: 0x%04x, offset: 0x%04x)\n",item_id,iterator->size,iterator->handle_id,offset);
				} */
			}else{
				fprintf(stderr,"item 0x%04x: invalid handle id: %u (must be between 1 and %u)",item_id,iterator->handle_id,item_content->seghd_maxUsedHandle);
			}
		}
		offset += 4*(iterator->value&HANDTABLE_ITEMSIZE_MASK);
		iterator = (struct tagHEAPBLK*)((char*)item_content + offset);
		if (item->size < offset + sizeof(struct tagHEAPBLK)) {
			free(hand_table);
			fprintf(stderr,"error: iterator ran outside of tagOSEG.data (in item 0x%04x)\n",item_id);
			throw new std::exception();
		}
	}
	// last item of (size&HANDTABLE_ITEMSIZE_MASK) == 0x00 seems always to be followed by: 0x83 0x7f 0x00 0x00 -- why??
	return hand_table;
}

bool COutline::change_item_size(uint64_t item_id, uint32_t new_size) {
	// struct HandTable* COutline::create_handtable(struct tagOSEG* item_content, uint64_t item_id)
	uint32_t seginf = (item_id >> ITEM_ID_WIDTH);
	uint32_t handle_id = (item_id & ((1LL<<ITEM_ID_WIDTH)-1LL));
	if (!seginf || seginf > this->outline->seg_inf_limit) {
		if (is_verbose()) {
			fprintf(stderr,"resize error: itemid: 0x%08x, seginf: 0x%08x\n",item_id,seginf);
		}
		return false;
	}
	struct HandTable* ht = this->hand_table[seginf];
	if (!ht) {
		return false;
	}
	if (!ht[handle_id].handle_data) {
		return false;
	}
	if ((ht[handle_id].size & ((HANDTABLE_ITEMSIZE_MASK+1) * 0x03)) != (HANDTABLE_ITEMSIZE_MASK+1)) {
		if (is_verbose()) {
			fprintf(stderr,"resize error: itemsize: 0x%08x, mask: 0x%08x\n",ht[handle_id].size, HANDTABLE_ITEMSIZE_MASK);
		}
		return false; // unsupported flags
	}

	uint32_t old_size = ht[handle_id].handle_data->data_length;

	if (new_size == old_size) {
		return true; // success: no change necessary
	}

	uint32_t old_size_ht = ht[handle_id].size;
	uint32_t new_size_ht = ((uint64_t)new_size + sizeof(struct tagITEM) + 4LL-1LL)/4LL;
	ht[handle_id].size = ((new_size_ht + (sizeof(struct tagHEAPBLK)+4-1)/4) | ((HANDTABLE_ITEMSIZE_MASK+1) * 0x1d));

	if (ht[handle_id].size != old_size_ht) {
		struct tagITEM* data = (struct tagITEM*)realloc(ht[handle_id].handle_data, 4*new_size_ht);
		if (!data) {
			ht[handle_id].size = old_size_ht;
			if (is_verbose()) {
				fprintf(stderr,"resize error: realloc of size 0x%08x failed, old size: 0x%08x\n",4*new_size_ht, old_size_ht);
			}
			return false; // cannot realloc
		}
		ht[handle_id].handle_data = data;
	}
	ht[handle_id].handle_data->data_length = new_size;
	return true;
}

uint8_t COutline::is_null(struct SalNumber* num) {
	if (num == 0) {
		return 1;
	}
	if (num->size == 0) {
		return 1;
	}
	return 0;
}

void COutline::sprint_number(char out[300], struct SalNumber* num) {
	if (!out) {
		return;
	}
	*out = 0;
	if (is_null(num)) {
		sprintf(out,"NUMBER_Null");
		return;
	}
	if (num->size == 1) {
		sprintf(out,"0");
		return;
	}

	//uint8_t negative = 0;
	if ((num->payload[0]&0x80) != 0x80) {
		sprintf(out,"-"); // negative numbers
		//negative = 1;
		num->payload[0] = ~num->payload[0];
		for (int i=1;i<num->size;i++) {
			num->payload[i] = 0x64 - num->payload[i];
			if (num->payload[i] == 0xff) {
				num->payload[i] = 0;
			}
		}
	}
	uint8_t pos = 1;
	uint8_t printed_any = 0;
	for (uint8_t i=(num->payload[0]&0x7f); i>0x40; i--) {
		if (pos < 0x18 && pos < num->size) {
			if (printed_any || num->payload[pos]/10) {
				sprintf(out+strlen(out),"%c",'0'+num->payload[pos]/10);
				printed_any = 1;
			}
			if (printed_any || num->payload[pos]%10) {
				sprintf(out+strlen(out),"%c",'0'+num->payload[pos]%10);
				printed_any = 1;
			}
		}else if (printed_any) {
			sprintf(out+strlen(out),"00");
		}
		pos++;
	}
	if (pos < 0x18 && pos < num->size) {
		if (!printed_any) {
			sprintf(out+strlen(out),"0");
		}
		sprintf(out+strlen(out),".");
		for (uint8_t i=0x40; i>(num->payload[0]&0x7f); i--) {
			sprintf(out+strlen(out),"00");
		}
		for (;pos < 0x18 && pos < num->size;pos++) {
			sprintf(out+strlen(out),"%c",'0'+num->payload[pos]/10);
			if ((pos != 0x17 && pos != num->size-1) || num->payload[pos]%10) {
				sprintf(out+strlen(out),"%c",'0'+num->payload[pos]%10);
			}
		}
	}
}

void COutline::sprint_date(char out[32], struct SalNumber* num) {
	char buf[300];
	sprint_number(buf,num);
	setlocale(LC_ALL, "en_US");
	double diff = atof(buf);
	diff*=60.0*60.0*24.0; // days to seconds
	double stamp = diff-2209161600.0; // -2209161600: Unix timestamp of Dec 30th, 1899 (GMT)
	int64_t seconds = (int64_t)stamp;
	if (seconds > stamp) {
		seconds--; // force [seconds <= stamp] for double->int conversion of negative numbers
	}
	struct tm* nowtm;
	time_t nowtime = seconds;
	nowtm = gmtime(&nowtime);
	char tmbuf[64];
	strftime(tmbuf, sizeof tmbuf, "%Y-%m-%d-%H.%M.%S", nowtm);
	// compute micro seconds
	uint32_t nano_x10 = (uint32_t)((stamp-(double)seconds)*10000000.0);
	if (nano_x10%10>4) {
		nano_x10+=10;
	}
	sprintf(out,"%s.%06u",tmbuf,nano_x10/10);
}

void COutline::print_flag(uint32_t flag, const char* flag_name) {
	oprintf("%24s: %s\n",flag_name,flag!=0?"yes":"no");
}

void COutline::print_stat(uint32_t value, const char* name) {
	oprintf("%24s: %10u\n",name,value);
}

void COutline::print_stats() {
	oputs("Built with Team Developer ");
	if (file_hdr.version > VERSION_TD74) {
		oputs("newer than 7.4");
	}else if (file_hdr.version >= VERSION_TD74) {
		oputs("7.4");
	}else if (file_hdr.version >= VERSION_TD73) {
		oputs("7.3");
	}else if (file_hdr.version >= VERSION_TD72) {
		oputs("7.2");
	}else if (file_hdr.version >= VERSION_TD71) {
		oputs("7.1");
	}else if (file_hdr.version >= VERSION_TD70) {
		oputs("7.0");
	}else if (file_hdr.version >= VERSION_TD63) {
		oputs("6.3");
	}else if (file_hdr.version >= VERSION_TD62) {
		oputs("6.2");
	}else if (file_hdr.version >= VERSION_TD61) {
		oputs("6.1");
	}else if (file_hdr.version >= VERSION_TD60) {
		oputs("6.0");
	}else if (file_hdr.version >= VERSION_TD52) {
		oputs("5.2");
	}else if (file_hdr.version >= VERSION_TD51) {
		oputs("5.1");
	}else{
		oputs("before 5.1");
	}
	if ((outline->flags & OFLAG_GLMS_SIGN_MASK)==OFLAG_GLMS_SIGN_TESTVERSION) {
		oputs(" (trial version)");
	}
	oputs("\n\n");

	oputs("File Header Flags:\n");
	print_flag(file_hdr.flags & FLAG_COMPILED, "Compiled");
	print_flag(file_hdr.flags & FLAG_NOT_EDITABLE, "Not Editable");
	print_flag(file_hdr.flags & FLAG_VISIBLE_H_ITEMS, "Visible HItems");
	print_flag(file_hdr.flags & FLAG_IS_EXE, "Is EXE");
	print_flag(file_hdr.flags & FLAG_IS_DLL, "Is DLL");
	print_flag(file_hdr.flags & FLAG_IS_64BIT, "Is 64bit");
	print_flag(file_hdr.run_only == RUN_ONLY, "Run Only");
	oputs("\n");

	oputs("Outline Flags:\n");
	print_flag(outline->flags & OFLAG_APP_SYMBOLS_CURRENT, "App Symbols Current");
	print_flag(outline->flags & OFLAG_APP_IS_COMPILED, "App is Compiled");
	print_flag(outline->flags & OFLAG_APP_CHANGED, "App Changed");
	print_flag(outline->flags & OFLAG_APP_SAVE_COMPILED, "App Save Compiled");
	print_flag(outline->flags & OFLAG_FILE_IS_EXE, "File is EXE");
	print_flag(outline->flags & OFLAG_FILE_IS_DLL, "File is DLL");
	print_flag(outline->flags & OFLAG_UNTITLED, "Untitled");
	print_flag(outline->flags & OFLAG_SHARE, "Share");
	print_flag(outline->flags & OFLAG_ALL_MARKED, "All Marked");
	print_flag(outline->flags & OFLAG_HIDDEN_INCLUDED, "Hidden Included");
	print_flag(outline->flags & OFLAG_RUN_ONLY, "Run Only");
	print_flag(outline->flags & OFLAG_CHILD_LINE_COUNTS_ADDED, "Child Line Counts Added");
	oputs("\n");

	oputs("Statistics:\n");
	print_stat(outline->statistics.items,"Items");
	print_stat(outline->statistics.functions,"Functions");
	print_stat(outline->statistics.variables,"Variables");
	print_stat(outline->statistics.dialog_boxes,"Dialog Boxes");
	print_stat(outline->statistics.form_windows,"Form Windows");
	print_stat(outline->statistics.table_windows,"Table Windows");
	print_stat(outline->statistics.mdi_windows,"MDI Windows");
	print_stat(outline->statistics.child_windows,"Child Windows");
	print_stat(outline->statistics.sal_lines,"SAL Lines");
	print_stat(outline->statistics.comments,"Comments");
	print_stat(outline->statistics.to_compile,"To Compile");
	print_stat(outline->statistics.compile_ref,"Compile References");
	oputs("\n");
}

struct FileHdr COutline::get_file_hdr() {
	return this->file_hdr;
}
