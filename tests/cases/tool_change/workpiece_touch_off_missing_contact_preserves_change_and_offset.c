#include "support/workpiece_touch_off_host.h"
int main(void)
{
    start_workpiece_touch_off(false);
    toolsetter_contact_z = -16000;
    CHECK(workpiece_touch_off() == Status_GCodeToolError);
    CHECK(!sys.flags.probe_succeeded);
    CHECK(HOST_PARSER_FLAGS.tool_change);
    CHECK(gc_state.modal.tool_offset_mode == ToolLengthOffset_Cancel);
    NEAR(gc_state.modal.tool_length_offset[Z_AXIS], 0);
    CHECK(!(sys.rt_exec_state & EXEC_CYCLE_START));
    CHECK(tool_stream_handler != original_enqueue);
    CHECK(plan_get_current_block() == NULL);
    CHECK(strstr(engine_output, "Probe failed, try again.") != NULL);
    return EXIT_SUCCESS;
}
