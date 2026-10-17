#pragma once
#include "support/m6_program_host.h"
static unsigned tool_reload_calls;
static status_code_t tool_reload_status = Status_OK;
static status_code_t reload_tool_backend(void)
{
    tool_reload_calls++;
    return tool_reload_status;
}
static void prepare_tool_reload(void)
{
    prepare_m6_program();
    grbl.tool_table.reload = reload_tool_backend;
    CHECK(gc_state.tool->tool_id == 0);
}
