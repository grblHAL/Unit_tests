#include "support/arc_limits_motion_host.h"

int main(void)
{
    prepare_arc_limits_motion();
    settings.limits.soft_enabled.mask = 0;
    sys.soft_limits.mask = 0;
    queue_motion_program("G3X1Y1J1F100");
    CHECK(arc_limit_calls == 0);
    execute_motion_program();
    CHECK(arc_limit_calls == 0);
    CHECK(physical_position[X_AXIS] == 80 && physical_position[Y_AXIS] == 80);
    CHECK(axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
