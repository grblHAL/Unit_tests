#include "support/tool_change_host.h"

int main(void)
{
    prepare_tool_change_motion();
    coord_system_data_t g30 = {.coord = {.x = 4, .y = 5, .z = -0.5f}};
    settings_write_coord_data(CoordinateSystem_G30, &g30);
    settings.flags.tool_change_at_g30 = true;
    start_manual_change();
    CHECK(sys.homed.mask == Z_AXIS_BIT);
    CHECK(state_get() == STATE_TOOL_CHANGE && HOST_PARSER_FLAGS.tool_change);
    CHECK(physical_position[X_AXIS] == 160 && physical_position[Y_AXIS] == 240);
    CHECK(axis_pulses[X_AXIS] == 0 && axis_pulses[Y_AXIS] == 0);
    CHECK(physical_position[Z_AXIS] == 0 && axis_pulses[Z_AXIS] == 80);
    CHECK(plan_get_current_block() == NULL);
    CHECK(gc_state.tool->tool_id == 0 && manual_tool_changed_calls == 0);
    CHECK(tool_stream_handler == original_enqueue);
    grbl.on_toolchange_ack();
    CHECK(tool_stream_handler != original_enqueue);
    CHECK(!(sys.rt_exec_state & EXEC_CYCLE_START));
    return EXIT_SUCCESS;
}
