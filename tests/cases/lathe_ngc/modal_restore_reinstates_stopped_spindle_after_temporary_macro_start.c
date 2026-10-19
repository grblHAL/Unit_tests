#include "support/lathe_restore_runtime_host.h"
int main(void)
{
    prepare_lathe_restore();
    CHECK(laser_block("M5") == Status_OK);
    CHECK(laser_block("M70") == Status_OK);
    CHECK(laser_block("M3S500") == Status_OK);
    CHECK(laser_output_state.on);
    CHECK(laser_block("M72") == Status_OK);
    CHECK(!laser_output_state.on && !gc_spindle_get(0)->state.on);
    NEAR(gc_spindle_get(0)->rpm, 0);
    CHECK(plan_get_current_block() == NULL && axis_pulses[X_AXIS] == 0);
    ngc_modal_state_invalidate();
    return EXIT_SUCCESS;
}
