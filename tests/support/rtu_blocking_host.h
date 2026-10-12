#pragma once
#include "support/rtu_host.h"
static unsigned realtime_calls, observed_transmissions, attempt_ticks;
static unsigned reply_on_transmission;
static bool corrupt_first_reply, reply_injected;
static void blocking_realtime(sys_state_t state)
{
    (void)state;
    CHECK(++realtime_calls < 2000);
    poll_rtu();
    if(observed_transmissions != tx_calls) {
        observed_transmissions = tx_calls;
        attempt_ticks = 0;
        reply_injected = false;
    }
    if(tx_calls && ++attempt_ticks >= 2 && !reply_injected &&
       ((corrupt_first_reply && tx_calls == 1) || tx_calls == reply_on_transmission)) {
        inject_reply(corrupt_first_reply && tx_calls == 1);
        reply_injected = true;
    }
}
static inline bool send_blocking_request(uint8_t retries)
{
    modbus_message_t message = {.tx_length = 8, .rx_length = 7, .crc_check = true,
        .adu = {1,3,0,0,0,1,0,0}};
    modbus_callbacks_t callbacks = {.retries = retries, .retry_delay = 5,
        .on_rx_packet = received, .on_rx_exception = failed};
    grbl.on_execute_realtime = blocking_realtime;
    return modbus_send(&message, &callbacks, true);
}
