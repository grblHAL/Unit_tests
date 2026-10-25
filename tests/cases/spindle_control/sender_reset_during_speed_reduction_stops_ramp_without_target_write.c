#include "support/spindle_ramp_host.h"

static unsigned reset_requests, reset_pwm_calls, driver_resets, coolant_stops;
static control_signals_t ramp_controls(void) { return (control_signals_t){0}; }
static void ramp_reset_driver(void)
{
    CHECK(!ramp_hardware_state.on);
    reset_pwm_calls = ramp_pwm_calls;
    driver_resets++;
}
static void ramp_stop_coolant(coolant_state_t state)
{
    CHECK(state.value == 0);
    coolant_stops++;
}
static void reset_during_reduction(sys_state_t state)
{
    (void)state;
    if(ramp_pwm_calls && !reset_requests) {
        reset_requests++;
        CHECK(protocol_enqueue_realtime_command(CMD_RESET));
    }
}

int main(void)
{
    spindle_ptrs_t *active = prepare_spindle_ramp();
    hal.control.get_state = ramp_controls;
    hal.driver_reset = ramp_reset_driver;
    hal.coolant.set_state = ramp_stop_coolant;
    CHECK(spindle_set_state(active, (spindle_state_t){.on = true}, 8000));
    clear_ramp_records();
    grbl.on_execute_realtime = reset_during_reduction;
    CHECK(!spindle_set_state(active, (spindle_state_t){.on = true}, 2000));
    CHECK(reset_requests == 1 && driver_resets == 1 && coolant_stops >= 1);
    CHECK(sys.abort && !ramp_hardware_state.on);
    NEAR(ramp_initial_rpm, 0);
    CHECK(ramp_pwm_calls == reset_pwm_calls && ramp_pwm_calls > 0);
    CHECK(ramp_pwm_log[0] < active->get_pwm(active, 8000));
    CHECK(ramp_pwm_log[ramp_pwm_calls - 1] > active->get_pwm(active, 2000));
    advance_ramp_tasks(30);
    CHECK(ramp_pwm_calls == reset_pwm_calls && !ramp_hardware_state.on);
    return EXIT_SUCCESS;
}
