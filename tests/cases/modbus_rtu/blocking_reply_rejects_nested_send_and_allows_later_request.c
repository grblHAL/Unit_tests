#include "support/rtu_blocking_host.h"

static unsigned nested_attempts;
static void receive_and_attempt_nested_send(modbus_message_t *message)
{
    received(message);
    modbus_message_t nested = {.tx_length = 8, .rx_length = 7,
        .crc_check = true, .adu = {2,3,0,0,0,1,0,0}};
    modbus_callbacks_t callbacks = {.on_rx_packet = received, .on_rx_exception = failed};
    unsigned before = tx_calls;
    nested_attempts++;
    CHECK(!modbus_send(&nested, &callbacks, true));
    CHECK(tx_calls == before);
}
int main(void)
{
    prepare_rtu();
    reply_on_transmission = 1;
    grbl.on_execute_realtime = blocking_realtime;
    modbus_message_t message = {.tx_length = 8, .rx_length = 7,
        .crc_check = true, .adu = {1,3,0,0,0,1,0,0}};
    modbus_callbacks_t callbacks = {.on_rx_packet = receive_and_attempt_nested_send,
        .on_rx_exception = failed};
    CHECK(modbus_send(&message, &callbacks, true));
    CHECK(nested_attempts == 1);
    CHECK(tx_calls == 1 && rx_calls == 1 && exceptions == 0);
    CHECK(reply.adu[3] == 0x12 && reply.adu[4] == 0x34);
    reply_on_transmission = 2;
    CHECK(send_blocking_request(0));
    CHECK(nested_attempts == 1);
    CHECK(tx_calls == 2 && rx_calls == 2 && exceptions == 0);
    return EXIT_SUCCESS;
}
