#include "support/rtu_host.h"
int main(void)
{
    prepare_rtu();
    modbus_message_t message = {.tx_length = 8, .rx_length = 7, .crc_check = true,
        .adu = {1, 3, 0, 0, 0, 1, 0, 0}};
    CHECK(modbus_send(&message, NULL, false));
    poll_rtu(); poll_rtu();
    CHECK(tx_calls == 1);
    inject_reply(false);
    poll_rtu();
    CHECK(rx_calls == 0 && exceptions == 0);
    for(unsigned tick = 0; tick < 20; tick++) poll_rtu();
    CHECK(modbus_send(&message, NULL, false));
    poll_rtu(); poll_rtu();
    CHECK(tx_calls == 2);
    for(unsigned tick = 0; tick < 500; tick++) poll_rtu();
    CHECK(!modbus_isbusy());
    CHECK(rx_calls == 0 && exceptions == 0);
    modbus_callbacks_t callbacks = {.on_rx_packet = received, .on_rx_exception = failed};
    CHECK(modbus_send(&message, &callbacks, false));
    poll_rtu(); poll_rtu();
    CHECK(tx_calls == 3);
    inject_reply(false);
    poll_rtu();
    CHECK(rx_calls == 1 && exceptions == 0);
    CHECK(reply.adu[3] == 0x12 && reply.adu[4] == 0x34);
    return EXIT_SUCCESS;
}
