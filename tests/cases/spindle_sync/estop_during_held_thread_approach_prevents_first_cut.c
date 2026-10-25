#include "support/encoder_thread_motion_host.h"
static unsigned reset_calls, coolant_off_calls, pulses_at_reset[N_AXIS];
static void reset_driver(void) { reset_calls++; }
static void stop_coolant(coolant_state_t state) { CHECK(state.mask == 0); coolant_off_calls++; }
static bool hold_requested, estop_input, estop_sent, reset_after_release;
static unsigned held_polls, estop_polls, input_flushes;
static int32_t stopped_position[N_AXIS];
static control_signals_t estop_controls(void) { return (control_signals_t){.e_stop = estop_input}; }
static coolant_state_t no_coolant(void) { return (coolant_state_t){0}; }
static int32_t no_sender_data(void) { return SERIAL_NO_DATA; }
static void flush_sender_input(void) { input_flushes++; }
static void service_thread_estop(sys_state_t state)
{
    service_sync_parser_driver(state);
    if(!hold_requested && state == STATE_CYCLE && axis_pulses[X_AXIS] >= 20 && sync_encoder_resets == 0) {
        CHECK(!sys.override.control.feed_hold_disable);
        hold_requested = true;
        CHECK(protocol_enqueue_realtime_command(CMD_FEED_HOLD));
    }
    if(!estop_sent && state_get() == STATE_HOLD && sys.holding_state == Hold_Complete) {
        CHECK(sync_encoder_resets == 0 && physical_position[Z_AXIS] == 0);
        if(held_polls == 0) {
            memcpy(stopped_position, physical_position, sizeof(stopped_position));
            memcpy(pulses_at_reset, axis_pulses, sizeof(pulses_at_reset));
        }
        for(unsigned axis = 0; axis < N_AXIS; axis++) {
            CHECK(physical_position[axis] == stopped_position[axis]);
            CHECK(axis_pulses[axis] == pulses_at_reset[axis]);
        }
        if(++held_polls == 4) {
            estop_input = estop_sent = true;
            hal.control.interrupt_callback((control_signals_t){.e_stop = true});
        }
    }
    if(estop_sent && state_get() == STATE_ESTOP) {
        CHECK(!thread_encoder_state.on && !sync_parser_driver_running);
        CHECK(reset_calls > 0 && coolant_off_calls > 0);
        for(unsigned axis = 0; axis < N_AXIS; axis++) {
            CHECK(physical_position[axis] == stopped_position[axis]);
            CHECK(axis_pulses[axis] == pulses_at_reset[axis]);
        }
        if(!reset_after_release && ++estop_polls == 4) {
            estop_input = false;
            reset_after_release = true;
            CHECK(protocol_enqueue_realtime_command(CMD_RESET));
        }
    }
}
int main(void)
{
    prepare_encoder_thread_motion();
    hal.driver_reset = reset_driver;
    hal.coolant.set_state = stop_coolant;
    hal.signals_cap.e_stop = true;
    hal.control.get_state = estop_controls;
    hal.control.interrupt_callback = control_interrupt_handler;
    hal.coolant.get_state = no_coolant;
    hal.stream.read = no_sender_data;
    hal.stream.reset_read_buffer = flush_sender_input;
    grbl.on_execute_realtime = service_thread_estop;
    (void)sync_parser_block("G76Z-1P1I-1J0.5K1");
    CHECK(hold_requested && held_polls == 4 && estop_sent && reset_after_release && estop_polls == 4);
    CHECK(sys.abort && sys.alarm == Alarm_EStop && state_get() == STATE_ESTOP);
    CHECK(sync_encoder_resets == 0 && input_flushes > 0);
    CHECK(!thread_encoder_state.on && !sync_parser_driver_running);
    NEAR(sync_motion_feedback.rpm, 0);
    for(unsigned poll = 0; poll < 8; poll++) service_sync_parser_driver(state_get());
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        CHECK(physical_position[axis] == stopped_position[axis]);
        CHECK(axis_pulses[axis] == pulses_at_reset[axis]);
    }
    return EXIT_SUCCESS;
}
