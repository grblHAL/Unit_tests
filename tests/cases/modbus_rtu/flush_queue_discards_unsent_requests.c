#include "support/rtu_host.h"

int main(void)
{
    prepare_rtu();
    modbus_message_t message = {.tx_length = 8, .rx_length = 7, .crc_check = true, .adu = {1,3,0,0,0,1,0,0}};
    modbus_callbacks_t callbacks = {.on_rx_packet = received, .on_rx_exception = failed};
    CHECK(modbus_send(&message, &callbacks, false));
    CHECK(modbus_send(&message, &callbacks, false));
    modbus_flush_queue();
    for(unsigned i = 0; i < 500; i++) poll_rtu();
    CHECK(tx_calls == 0 && rx_calls == 0 && exceptions == 0);
    return EXIT_SUCCESS;
}
