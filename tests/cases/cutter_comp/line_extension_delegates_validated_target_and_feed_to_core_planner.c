#include "support/motion_extension_host.h"

int main(void)
{
    prepare_motion_extension();
    CHECK(cutter_block("G1X3Y4F100") == Status_OK);
    CHECK(extension_line_calls == 1 && extension_arc_calls == 0);
    NEAR(extension_feed, 100);
    NEAR(gc_state.position[X_AXIS], 3);
    NEAR(gc_state.position[Y_AXIS], 4);
    CHECK(plan_get_recent_block()->steps.value[X_AXIS] == 240);
    CHECK(plan_get_recent_block()->steps.value[Y_AXIS] == 320);
    return EXIT_SUCCESS;
}
