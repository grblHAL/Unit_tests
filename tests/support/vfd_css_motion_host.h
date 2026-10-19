#pragma once
#include "support/motion_program_host.h"
static spindle_state_t vfd_state;
static float vfd_command_rpm, vfd_rpm_log[2048];
static int32_t vfd_rpm_position[2048];
static unsigned vfd_rpm_calls;
static spindle_ptrs_t vfd_driver;
static float vfd_live_rpm, vfd_expected_fixed_rpm;
static bool vfd_check_fixed_rpm;
static void vfd_output(spindle_ptrs_t *spindle, spindle_state_t state, float rpm)
{
    CHECK(spindle == spindle_get(0));
    vfd_state = state;
    vfd_command_rpm = rpm;
    vfd_live_rpm = state.on ? rpm : 0;
}
static spindle_state_t vfd_input(spindle_ptrs_t *spindle)
{
    CHECK(spindle == spindle_get(0));
    return vfd_state;
}
static void vfd_update_rpm(spindle_ptrs_t *spindle, float rpm)
{
    CHECK(spindle == spindle_get(0) && vfd_rpm_calls < 2048);
    CHECK(isfinite(rpm) && rpm >= 0 && rpm <= 1000);
    vfd_live_rpm = rpm;
    vfd_rpm_log[vfd_rpm_calls] = rpm;
    vfd_rpm_position[vfd_rpm_calls++] = physical_position[X_AXIS];
}
static control_signals_t vfd_controls(void) { return (control_signals_t){0}; }
static bool vfd_connected(void) { return true; }
static void vfd_pulse(stepper_t *stepper)
{
    if(vfd_check_fixed_rpm) CHECK(vfd_state.on && fabsf(vfd_live_rpm - vfd_expected_fixed_rpm) < 1);
    pulse_driver(stepper);
}
static void prepare_vfd_css_motion(void)
{
    engine_prepare();
    sys.cold_start = true;
    settings.mode = Mode_Lathe;
    vfd_driver = (spindle_ptrs_t){.type = SpindleType_VFD, .ref_id = 10,
        .rpm_min = 0, .rpm_max = 1000,
        .cap = {.enable = true, .variable = true, .direction = true, .rpm_range_locked = true},
        .set_state = vfd_output, .get_state = vfd_input, .update_rpm = vfd_update_rpm};
    CHECK(spindle_register(&vfd_driver, "VFD") == 0);
    CHECK(spindle_select(0));
    coord_system_data_t coordinates = {0};
    for(unsigned i = 0; i < N_CoordinateSystems; i++)
        settings_write_coord_data((coord_system_id_t)i, &coordinates);
    gc_init(false);
    CHECK(plan_reset());
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        char acceleration[] = "100";
        CHECK(settings_store_setting(Setting_AxisAcceleration + axis, acceleration) == Status_OK);
    }
    limits_init();
    hal.control.get_state = vfd_controls;
    hal.stream.is_connected = vfd_connected;
    grbl.on_execute_realtime = protocol_execute_noop;
    hal.f_step_timer = 1000000;
    hal.stepper.enable = enable_motors;
    hal.stepper.go_idle = idle_driver;
    hal.stepper.wake_up = wake_driver;
    hal.stepper.cycles_per_tick = timer_cycles;
    hal.stepper.pulse_start = vfd_pulse;
    st_reset();
    report_init_fns();
    state_set(STATE_IDLE);
    /* Establish radius by ordinary tool motion, keeping parser, planner and
       physical coordinates aligned rather than assigning their positions. */
    queue_motion_program("G18G0X40");
    execute_motion_program();
    CHECK(protocol_exec_rt_system() && state_get() == STATE_IDLE);
    memset(axis_pulses, 0, sizeof(axis_pulses));
    wake_calls = 0;
    vfd_rpm_calls = 0;
}
static void vfd_block(const char *text)
{
    char block[96];
    CHECK(strlen(text) < sizeof(block));
    strcpy(block, text);
    CHECK(gc_execute_block(block) == Status_OK);
}
static inline void check_vfd_css_ramp(bool rising, float endpoint_rpm)
{
    CHECK(vfd_rpm_calls > 1);
    for(unsigned i = 0; i < vfd_rpm_calls; i++) {
        CHECK(vfd_state.on);
        if(i) {
            CHECK(rising ? vfd_rpm_log[i] >= vfd_rpm_log[i-1] : vfd_rpm_log[i] <= vfd_rpm_log[i-1]);
            CHECK(rising ? vfd_rpm_position[i] <= vfd_rpm_position[i-1] : vfd_rpm_position[i] >= vfd_rpm_position[i-1]);
        }
    }
    CHECK(fabsf(vfd_rpm_log[vfd_rpm_calls-1] - endpoint_rpm) < 1);
}
