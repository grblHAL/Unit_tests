#pragma once
#include "support/ngc_tool_file_host.h"
#include "state_machine.h"
#include "report.h"
static unsigned ngc_runtime_tool_changes;
static void ngc_runtime_tool_changed(tool_data_t *tool) { CHECK(tool != NULL); ngc_runtime_tool_changes++; }
static control_signals_t ngc_tool_controls(void) { return (control_signals_t){0}; }
static bool ngc_tool_connected(void) { return true; }
static inline vfs_file_t *prepare_ngc_runtime_file(void)
{
    vfs_file_t *file = prepare_ngc_tool_file();
    hal.control.get_state = ngc_tool_controls;
    grbl.on_tool_changed = ngc_runtime_tool_changed;
    hal.stream.is_connected = ngc_tool_connected;
    settings.status_report.sync_on_wco_change = false;
    report_init_fns(); report_init(); state_set(STATE_IDLE); return file;
}
