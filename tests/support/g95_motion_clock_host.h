#pragma once
#include "support/spindle_sync_motion_host.h"
static uint64_t g95_timer_cycles, g95_sample_cycles[4];
static unsigned g95_samples;
static uint32_t g95_change_at_ms;
static float g95_target_rpm;
static bool g95_rpm_changed;
static void g95_clocked_pulse(stepper_t *stepper)
{
    g95_timer_cycles += sync_timer_cycles;
    engine_ticks = (uint32_t)(g95_timer_cycles * 1000 / hal.f_step_timer);
    /* Model an external spindle-speed change at a configured elapsed time.
       Encoder rotation is independent of commanded or measured axis travel. */
    if(!g95_rpm_changed && engine_ticks >= g95_change_at_ms) {
        sync_motion_feedback.rpm = g95_target_rpm;
        g95_rpm_changed = true;
    }
    sync_motion_pulse(stepper);
    const int32_t sample_steps[] = {160, 320, 560, 720};
    if(g95_samples < 4 && physical_position[Z_AXIS] == sample_steps[g95_samples])
        g95_sample_cycles[g95_samples++] = g95_timer_cycles;
}
static inline void prepare_clocked_g95(float initial_rpm, float final_rpm, uint32_t change_at_ms)
{
    prepare_spindle_sync_motion();
    char acceleration[] = "100";
    CHECK(settings_store_setting(Setting_AxisAcceleration + Z_AXIS, acceleration) == Status_OK);
    sync_motion_feedback.rpm = initial_rpm;
    g95_target_rpm = final_rpm;
    g95_change_at_ms = change_at_ms;
    hal.stepper.pulse_start = g95_clocked_pulse;
    grbl.on_execute_realtime = protocol_execute_noop;
}
static inline float measured_g95_feed(unsigned first, unsigned second)
{
    CHECK(second < 4 && first < second && g95_sample_cycles[second] > g95_sample_cycles[first]);
    /* Both windows span 160 physical Z steps, or 2 mm at 80 steps/mm. */
    return 2.0f * 60.0f * (float)hal.f_step_timer /
           (float)(g95_sample_cycles[second] - g95_sample_cycles[first]);
}
static inline void check_clocked_g95_end(void)
{
    CHECK(g95_rpm_changed && g95_samples == 4);
    CHECK(axis_pulses[Z_AXIS] == 800 && physical_position[Z_AXIS] == 800);
    CHECK(axis_pulses[X_AXIS] == 0 && axis_pulses[Y_AXIS] == 0);
    CHECK(sync_angle_reads == 0 && sync_encoder_resets == 0);
    CHECK(!sys.abort && sys.alarm == Alarm_None);
}
