#include "support/toolsetter_motion_host.h"

int main(void)
{
    prepare_toolsetter_motion(ToolChange_Manual_G59_3);
    settings.flags.tool_change_at_g30 = true;
    coord_system_data_t g30 = {.coord = {.x = 4, .y = 5, .z = -3}};
    settings_write_coord_data(CoordinateSystem_G30, &g30);
    start_manual_change();
    CHECK(physical_position[X_AXIS] == 320 && physical_position[Y_AXIS] == 400);
    grbl.on_toolchange_ack();
    hal.control.interrupt_callback((control_signals_t){.cycle_start = true});
    hal.control.interrupt_callback((control_signals_t){.cycle_start = true});
    CHECK(physical_position[X_AXIS] == 320 && physical_position[Y_AXIS] == 400);
    engine_execute_tasks(STATE_TOOL_CHANGE);
    CHECK(HOST_PARSER_FLAGS.tool_change);
    CHECK(physical_position[X_AXIS] == 80 && physical_position[Y_AXIS] == 80);
    CHECK(physical_position[Z_AXIS] == -160 && toolsetter_xy_pulses > 0);
    CHECK(plan_get_current_block() == NULL && manual_tool_changed_calls == 0);
    return EXIT_SUCCESS;
}
