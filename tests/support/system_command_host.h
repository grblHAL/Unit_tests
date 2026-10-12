#pragma once
#include "support/report_host.h"
#include "protocol.h"
#include "state_machine.h"
static control_signals_t command_controls, changed_controls;
static limit_signals_t command_limits;
static unsigned control_change_calls;
static control_signals_t command_control_state(void) { return command_controls; }
static limit_signals_t command_limit_state(void) { return command_limits; }
static void command_control_changed(control_signals_t signals) { changed_controls = signals; control_change_calls++; }
static inline void prepare_system_command(void)
{
    prepare_report();
    grbl.on_execute_realtime = protocol_execute_noop;
    grbl.on_control_signals_changed = command_control_changed;
    hal.control.get_state = command_control_state;
    hal.limits.get_state = command_limit_state;
    state_set(STATE_IDLE);
}
static inline status_code_t system_command(const char *text)
{
    char line[96];
    CHECK(strlen(text) < sizeof(line));
    strcpy(line, text);
    return system_execute_line(line, hal.stream.write);
}
