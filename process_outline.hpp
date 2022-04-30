#undef INC_ITEM_HPP_
#ifndef TDx64
#ifndef PROCESS_OUTLINE_HPP_
#define INC_ITEM_HPP_
#define PROCESS_OUTLINE_HPP_
#endif
#endif

#ifdef TDx64
#ifndef PROCESS_OUTLINE64_HPP_
#define INC_ITEM_HPP_
#define PROCESS_OUTLINE64_HPP_
#endif
#endif

#ifdef INC_ITEM_HPP_

#include "COutline.hpp"
#include "commandline_args.hpp"

void print_indent(uint32_t indent);
void iterate_items(COutline& outline, uint64_t item, uint32_t indention, uint64_t* parent_memory_item, bool first_pass = false);
bool process_outline(COutline& outline);

#endif
#undef INC_ITEM_HPP_
