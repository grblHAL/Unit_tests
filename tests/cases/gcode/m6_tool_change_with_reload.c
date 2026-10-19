#include "support/engine_host.h"
#include "ngc_tools.h"
#include "check.h"
#include <string.h>

static tool_data_t tools[4];
static tool_table_entry_t entries[4] = {{.data = &tools[0]}, {.data = &tools[1]}, {.data = &tools[2]}, {.data = &tools[3]}};
static tool_table_entry_t *get_tool(tool_id_t id)
{
    if(id >= 1 && id <= 4) return &entries[id - 1];
    return NULL;
}
static status_code_t tool_reload(tool_id_t id)
{
    CHECK(id >= 1 && id <= 4);
    return Status_OK;
}

int main(void)
{
    engine_prepare(); sys.cold_start = true;
    coord_system_data_t coordinates = {0};
    for(unsigned i = 0; i < N_CoordinateSystems; i++) settings_write_coord_data((coord_system_id_t)i, &coordinates);
    grbl.tool_table.get_tool = get_tool;
    grbl.tool_table.n_tools = 4;
    grbl.tool_table.reload_tool = tool_reload;
    CHECK(spindle_select(0)); gc_init(false); CHECK(plan_reset()); limits_init();
    hal.control.get_state = engine_controls;
    hal.stream.is_connected = engine_connected;
    grbl.on_execute_realtime = protocol_execute_noop;
    report_init_fns(); report_init(); state_set(STATE_IDLE);
    sys.cold_start = false; sys.driver_started = true;

    // T1 M6 - Tool change to tool 1
    char block1[] = "T1M6";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(gc_state.tool == 1);

    // T2 M6 - Tool change to tool 2
    char block2[] = "T2M6";
    CHECK(gc_execute_block(block2) == Status_OK);
    CHECK(gc_state.tool == 2);

    // T3 M6 - Tool change to tool 3
    char block3[] = "T3M6";
    CHECK(gc_execute_block(block3) == Status_OK);
    CHECK(gc_state.tool == 3);

    return EXIT_SUCCESS;
}