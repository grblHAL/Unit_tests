#pragma once
#include "support/engine_host.h"
#include "check.h"
static tool_data_t offset_tool = {.tool_id = 1};
static tool_table_entry_t offset_entry = {.data = &offset_tool};
static tool_table_entry_t missing_entry;
static get_tool_ptr original_get_tool;
static tool_table_entry_t *lookup_offset_tool(tool_id_t id)
{
    if(id == 0) return original_get_tool(id);
    return id == 1 ? &offset_entry : &missing_entry;
}
static inline void prepare_offset_tool(void)
{
    engine_parser_prepare();
    original_get_tool = grbl.tool_table.get_tool;
    grbl.tool_table.get_tool = lookup_offset_tool;
    grbl.tool_table.n_tools = 1;
    for(unsigned axis = 0; axis < N_AXIS; axis++) offset_tool.offset.values[axis] = axis + 2;
}
