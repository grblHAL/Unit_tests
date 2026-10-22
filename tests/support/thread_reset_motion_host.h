#pragma once
#include "support/encoder_thread_motion_host.h"
static bool reset_sent;
static unsigned reset_calls, coolant_off_calls;
static void thread_reset(void) { reset_calls++; }
static void thread_coolant(coolant_state_t state) { CHECK(state.mask == 0); coolant_off_calls++; }
static unsigned pulses_at_reset[N_AXIS];
static bool (*thread_reset_condition)(sys_state_t state);
static void reset_during_cut(sys_state_t state)
{
    service_sync_parser_driver(state);
    if(!reset_sent && thread_reset_condition(state)) {
        reset_sent = true;
        memcpy(pulses_at_reset, axis_pulses, sizeof(pulses_at_reset));
        CHECK(protocol_enqueue_realtime_command(CMD_RESET));
    }
}
static void prepare_thread_reset(void)
{
    prepare_encoder_thread_motion();
    hal.coolant.set_state = thread_coolant;
    hal.driver_reset = thread_reset;
    grbl.on_execute_realtime = reset_during_cut;
}
static void check_thread_reset_stops_pulses(void)
{
    CHECK(reset_sent && sys.abort && !sync_parser_driver_running);
    CHECK(reset_calls == 1 && coolant_off_calls == 1);
    CHECK(!thread_encoder_state.on && sync_motion_feedback.rpm == 0);
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        CHECK(axis_pulses[axis] == pulses_at_reset[axis]);
        CHECK(sys.position[axis] == physical_position[axis]);
    }
    for(unsigned i = 0; i < 8; i++) service_sync_parser_driver(state_get());
    for(unsigned axis = 0; axis < N_AXIS; axis++) CHECK(axis_pulses[axis] == pulses_at_reset[axis]);
}
