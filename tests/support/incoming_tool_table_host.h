#pragma once
#include "support/incoming_gcode_host.h"
static tool_data_t tools[4];
static tool_table_entry_t entries[4], incoming_current, incoming_missing;
static tool_table_entry_t *get_tool(tool_id_t id)
{ return id == 0 ? &incoming_current : id > 0 && id <= 4 && (uint32_t)id <= grbl.tool_table.n_tools ? &entries[id - 1] : &incoming_missing; }
static bool incoming_save_tool(tool_data_t *tool
#ifdef HOST_TOOL_PERSIST_API
    , bool persist
#endif
)
{
#ifdef HOST_TOOL_PERSIST_API
    (void)persist;
#endif
    CHECK(tool->tool_id >= 1 && tool->tool_id <= 4);
    tools[tool->tool_id - 1] = *tool;
    return true;
}
static inline void prepare_incoming_tool_table(void)
{
    engine_parser_prepare();
    incoming_current.data = gc_state.tool;
    for(unsigned i = 0; i < 4; i++) { tools[i].tool_id = i + 1; entries[i].data = &tools[i]; }
    grbl.tool_table.get_tool = get_tool;
    grbl.tool_table.set_tool = incoming_save_tool;
    grbl.tool_table.n_tools = 4;
}
