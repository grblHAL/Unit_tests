#include "support/engine_host.h"
#include "ngc_tools.h"
#include "check.h"
#include <string.h>

static tool_data_t tool;
static tool_table_entry_t entry = {.data = &tool};
static tool_table_entry_t *get_tool(tool_id_t id)
{
    CHECK(id >= 1 && id <= 4);
    return &entry;
}

int main(void)
{
    engine_prepare(); sys.cold_start = true;
    coord_system_data_t coordinates = {0};
    for(unsigned i = 0; i < N_CoordinateSystems; i++) settings_write_coord_data((coord_system_id_t)i, &coordinates);
    grbl.tool_table.get_tool = get_tool;
    grbl.tool_table.n_tools = 4;
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

    // T5 M6 - Invalid tool (only 4 tools)
    char block3[] = "T5M6";
    CHECK(gc_execute_block(block3) == Status_GcodeIllegalToolTableEntry);
    CHECK(gc_state.tool == 2); // Tool should remain unchanged

    return EXIT_SUCCESS;
}