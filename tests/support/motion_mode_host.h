#pragma once
#include "support/motion_program_host.h"
static unsigned rapid_steps, feed_steps;
static void tracking_spindle_output(spindle_ptrs_t *spindle, spindle_state_t state, float rpm)
{ (void)spindle; (void)rpm; CHECK(!state.on); }
static spindle_state_t tracking_spindle_input(spindle_ptrs_t *spindle)
{ (void)spindle; return (spindle_state_t){0}; }
static spindle_ptrs_t tracking_spindle;

static motion_mode_t mode_sequence[8];
static unsigned mode_changes;
static char rapid_report[256], feed_report[256];
static void tracked_mode_pulse(stepper_t *stepper)
{
    pulse_driver(stepper);
    if(stepper->step_out.mask) {
        motion_mode_t mode = st_get_motion_mode();
        CHECK(mode == MotionMode_Seek || mode == MotionMode_Linear || mode == MotionMode_CwArc || mode == MotionMode_CcwArc);
        if(mode == MotionMode_Seek) rapid_steps++; else feed_steps++;
        if(!mode_changes || mode_sequence[mode_changes-1] != mode) {
            CHECK(mode_changes < 8); mode_sequence[mode_changes++] = mode;
            engine_output[0] = 0; report_gcode_modes(hal.stream.write);
            CHECK(strlen(engine_output) < sizeof(rapid_report));
            strcpy(mode == MotionMode_Seek ? rapid_report : feed_report, engine_output);
            engine_output[0] = 0;
        }
    }
}
static inline void prepare_motion_modes(void)
{
    /* Register a real host spindle before parser startup: modal reports inspect it. */
    engine_prepare();
    tracking_spindle = (spindle_ptrs_t){.type = SpindleType_Basic,
        .set_state = tracking_spindle_output, .get_state = tracking_spindle_input};
    CHECK(spindle_register(&tracking_spindle, "host") == 0);
    prepare_motion_program(); report_init();
    hal.stepper.pulse_start = tracked_mode_pulse;
}
