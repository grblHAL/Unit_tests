#pragma once
#include "support/engine_host.h"
#include "protocol.h"
#include "override.h"
#include "check.h"
static inline void prepare_protocol(void)
{
    engine_parser_prepare();
    grbl.on_execute_realtime = protocol_execute_noop;
}
static inline void execute_command(uint8_t command)
{
    CHECK(protocol_enqueue_realtime_command(command));
    CHECK(protocol_exec_rt_system());
}
