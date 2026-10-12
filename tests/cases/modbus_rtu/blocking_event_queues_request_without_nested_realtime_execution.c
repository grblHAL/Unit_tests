#include "support/rtu_host.h"
#include "system.h"

int main(void)
{
    prepare_rtu();
    sys.blocking_event = true;
    modbus_message_t message = {.tx_length = 8, .rx_length = 7, .crc_check = true, .adu = {1,3,0,0,0,1,0,0}};
    modbus_callbacks_t callbacks = {.on_rx_packet = received, .on_rx_exception = failed};
    CHECK(modbus_send(&message, &callbacks, true));
    CHECK(tx_calls == 0 && rx_calls == 0);
    sys.blocking_event = false;
    poll_rtu(); poll_rtu();
    CHECK(tx_calls == 1);
    inject_reply(false); poll_rtu();
    CHECK(rx_calls == 1 && exceptions == 0);
    return EXIT_SUCCESS;
}
