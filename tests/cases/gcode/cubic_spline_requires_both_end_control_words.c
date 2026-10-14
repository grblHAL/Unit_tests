#include "support/canned_motion_host.h"
int main(void)
{
    prepare_canned_motion();
    CHECK(canned_block("G5X1Y1I0J1P0F100") == Status_GcodeValueWordMissing);
    CHECK(plan_get_current_block() == NULL && wake_calls == 0);
    NEAR(gc_state.position[X_AXIS], 0);
    NEAR(gc_state.position[Y_AXIS], 0);
    return EXIT_SUCCESS;
}
