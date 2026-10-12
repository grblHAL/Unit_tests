#include "support/tool_change_host.h"
#include "check.h"

int main(void)
{
    prepare_tool_change_motion();
    start_manual_change();
    resume_manual_change();
    CHECK(!gc_state.tool_change);
    CHECK(sys.position[X_AXIS] == 160 && sys.position[Y_AXIS] == 240);
    CHECK(sys.position[Z_AXIS] == -80 && physical_position[Z_AXIS] == -80);
    CHECK(axis_pulses[Z_AXIS] == 160);
    CHECK(plan_get_current_block() == NULL);
    CHECK(tool_stream_handler == original_enqueue);
    CHECK(hal.control.interrupt_callback == original_control);
    return EXIT_SUCCESS;
}
