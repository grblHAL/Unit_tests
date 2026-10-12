#pragma once
#include "support/engine_host.h"
#include "check.h"
static tool_data_t g10_tool = {.tool_id = 3, .offset.values = {1, 2, 3}, .radius = 4};
static tool_data_t persisted_tool;
static tool_table_entry_t g10_entry = {.data = &g10_tool}, g10_missing = {0}, g10_current;
static unsigned g10_save_calls;
static tool_table_entry_t *g10_get_tool(tool_id_t id)
{
    return id == 3 ? &g10_entry : id == 0 ? &g10_current : &g10_missing;
}
static bool g10_save_tool(tool_data_t *tool)
{
    CHECK(tool == &g10_tool);
    persisted_tool = *tool;
    g10_save_calls++;
    return true;
}
static inline void prepare_g10_tool(void)
{
    engine_parser_prepare();
    g10_current.data = gc_state.tool;
    grbl.tool_table.n_tools = 1;
    grbl.tool_table.get_tool = g10_get_tool;
    grbl.tool_table.set_tool = g10_save_tool;
}
