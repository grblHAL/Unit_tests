#include "support/workpiece_touch_off_host.h"
int main(void)
{
    start_workpiece_touch_off(false);
    CHECK(workpiece_touch_off() == Status_OK);
    check_workpiece_touch_off();
    CHECK(sys.probe_position[Z_AXIS] >= -242 && sys.probe_position[Z_AXIS] <= -240);
    CHECK(tool_stream_handler(CMD_CYCLE_START));
    engine_execute_tasks(STATE_TOOL_CHANGE);
    CHECK(!gc_state.tool_change);
    CHECK(tool_stream_handler == original_enqueue);
    CHECK(sys.rt_exec_state & EXEC_CYCLE_START);
    NEAR((float)physical_position[Z_AXIS] / settings.axis[Z_AXIS].steps_per_mm - gc_state.modal.tool_length_offset[Z_AXIS], -1);
    return EXIT_SUCCESS;
}
