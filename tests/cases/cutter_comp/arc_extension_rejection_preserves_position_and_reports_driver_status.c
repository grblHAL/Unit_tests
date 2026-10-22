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
    extension_accept = true;
    CHECK(cutter_block("G1X2Y0F100") == Status_OK);
    plan_block_t *queued = plan_get_current_block();
    CHECK(queued != NULL && queued->steps.value[X_AXIS] == 160);
    extension_accept = false;
    CHECK(cutter_block("G2X3Y-1I0J-1") == Status_GcodeInvalidTarget);
    CHECK(extension_arc_calls == 2 && extension_line_calls == 1);
    CHECK(extension_turns == -1);
    CHECK(plan_get_current_block() == queued && plan_get_recent_block() == queued);
    CHECK(queued->steps.value[X_AXIS] == 160);
    NEAR(gc_state.position[X_AXIS], 2);
    NEAR(gc_state.position[Y_AXIS], 0);
    extension_accept = true;
    CHECK(cutter_block("G2X3Y-1I0J-1") == Status_OK);
    CHECK(extension_arc_calls == 3);
    CHECK(plan_get_current_block() == queued && plan_get_recent_block() != queued);
    NEAR(gc_state.position[X_AXIS], 3);
    NEAR(gc_state.position[Y_AXIS], -1);
    return EXIT_SUCCESS;
}
