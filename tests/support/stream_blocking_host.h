#pragma once
#include "support/engine_host.h"
#include "stream.h"
#include "state_machine.h"
#include "check.h"
static unsigned blocking_callbacks;
static bool inject_reset, nested_result;
static void blocking_foreground(sys_state_t state)
{
    CHECK(state == STATE_IDLE);
    CHECK(++blocking_callbacks == 1);
    if(inject_reset) sys.rt_exec_state |= EXEC_RESET;
    nested_result = stream_tx_blocking();
}
static inline void prepare_stream_blocking(void)
{
    engine_prepare();
    state_set(STATE_IDLE);
    grbl.on_execute_realtime = blocking_foreground;
}
