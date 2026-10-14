#pragma once
#include "support/stream_claim_host.h"
#include "state_machine.h"
#include <stdint.h>
static bool busy_network_up;
static unsigned busy_connection_queries;
static inline bool busy_network_connected(void) { busy_connection_queries++; return busy_network_up; }
static inline void prepare_busy_uart(void)
{
    prepare_stream_claim(); state_set(STATE_IDLE);
    hal.stream.type = StreamType_Serial; hal.stream.instance = 1;
}
