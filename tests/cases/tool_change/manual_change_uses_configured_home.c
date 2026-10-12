#include "support/tool_change_host.h"
#include "check.h"

int main(void)
{
    prepare_tool_change_motion();
    sys.home_position[Z_AXIS] = -0.5f;
    start_manual_change();
    CHECK(sys.position[Z_AXIS] == -40 && physical_position[Z_AXIS] == -40);
    CHECK(axis_pulses[Z_AXIS] == 40);
    CHECK(gc_state.position[Z_AXIS] == -0.5f);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
