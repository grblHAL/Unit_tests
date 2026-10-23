#include "support/rtu_host.h"

static unsigned completed, contexts[MODBUS_QUEUE_LENGTH * 3];
static void complete_in_order(modbus_message_t *message)
{
    CHECK(completed < MODBUS_QUEUE_LENGTH * 3);
    CHECK(message->context == &contexts[completed]);
    CHECK(*(unsigned *)message->context == completed);
    CHECK(message->rx_length == 7 && message->adu[3] == 0x12 && message->adu[4] == 0x34);
    completed++;
}
int main(void)
{
    prepare_rtu();
    modbus_callbacks_t callbacks = {.on_rx_packet = complete_in_order, .on_rx_exception = failed};
    unsigned queued = 0, observed = 0, wait = 0;
    /* Refill below capacity, wrapping both ring pointers several times. */
    for(unsigned batch = 0; batch < 4; batch++) {
        unsigned end = queued + MODBUS_QUEUE_LENGTH / 2;
        while(queued < end) {
            contexts[queued] = queued;
            modbus_message_t message = {.tx_length = 8, .rx_length = 7, .crc_check = true,
                .context = &contexts[queued], .adu = {1, 3, 0, (uint8_t)queued, 0, 1, 0, 0}};
            CHECK(modbus_send(&message, &callbacks, false));
            memset(&message, 0xa5, sizeof(message)); /* Sender may reuse its stack immediately. */
            queued++;
        }
        for(unsigned tick = 0; tick < 1000 && completed < end; tick++) {
            poll_rtu();
            if(observed != tx_calls) {
                CHECK(tx_calls == observed + 1);
                CHECK(tx_length == 8 && tx_bytes[3] == observed);
                uint16_t crc = modbus_crc16x(tx_bytes, 6);
                CHECK(tx_bytes[6] == (uint8_t)crc && tx_bytes[7] == (uint8_t)(crc >> 8));
                observed = tx_calls;
                wait = 0;
            }
            if(++wait == 2) inject_reply(false);
        }
        CHECK(completed == end && exceptions == 0);
    }
    for(unsigned tick = 0; tick < 100; tick++) poll_rtu();
    CHECK(completed == queued && tx_calls == queued);
    CHECK(!modbus_isbusy() && engine_irq_depth == 0);
    return EXIT_SUCCESS;
}
