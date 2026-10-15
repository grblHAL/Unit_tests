#include "support/motion_extension_host.h"

int main(void)
{
    prepare_motion_extension();
    extension_accept = false;
    CHECK(cutter_block("G3X1Y1I0J1F100") == Status_GcodeInvalidTarget);
    CHECK(extension_arc_calls == 1 && extension_line_calls == 0);
    CHECK(extension_turns == 1 && extension_plane.axis_0 == X_AXIS && extension_plane.axis_1 == Y_AXIS);
    NEAR(extension_target[X_AXIS], 1);
    NEAR(extension_target[Y_AXIS], 1);
    NEAR(gc_state.position[X_AXIS], 0);
    NEAR(gc_state.position[Y_AXIS], 0);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
