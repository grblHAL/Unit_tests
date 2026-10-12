#pragma once
#include "support/motion_program_host.h"
/* This is the same upstream settings hook invoked by settings_init(). */
extern void st_spindle_sync_cfg(settings_t *current, settings_changed_flags_t changed);
static spindle_data_t sync_motion_feedback;
static unsigned sync_rpm_reads, sync_angle_reads, sync_settings_calls, sync_realtime_calls, sync_encoder_resets;
static settings_changed_flags_t sync_last_changed;
static uint32_t sync_timer_cycles = 1;
static spindle_data_t *sync_motion_data(spindle_data_request_t request)
{
    if(request == SpindleData_RPM) sync_rpm_reads++;
    if(request == SpindleData_AngularPosition) sync_angle_reads++;
    return &sync_motion_feedback;
}
static void sync_motion_reset_data(void)
{
    sync_encoder_resets++;
    sync_motion_feedback.angular_position = 0;
    sync_motion_feedback.index_count = 0;
}
static void sync_motion_realtime(sys_state_t state)
{
    (void)state;
    sync_realtime_calls++;
    engine_ticks++;
    sync_motion_feedback.angular_position += sync_motion_feedback.rpm / 60000.0f;
    sync_motion_feedback.index_count = (uint32_t)sync_motion_feedback.angular_position;
}
static void sync_motion_settings_changed(settings_t *current, settings_changed_flags_t changed)
{
    CHECK(current == &settings);
    sync_last_changed = changed;
    sync_settings_calls++;
}
static void sync_motion_timer(uint32_t cycles)
{
    CHECK(cycles > 0);
    sync_timer_cycles = cycles;
}
static void sync_motion_pulse(stepper_t *stepper)
{
    /* A measured encoder model advances with elapsed driver timer periods,
       independently of requested tool displacement. */
    sync_motion_feedback.angular_position += sync_motion_feedback.rpm / 60.0f *
                                            (float)sync_timer_cycles / (float)hal.f_step_timer;
    pulse_driver(stepper);
}
static inline void prepare_spindle_sync_motion(void)
{
    prepare_motion_program();
    sync_motion_feedback.rpm = 100;
    grbl.on_execute_realtime = sync_motion_realtime;
    hal.spindle_data.get = sync_motion_data;
    hal.spindle_data.reset = sync_motion_reset_data;
    spindle_get(0)->get_data = sync_motion_data;
    spindle_get(0)->reset_data = sync_motion_reset_data;
    hal.driver_cap.spindle_encoder = true;
    settings.spindle.ppr = 100;
    grbl.on_settings_changed = sync_motion_settings_changed;
    hal.stepper.cycles_per_tick = sync_motion_timer;
    hal.stepper.pulse_start = sync_motion_pulse;
    st_spindle_sync_cfg(&settings, (settings_changed_flags_t){0});
    CHECK(hal.driver_cap.spindle_sync);
}
static inline void queue_spindle_sync_line(float z, bool units_per_rev)
{
    float target[N_AXIS] = {0, 0, z};
    plan_line_data_t data;
    plan_data_init(&data);
    data.feed_rate = 1;
    data.spindle.state.synchronized = true;
    data.condition.units_per_rev = units_per_rev;
    CHECK(plan_buffer_line(target, &data));
}
