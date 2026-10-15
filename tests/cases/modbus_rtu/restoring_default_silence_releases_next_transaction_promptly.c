#include "support/rtu_host.h"

int main(void)
{
    prepare_rtu();
    modbus_silence_timeout_t silence = {.b19200 = 10};
    modbus_set_silence(&silence);
    modbus_set_silence(NULL);
    send_request();
    inject_reply(false);
    poll_rtu();
    CHECK(rx_calls == 1);
    modbus_message_t next = {.tx_length = 8, .rx_length = 7, .crc_check = true,
        .adu = {2, 3, 0, 0, 0, 1, 0, 0}};
    modbus_callbacks_t callbacks = {.on_rx_packet = received, .on_rx_exception = failed};
    CHECK(modbus_send(&next, &callbacks, false));
    for(unsigned i = 0; i < 5; i++) poll_rtu();
    CHECK(tx_calls == 2);
    CHECK(tx_bytes[0] == 2 && exceptions == 0);
    return EXIT_SUCCESS;
}
