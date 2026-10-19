#pragma once
#include "support/engine_host.h"
#include "protocol.h"
#include "check.h"
static unsigned control_start_calls, plugin_start_calls;
static void control_start_event(control_signals_t signals)
{
    CHECK(signals.cycle_start);
    control_start_calls++;
}
static void cycle_start_event(void)
{
    CHECK(sys.rt_exec_state & EXEC_CYCLE_START);
    plugin_start_calls++;
}
static inline void verify_realtime_start_callbacks(uint8_t command)
{
    engine_prepare();
    grbl.on_control_signals_changed = control_start_event;
    grbl.on_cycle_start = cycle_start_event;
    CHECK(protocol_enqueue_realtime_command(command));
    CHECK(control_start_calls == 1 && plugin_start_calls == 1);
    CHECK(sys.rt_exec_state & EXEC_CYCLE_START);
}
