#include "support/canned_motion_host.h"
int main(void)
{
    prepare_canned_motion();
    CHECK(canned_block("G18") == Status_OK);
    CHECK(canned_block("G5X1Z1I0J1P0Q-1F100") == Status_GcodeIllegalPlane);
    CHECK(plan_get_current_block() == NULL && wake_calls == 0);
    CHECK(gc_state.modal.plane_select == PlaneSelect_ZX);
    NEAR(gc_state.position[X_AXIS], 0);
    NEAR(gc_state.position[Z_AXIS], 0);
    return EXIT_SUCCESS;
}
