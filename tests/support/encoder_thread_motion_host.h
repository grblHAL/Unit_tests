#pragma once
#include "support/spindle_sync_parser_host.h"
static spindle_ptrs_t thread_encoder_driver;
static spindle_state_t thread_encoder_state;
static int32_t thread_minimum_x, thread_maximum_x;
static void thread_encoder_pulse(stepper_t *stepper)
{
    sync_motion_pulse(stepper);
    if(physical_position[X_AXIS] < thread_minimum_x) thread_minimum_x = physical_position[X_AXIS];
    if(physical_position[X_AXIS] > thread_maximum_x) thread_maximum_x = physical_position[X_AXIS];
}
static control_signals_t thread_encoder_controls(void) { return (control_signals_t){0}; }
static bool thread_encoder_connected(void) { return true; }
static void thread_encoder_update(spindle_ptrs_t *spindle, float rpm)
{
    CHECK(spindle == spindle_get(0));
    sync_motion_feedback.rpm = thread_encoder_state.on ? rpm : 0;
}
static void thread_encoder_output(spindle_ptrs_t *spindle, spindle_state_t state, float rpm)
{
    CHECK(spindle == spindle_get(0));
    thread_encoder_state = state;
    sync_motion_feedback.rpm = state.on ? rpm : 0;
}
static spindle_state_t thread_encoder_input(spindle_ptrs_t *spindle)
{
    CHECK(spindle == spindle_get(0));
    return thread_encoder_state;
}
static void prepare_encoder_thread_motion(void)
{
    engine_prepare();
    sys.cold_start = true;
    settings.mode = Mode_Lathe;
    settings.spindle.ppr = 100;
    hal.driver_cap.spindle_encoder = true;
    hal.spindle_data.get = sync_motion_data;
    hal.spindle_data.reset = sync_motion_reset_data;
    thread_encoder_driver = (spindle_ptrs_t){.type = SpindleType_VFD, .ref_id = 10,
        .rpm_min = 10, .rpm_max = 1000,
        .cap = {.enable = true, .variable = true, .direction = true, .rpm_range_locked = true},
        .set_state = thread_encoder_output, .get_state = thread_encoder_input,
        .get_data = sync_motion_data, .reset_data = sync_motion_reset_data, .update_rpm = thread_encoder_update};
    CHECK(spindle_register(&thread_encoder_driver, "Encoder spindle") == 0);
    CHECK(spindle_select(0));
    coord_system_data_t coordinates = {0};
    for(unsigned i = 0; i < N_CoordinateSystems; i++) settings_write_coord_data((coord_system_id_t)i, &coordinates);
    gc_init(false);
    CHECK(plan_reset());
    limits_init();
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        char acceleration[] = "100";
        CHECK(settings_store_setting(Setting_AxisAcceleration + axis, acceleration) == Status_OK);
    }
    hal.control.get_state = thread_encoder_controls;
    hal.stream.is_connected = thread_encoder_connected;
    hal.f_step_timer = 1000000;
    hal.stepper.enable = enable_motors;
    hal.stepper.go_idle = sync_parser_idle;
    hal.stepper.wake_up = sync_parser_wake;
    hal.stepper.cycles_per_tick = sync_motion_timer;
    hal.stepper.pulse_start = thread_encoder_pulse;
    grbl.on_execute_realtime = service_sync_parser_driver;
    grbl.on_settings_changed = sync_motion_settings_changed;
    st_spindle_sync_cfg(&settings, (settings_changed_flags_t){0});
    CHECK(hal.driver_cap.spindle_sync);
    st_reset();
    sys.driver_started = true;
    sys.cold_start = false;
    report_init_fns();
    state_set(STATE_IDLE);
    CHECK(sync_parser_block("G18M3S100") == Status_OK);
    CHECK(sync_parser_block("G0X10") == Status_OK);
    CHECK(protocol_buffer_synchronize());
    CHECK(physical_position[X_AXIS] == 800 && sync_motion_feedback.rpm == 100);
    memset(axis_pulses, 0, sizeof(axis_pulses));
    thread_minimum_x = thread_maximum_x = physical_position[X_AXIS];
}
