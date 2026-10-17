#include "support/lathe_restore_runtime_host.h"
int main(void)
{
    prepare_lathe_restore();
    CHECK(laser_block("M4S500") == Status_OK);
    CHECK(laser_block("M70") == Status_OK);
    CHECK(laser_block("M3S300") == Status_OK);
    CHECK(laser_output_state.on && !laser_output_state.ccw);
    CHECK(laser_block("M72") == Status_OK);
    CHECK(laser_output_state.on && laser_output_state.ccw);
    CHECK(gc_spindle_get(0)->state.on && gc_spindle_get(0)->state.ccw);
    NEAR(laser_output_power, 500);
    NEAR(gc_spindle_get(0)->rpm, 500);
    CHECK(plan_get_current_block() == NULL && axis_pulses[X_AXIS] == 0);
    ngc_modal_state_invalidate();
    return EXIT_SUCCESS;
}
