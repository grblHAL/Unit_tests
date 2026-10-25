#include "support/workpiece_touch_off_host.h"

int main(void)
{
    start_workpiece_touch_off(false);
    toolsetter_contact_z = -480;
    CHECK(workpiece_touch_off() == Status_OK);
    CHECK(sys.flags.probe_succeeded);
    CHECK(sys.probe_position[Z_AXIS] >= -482 && sys.probe_position[Z_AXIS] <= -480);
    CHECK(physical_position[Z_AXIS] == sys.probe_position[Z_AXIS] + 320);
    CHECK(physical_position[Z_AXIS] < sys.home_position[Z_AXIS] * settings.axis[Z_AXIS].steps_per_mm);
    CHECK(physical_position[X_AXIS] == 160 && physical_position[Y_AXIS] == 240);
    CHECK(gc_state.modal.tool_offset_mode == ToolLengthOffset_EnableDynamic);
    NEAR(gc_state.modal.tool_length_offset[Z_AXIS],
         (float)(sys.probe_position[Z_AXIS] - sys.tlo_reference[Z_AXIS]) / settings.axis[Z_AXIS].steps_per_mm);
    CHECK(HOST_PARSER_FLAGS.tool_change && tool_stream_handler != original_enqueue);
    CHECK(!(sys.rt_exec_state & EXEC_CYCLE_START));
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
