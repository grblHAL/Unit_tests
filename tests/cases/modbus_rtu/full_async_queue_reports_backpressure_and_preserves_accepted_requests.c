#include "support/rtu_host.h"

static void drain_replies(void)
{
    unsigned observed = 0, ticks_since_send = 0;
    for(unsigned tick = 0; tick < 1000; tick++) {
        poll_rtu();
        if(observed != tx_calls) {
            observed = tx_calls;
            ticks_since_send = 0;
        }
        if(observed && ++ticks_since_send == 2) inject_reply(false);
    }
}
int main(void)
{
    prepare_rtu();
    modbus_message_t message = {.tx_length = 8, .rx_length = 7, .crc_check = true,
        .adu = {1, 3, 0, 0, 0, 1, 0, 0}};
    modbus_callbacks_t callbacks = {.on_rx_packet = received, .on_rx_exception = failed};
    unsigned accepted = 0;
    bool rejected = false;
    for(unsigned request = 0; request < MODBUS_QUEUE_LENGTH * 2; request++) {
        if(!modbus_send(&message, &callbacks, false)) {
            rejected = true;
            break;
        }
        accepted++;
    }
    CHECK(tx_calls == 0 && accepted > 0);
    drain_replies();
    fprintf(stderr, "Queue accepted=%u transmitted=%u completed=%u rejected=%u\n",
        accepted, tx_calls, rx_calls, rejected);
    CHECK(exceptions == 0 && tx_calls == rx_calls);
    CHECK(rx_calls == accepted);
    CHECK(rejected);
    CHECK(modbus_send(&message, &callbacks, false));
    drain_replies();
    CHECK(tx_calls == accepted + 1 && rx_calls == accepted + 1 && exceptions == 0);
    CHECK(!modbus_isbusy() && engine_irq_depth == 0);
    return EXIT_SUCCESS;
}
