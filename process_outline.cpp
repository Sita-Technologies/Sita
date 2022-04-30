#include "process_outline.hpp"

#include "helper.hpp"
#include <string.h>

#ifndef TDx64
void print_indent(uint32_t indent) {
	for (uint32_t i=0; i<indent; i++) {
		oputs(" ");
	}
}
#endif

void iterate_items(COutline& outline, uint64_t item, uint32_t indention, uint64_t* parent_memory_item, bool first_pass) {
	uint32_t last_sibling = 0;
	while (item) {

		uint64_t memory_item[0x20];
		if (parent_memory_item) {
			memcpy(memory_item,parent_memory_item,sizeof(uint64_t)*0x20);
		}else{
			memset(memory_item,0,sizeof(uint64_t)*0x20);
		}

		tagITEM* p_item = outline.get_item(item);
		if (!p_item) {
			return;
		}

		uint64_t deref = outline.item_pointer_dereference(item);
		if (deref && deref != item) {

			if (is_verbose() && !first_pass) {
				print_indent(indention);
				oprintf("%04x.%04x: ",item>>16,item&0xFFFF);
				oprintf("[0x%04x]",p_item->type);
				oprintf("(flgs:0x%08x)",p_item->flags);
				oputs("<NULL> ");
				tag_items[p_item->type]->print(&outline,item,memory_item);
				oputs("\n");
			}

			iterate_items(outline,deref,indention, memory_item, first_pass);
		}else if (p_item->type != Item::Type::POINTER){
			if (first_pass) {
				if (p_item->type < TAG_ITEMS_AMOUNT) {
					tag_items[p_item->type]->first_pass(&outline,item, memory_item);
				}
			}else{
				if (p_item->type < TAG_ITEMS_AMOUNT) {
					tag_items[p_item->type]->preprocess(&outline,item,memory_item);
				}

				if (!get_app_output_filename() || is_verbose()) {
					print_indent(indention);
					if (is_verbose()) {
						oprintf("%04x.%04x: ",item>>16,item&0xFFFF);
						oprintf("[0x%04x]",p_item->type);
						oprintf("(flgs:0x%08x)",p_item->flags);
					}
					if (p_item->type >= TAG_ITEMS_AMOUNT) {
						oputs("???");
					}else{
						tag_items[p_item->type]->print(&outline,item,memory_item);
					}
					if (p_item->flags & 0x1000) {
						oputs(" !__Exported");
					}
					oputs("\n");
				}

				if (get_app_output_filename() && p_item->type < TAG_ITEMS_AMOUNT) {
					tag_items[p_item->type]->decompile(&outline,item,memory_item);
					p_item = outline.get_item(item);
				}
			}
		}else{
			if (is_verbose() && !first_pass && !get_app_output_filename()) {
				print_indent(indention);
				oprintf("%04x.%04x: ",item>>16,item&0xFFFF);
				oprintf("[0x%04x]",p_item->type);
				oprintf("(flgs:0x%08x)",p_item->flags);
				oputs("<NULL_noref> ");
				tag_items[p_item->type]->print(&outline,item,memory_item);
				oputs("\n");
			}
		}

		if (!first_pass && get_app_output_filename()) {
			CItem::remove_itembody(&outline,item,0x30); // childlinecount
			CItem::remove_itembody(&outline,item,0x31); // previtem (recompute)
			// insert previtem
			if (last_sibling) {
				uint8_t tmp[5];
				memset(tmp,0,5);
				tmp[0] = 0x31;
				memcpy(tmp+1,&last_sibling,CItem::itembody_elementsize((struct ItemBody*)tmp));
				CItem::add_itembody(&outline,item,(struct ItemBody*)tmp);
			}
		}

		uint64_t next;
		next = outline.child_item(item);
		if (next) {
			iterate_items(outline, next,indention+(outline.get_item(item)->type == Item::Type::POINTER?0:1),memory_item,first_pass);
		}

		p_item = outline.get_item(item); // repair after possible size-changing in recursive call
		if (p_item->type < TAG_ITEMS_AMOUNT) {
			tag_items[p_item->type]->postprocess(&outline,item,first_pass?NULL:memory_item);
		}

		next = outline.next_item(item);
		last_sibling = (item & (((1LL<<ITEM_ID_WIDTH)-1LL)));
		item = next;
	}
}

bool process_outline(COutline& outline) {
	if (is_verbose()) {
		oprintf("Information about %s:\n",get_input_filename());
		outline.print_stats();
	}

	if (get_app_output_filename() || !get_resource_dump_dir()) {
		iterate_items(outline,outline.top_item(),0,NULL, true);
		iterate_items(outline,outline.top_item(),0,NULL);

		if (is_verbose()) {
			oputs("\n=== STRING TABLE ===\n");
			uint32_t string_id = 0;
			const struct String* str = outline.string_lookup(string_id);
			while (str) {
				oprintf("0x%08x: ",string_id);
				print_utf16(str->str, str->len);
				oputs("\n");
				str = outline.string_lookup(++string_id);
			}
		}
		if (get_app_output_filename()) {
			// create .app file
			FILE* app_output = fopen(get_app_output_filename(),"w+b");
			if (!app_output) {
				fprintf(stderr,"cannot write to app file %s\n",get_app_output_filename());
				return false;
			}
			outline.save(app_output);
			fclose(app_output);
			printf("decompiled app written to app file %s\n",get_app_output_filename());
		}
	}
	return true;
}
