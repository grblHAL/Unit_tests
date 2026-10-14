#include "support/arc_limits_motion_host.h"

int main(void)
{
    prepare_arc_limits_motion();
    queue_motion_program("G2X1Y1I1F100");
    CHECK(arc_limit_calls == 1);
    CHECK(checked_arc_plane.axis_0 == 0 && checked_arc_plane.axis_1 == 1);
    CHECK(checked_arc_plane.axis_linear == 2);
    NEAR(checked_arc_radius, 1); NEAR(checked_arc_center.x, 1); NEAR(checked_arc_center.y, 0);
    CHECK(checked_arc_turns == -1);
    for(unsigned axis = 0; axis < N_AXIS; axis++) NEAR(checked_arc_start.values[axis], 0);
    NEAR(checked_arc_target.values[0], 1); NEAR(checked_arc_target.values[1], 1);
    execute_motion_program();
    CHECK(arc_limit_calls == 1);
    CHECK(physical_position[0] == 80 && physical_position[1] == 80);
    CHECK(axis_pulses[2] == 0);
    return EXIT_SUCCESS;
}
