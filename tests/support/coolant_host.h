#pragma once
#include "support/engine_host.h"
#include "coolant_control.h"
#include "state_machine.h"
#include "report.h"
#include "protocol.h"
#include "check.h"
static coolant_state_t actual_coolant;
static unsigned coolant_calls;
static void set_coolant(coolant_state_t state)
{
    actual_coolant = state;
    coolant_calls++;
}
static coolant_state_t get_coolant(void) { return actual_coolant; }
static control_signals_t coolant_controls(void) { return (control_signals_t){0}; }
static bool coolant_connected(void) { return true; }
static inline void prepare_coolant(void)
{
    engine_parser_prepare();
    state_set(STATE_IDLE);
    grbl.on_execute_realtime = protocol_execute_noop;
    hal.coolant.set_state = set_coolant;
    hal.coolant.get_state = get_coolant;
    hal.control.get_state = coolant_controls;
    hal.stream.is_connected = coolant_connected;
    report_init_fns();
    report_init();
}
