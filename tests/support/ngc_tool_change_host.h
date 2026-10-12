#pragma once
#include "support/ngc_tool_runtime_host.h"
static unsigned ngc_change_calls;
static status_code_t ngc_change_status = Status_Unhandled;
static atc_status_t ngc_atc_status(void) { return ATC_Online; }
static status_code_t ngc_tool_change(parser_state_t *parser)
{ CHECK(parser == &gc_state); ngc_change_calls++; return ngc_change_status; }
static inline vfs_file_t *prepare_ngc_change_file(void)
{
    vfs_file_t *file = prepare_ngc_runtime_file();
    hal.driver_cap.atc = true; hal.tool.atc_get_state = ngc_atc_status;
    hal.tool.change = ngc_tool_change; settings.tool_change.mode = ToolChange_Manual;
    return file;
}
