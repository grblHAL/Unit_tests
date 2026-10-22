#include "support/motion_extension_host.h"

int main(void)
{
    prepare_motion_extension();
    extension_accept = false;
    CHECK(cutter_block("G1X3Y4F100") == Status_GcodeInvalidTarget);
    CHECK(extension_line_calls == 1 && extension_arc_calls == 0);
    NEAR(extension_target[X_AXIS], 3);
    NEAR(extension_target[Y_AXIS], 4);
    NEAR(extension_feed, 100);
    NEAR(gc_state.position[X_AXIS], 0);
    NEAR(gc_state.position[Y_AXIS], 0);
    CHECK(plan_get_current_block() == NULL);
    CHECK(cutter_block("G0X6Y8") == Status_GcodeInvalidTarget);
    CHECK(extension_line_calls == 2 && extension_arc_calls == 0);
    NEAR(extension_target[X_AXIS], 6);
    NEAR(extension_target[Y_AXIS], 8);
    NEAR(gc_state.position[X_AXIS], 0);
    NEAR(gc_state.position[Y_AXIS], 0);
    CHECK(plan_get_current_block() == NULL);

    extension_accept = true;
    CHECK(cutter_block("G0X3Y4") == Status_OK);
    CHECK(extension_line_calls == 3 && extension_arc_calls == 0);
    NEAR(gc_state.position[X_AXIS], 3);
    NEAR(gc_state.position[Y_AXIS], 4);
    CHECK(plan_get_recent_block()->steps.value[X_AXIS] == 240);
    CHECK(plan_get_recent_block()->steps.value[Y_AXIS] == 320);
    CHECK(plan_get_recent_block()->condition.rapid_motion);
    return EXIT_SUCCESS;
}
