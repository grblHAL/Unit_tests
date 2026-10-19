#include "support/rtu_blocking_host.h"
int main(void)
{
    prepare_rtu();
    modbus_message_t message = {.tx_length = 8, .rx_length = 7, .crc_check = true,
        .adu = {1, 3, 0, 0, 0, 1, 0, 0}};
    grbl.on_execute_realtime = blocking_realtime;
    CHECK(!modbus_send(&message, NULL, true));
    CHECK(tx_calls == 1 && exceptions == 0 && rx_calls == 0);
    reply_on_transmission = 2;
    CHECK(send_blocking_request(0));
    CHECK(tx_calls == 2 && rx_calls == 1 && exceptions == 0);
    return EXIT_SUCCESS;
}
