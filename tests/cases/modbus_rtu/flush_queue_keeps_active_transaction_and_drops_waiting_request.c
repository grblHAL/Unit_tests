#include "support/rtu_host.h"

int main(void)
{
    prepare_rtu();
    send_request();
    modbus_message_t message = {.tx_length = 8, .rx_length = 7, .crc_check = true, .adu = {2,3,0,0,0,1,0,0}};
    modbus_callbacks_t callbacks = {.on_rx_packet = received, .on_rx_exception = failed};
    CHECK(modbus_send(&message, &callbacks, false));
    modbus_flush_queue();
    inject_reply(false);
    poll_rtu();
    for(unsigned i = 0; i < 500; i++) poll_rtu();
    CHECK(tx_calls == 1 && rx_calls == 1 && exceptions == 0);
    CHECK(reply.adu[0] == 1);
    return EXIT_SUCCESS;
}
