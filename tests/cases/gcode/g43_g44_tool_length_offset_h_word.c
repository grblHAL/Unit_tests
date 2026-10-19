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

    // Set tool 1 length
    tools[0].length = 10.0f;

    // G43 H1 - Apply tool 1 length offset
    char block1[] = "G43H1";
    CHECK(gc_execute_block(block1) == Status_OK);
    NEAR(gc_state.modal.tool_length_offset, 10.0f);

    // G44 H1 - Apply negative tool 1 length offset
    char block2[] = "G44H1";
    CHECK(gc_execute_block(block2) == Status_OK);
    NEAR(gc_state.modal.tool_length_offset, -10.0f);

    // G49 - Cancel tool length offset
    char block3[] = "G49";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(gc_state.modal.tool_length_offset, 0.0f);

    // G43 H5 - Invalid tool
    char block4[] = "G43H5";
    CHECK(gc_execute_block(block4) == Status_GcodeIllegalToolTableEntry);

    return EXIT_SUCCESS;
}