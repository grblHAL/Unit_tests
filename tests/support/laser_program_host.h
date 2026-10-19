#pragma once
#include "support/engine_host.h"
#include "spindle_control.h"
#include "protocol.h"
#include "state_machine.h"
#include "report.h"
#include "check.h"
#include <string.h>
static spindle_ptrs_t laser_driver;
static spindle_pwm_t laser_pwm_context;
static unsigned laser_pwm_calls;
/* Observe the driver level whether core uses set_state or update_pwm. */
static uint_fast16_t laser_last_driver_level;
static uint_fast16_t laser_pwm_log[2048];
static uint_fast16_t laser_get_pwm(spindle_ptrs_t *spindle, float rpm)
{ CHECK(spindle == spindle_get(0)); CHECK(rpm >= 0 && rpm <= 1000); return (uint_fast16_t)lroundf(rpm); }
static void laser_update_pwm(spindle_ptrs_t *spindle, uint_fast16_t pwm)
{
    CHECK(spindle == spindle_get(0)); CHECK(laser_pwm_calls < 2048);
    laser_pwm_log[laser_pwm_calls++] = pwm;
    laser_last_driver_level = pwm;
}
static spindle_state_t laser_output_state;
static float laser_output_power;
static unsigned laser_output_calls;
static void laser_output(spindle_ptrs_t *spindle, spindle_state_t state, float rpm)
{
    CHECK(spindle == spindle_get(0));
    laser_output_state = state; laser_output_power = rpm; laser_output_calls++;
    laser_last_driver_level = state.on ? (uint_fast16_t)lroundf(rpm) : 0;
}
static spindle_state_t laser_input(spindle_ptrs_t *spindle) { (void)spindle; return laser_output_state; }
static control_signals_t laser_controls(void) { return (control_signals_t){0}; }
static bool laser_connected(void) { return true; }
static inline void prepare_pwm_program_mode(machine_mode_t mode, bool check_mode)
{
    engine_prepare();
    sys.cold_start = true;
    settings.mode = mode;
    settings.arc_tolerance = 0.02f;
    settings.planner_buffer_blocks = 64;
    laser_pwm_context.settings = &settings.pwm_spindle;
    laser_driver = (spindle_ptrs_t){.type = SpindleType_PWM, .ref_id = 10,
        .context = {.pwm = &laser_pwm_context},
        .rpm_min = 0, .rpm_max = 1000,
        .cap = {.enable = true, .variable = true, .direction = true, .laser = true, .rpm_range_locked = true},
        .set_state = laser_output, .get_state = laser_input,
        .get_pwm = laser_get_pwm, .update_pwm = laser_update_pwm};
    CHECK(spindle_register(&laser_driver, "Laser") == 0);
    coord_system_data_t coordinates = {0};
    for(unsigned i = 0; i < N_CoordinateSystems; i++) settings_write_coord_data((coord_system_id_t)i, &coordinates);
    CHECK(spindle_select(0));
    gc_init(false);
    CHECK(plan_reset());
    limits_init();
    hal.control.get_state = laser_controls;
    hal.stream.is_connected = laser_connected;
    grbl.on_execute_realtime = protocol_execute_noop;
    report_init_fns(); report_init();
    state_set(check_mode ? STATE_CHECK_MODE : STATE_IDLE);
    CHECK(spindle_get(0)->cap.laser == (mode == Mode_Laser));
    laser_output_calls = 0;
}
static inline status_code_t laser_block(const char *text)
{
    char block[96]; CHECK(strlen(text) < sizeof(block)); strcpy(block, text);
    return gc_execute_block(block);
}

static inline void prepare_laser_program(bool check_mode)
{ prepare_pwm_program_mode(Mode_Laser, check_mode); }
