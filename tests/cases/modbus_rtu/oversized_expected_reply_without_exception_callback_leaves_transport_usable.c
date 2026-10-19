#include "support/rtu_host.h"
int main(void)
{
    prepare_rtu();
    modbus_message_t message = {.tx_length = 8, .rx_length = MODBUS_MAX_ADU_SIZE + 1,
        .adu = {1, 3, 0, 0, 0, 1, 0, 0}};
    modbus_callbacks_t callbacks = {.on_rx_packet = received};
    CHECK(!modbus_send(&message, &callbacks, false));
    CHECK(tx_calls == 0 && rx_calls == 0 && exceptions == 0);
    send_request(); inject_reply(false);
    for(unsigned tick = 0; tick < 20 && !rx_calls; tick++) poll_rtu();
    CHECK(rx_calls == 1 && exceptions == 0);
    return EXIT_SUCCESS;
}
