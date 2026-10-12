#include "support/tool_change_host.h"
#include "check.h"

int main(void)
{
    prepare_tool_change_motion();
    start_manual_change();
    CHECK(sys.position[Z_AXIS] == 0 && physical_position[Z_AXIS] == 0);
    CHECK(axis_pulses[Z_AXIS] == 80);
    CHECK(sys.position[X_AXIS] == 160 && sys.position[Y_AXIS] == 240);
    CHECK(axis_pulses[X_AXIS] == 0 && axis_pulses[Y_AXIS] == 0);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
