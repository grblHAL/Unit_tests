#include "support/paired_pwm_program_host.h"

static unsigned reset_requests, reset_driver_calls, reset_request_index, quench_output_index;
static void reset_driver(void)
{
    CHECK(!actual_spindle_states[0].on && pair_output[0] == 0 && pair_calls[0] > 0);
    quench_output_index = pair_calls[0] - 1;
    reset_driver_calls++;
}
static void stop_coolant(coolant_state_t state) { CHECK(state.value == 0); }
static void reset_during_ramp(sys_state_t state)
{
    CHECK(state == STATE_IDLE);
    if(reset_requests == 0 && pair_output[0] > 0) {
        CHECK(pair_output[0] < 600 && actual_spindle_states[0].on);
        reset_requests++;
        reset_request_index = pair_calls[0];
        CHECK(protocol_enqueue_realtime_command(CMD_RESET));
    }
}
int main(void)
{
    pair_enable_secondary = false;
    prepare_paired_pwm_program();
    hal.driver_reset = reset_driver;
    hal.coolant.set_state = stop_coolant;
    grbl.on_execute_realtime = reset_during_ramp;
    (void)spindle_program_block("M3S6000");
    CHECK(reset_requests == 1 && reset_driver_calls == 1 && sys.abort);
    CHECK(reset_request_index > 0 && pair_calls[0] > reset_request_index);
    CHECK(quench_output_index >= reset_request_index);
    CHECK(!actual_spindle_states[0].on && pair_output[0] == 0);
    for(unsigned i = quench_output_index; i < pair_calls[0]; i++) CHECK(pair_log[0][i] == 0);
    CHECK(pair_calls[1] == 0 && spindle_get(1) == NULL);
    CHECK(sys.alarm != Alarm_Spindle && plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
