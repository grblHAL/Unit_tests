#pragma once
#include "support/laser_stepper_host.h"
#include "ngc_params.h"
static inline void prepare_lathe_restore(void)
{
    prepare_pwm_stepper_mode(Mode_Lathe);
    sys.cold_start = false;
    sys.driver_started = true;
    CHECK(!spindle_get(0)->cap.laser);
    CHECK(state_get() == STATE_IDLE);
}
static inline void check_lathe_speed_restore(bool css)
{
    prepare_lathe_restore();
    CHECK(laser_block(css ? "G96S150D800" : "G97S500") == Status_OK);
    float saved_rpm = gc_spindle_get(0)->rpm;
    CHECK(laser_block("M70") == Status_OK);
    CHECK(laser_block(css ? "G97S500" : "G96S150D800") == Status_OK);
    CHECK(ngc_modal_state_restore());
    CHECK(gc_spindle_get(0)->rpm_mode == (css ? SpindleSpeedMode_CSS : SpindleSpeedMode_RPM));
    NEAR(gc_spindle_get(0)->rpm, saved_rpm);
    CHECK(!laser_output_state.on && !gc_spindle_get(0)->state.on);
    CHECK(plan_get_current_block() == NULL && axis_pulses[X_AXIS] == 0);
    ngc_modal_state_invalidate();
}
