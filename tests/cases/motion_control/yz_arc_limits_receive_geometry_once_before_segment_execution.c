#include "support/arc_limits_motion_host.h"

int main(void)
{
    prepare_arc_limits_motion();
    queue_motion_program("G19G3Y1Z1K1F100");
    CHECK(arc_limit_calls == 1);
    CHECK(checked_arc_plane.axis_0 == 1 && checked_arc_plane.axis_1 == 2);
    CHECK(checked_arc_plane.axis_linear == 0);
    NEAR(checked_arc_radius, 1); NEAR(checked_arc_center.x, 0); NEAR(checked_arc_center.y, 1);
    CHECK(checked_arc_turns == 1);
    for(unsigned axis = 0; axis < N_AXIS; axis++) NEAR(checked_arc_start.values[axis], 0);
    NEAR(checked_arc_target.values[1], 1); NEAR(checked_arc_target.values[2], 1);
    execute_motion_program();
    CHECK(arc_limit_calls == 1);
    CHECK(physical_position[1] == 80 && physical_position[2] == 80);
    CHECK(axis_pulses[0] == 0);
    return EXIT_SUCCESS;
}
