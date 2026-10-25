#include "support/rtu_blocking_host.h"

static void echo_written_register(sys_state_t state)
{
    blocking_realtime(state);
    if(tx_calls == 1 && attempt_ticks >= 2 && !reply_injected) {
        CHECK(tx_length == 8 && tx_bytes[1] == 6);
        memcpy(rx_bytes, tx_bytes, tx_length);
        rx_position = 0;
        rx_length = tx_length;
        reply_injected = true;
    }
}

int main(void)
{
    prepare_rtu();
    modbus_message_t write = {.tx_length = 8, .rx_length = 8, .crc_check = true,
        .adu = {1, 6, 0, 10, 0x12, 0x34, 0, 0}};
    modbus_callbacks_t callbacks = {.on_rx_exception = failed};
    grbl.on_execute_realtime = echo_written_register;
    CHECK(modbus_send(&write, &callbacks, true));
    CHECK(tx_calls == 1 && rx_calls == 0 && exceptions == 0);
    CHECK(tx_bytes[2] == 0 && tx_bytes[3] == 10);
    CHECK(tx_bytes[4] == 0x12 && tx_bytes[5] == 0x34);
    reply_on_transmission = 2;
    CHECK(send_blocking_request(0));
    CHECK(tx_calls == 2 && rx_calls == 1 && exceptions == 0);
    CHECK(reply.adu[3] == 0x12 && reply.adu[4] == 0x34);
    return EXIT_SUCCESS;
}
