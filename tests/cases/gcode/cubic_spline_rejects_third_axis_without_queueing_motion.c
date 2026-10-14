#include "support/canned_motion_host.h"
int main(void)
{
    prepare_canned_motion();
    CHECK(canned_block("G5X1Y1Z1I0J1P0Q-1F100") == Status_GcodeAxisCommandConflict);
    CHECK(plan_get_current_block() == NULL && wake_calls == 0);
    NEAR(gc_state.position[X_AXIS], 0);
    NEAR(gc_state.position[Y_AXIS], 0);
    NEAR(gc_state.position[Z_AXIS], 0);
    return EXIT_SUCCESS;
}
