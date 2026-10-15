#include "support/motion_extension_host.h"

int main(void)
{
    prepare_motion_extension();
    CHECK(cutter_block("G2X1Y-1I0J-1F100") == Status_OK);
    CHECK(extension_arc_calls == 1 && extension_line_calls == 0);
    CHECK(extension_turns == -1 && extension_plane.axis_0 == X_AXIS && extension_plane.axis_1 == Y_AXIS);
    NEAR(extension_feed, 100);
    NEAR(gc_state.position[X_AXIS], 1);
    NEAR(gc_state.position[Y_AXIS], -1);
    CHECK(plan_get_current_block() != NULL);
    return EXIT_SUCCESS;
}
