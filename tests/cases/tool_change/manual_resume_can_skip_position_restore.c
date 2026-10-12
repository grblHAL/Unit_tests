#include "support/tool_change_host.h"
#include "check.h"

int main(void)
{
    prepare_tool_change_motion();
    settings.flags.no_restore_position_after_M6 = true;
    start_manual_change();
    resume_manual_change();
    CHECK(!gc_state.tool_change);
    CHECK(sys.position[Z_AXIS] == 0 && physical_position[Z_AXIS] == 0);
    CHECK(axis_pulses[Z_AXIS] == 80);
    CHECK(plan_get_current_block() == NULL);
    CHECK(tool_stream_handler == original_enqueue);
    return EXIT_SUCCESS;
}
