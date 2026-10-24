#include "support/toolsetter_motion_host.h"

int main(void)
{
    prepare_toolsetter_motion(ToolChange_SemiAutomatic);
    coord_system_data_t fixture = {.coord = {.x = 2, .y = 1, .z = -2}};
    settings_write_coord_data(CoordinateSystem_G59_3, &fixture);
    CHECK(probe_add(Probe_Default, 0, IRQ_Mode_None, &toolsetter_contact_z, toolsetter_contact));
    run_automatic_toolsetter();
    CHECK(!HOST_PARSER_FLAGS.tool_change);
    CHECK(sys.tlo_reference_set.mask & Z_AXIS_BIT);
    CHECK(sys.tlo_reference[Z_AXIS] == sys.probe_position[Z_AXIS]);
    CHECK(sys.probe_position[Z_AXIS] >= -242 && sys.probe_position[Z_AXIS] <= -240);
    CHECK(physical_position[X_AXIS] == 160 && physical_position[Y_AXIS] == 240);
    CHECK(physical_position[Z_AXIS] == -80);
    CHECK(sys.position[X_AXIS] == 160 && sys.position[Y_AXIS] == 240);
    CHECK(sys.position[Z_AXIS] == -80);
    CHECK(axis_pulses[X_AXIS] == 0 && axis_pulses[Y_AXIS] == 320);
    CHECK(toolsetter_xy_pulses == 320);
    CHECK(hal.tool.change(&gc_state) == Status_OK);
    CHECK(!HOST_PARSER_FLAGS.tool_change && axis_pulses[Y_AXIS] == 320);
    CHECK(tool_stream_handler == original_enqueue);
    CHECK(hal.control.interrupt_callback == original_control);
    CHECK(sys.rt_exec_state & EXEC_CYCLE_START);
    CHECK(plan_get_current_block() == NULL && !sys.abort);
    return EXIT_SUCCESS;
}
