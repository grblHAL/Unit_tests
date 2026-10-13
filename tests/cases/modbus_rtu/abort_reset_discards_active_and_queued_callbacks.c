#include "support/rtu_host.h"
static unsigned resets;
static void original_reset(void) { resets++; }

int main(void)
{
    prepare_rtu_with_reset(original_reset);
    send_request();
    modbus_message_t message = {.tx_length = 8, .rx_length = 7, .crc_check = true, .adu = {2,3,0,0,0,1,0,0}};
    modbus_callbacks_t callbacks = {.on_rx_packet = received, .on_rx_exception = failed};
    CHECK(modbus_send(&message, &callbacks, false));
    inject_reply(false);
    sys.abort = true;
    reset_rtu_driver();
    CHECK(resets == 1 && rx_count() == 0);
    sys.abort = false;
    for(unsigned i = 0; i < 600; i++) poll_rtu();
    CHECK(tx_calls == 1 && rx_calls == 0 && exceptions == 0);
    message.adu[0] = 1;
    CHECK(modbus_send(&message, &callbacks, false));
    poll_rtu(); poll_rtu();
    CHECK(tx_calls == 2);
    inject_reply(false); poll_rtu();
    CHECK(rx_calls == 1 && exceptions == 0);
    return EXIT_SUCCESS;
}
