#include "support/rtu_exception_host.h"
int main(void)
{
    prepare_rtu();
    device_exception = 2;
    grbl.on_execute_realtime = service_device_exception;
    modbus_message_t message = {.tx_length = 8, .rx_length = 7, .crc_check = true,
        .adu = {1, 3, 0, 0, 0, 1, 0, 0}};
    const modbus_callbacks_t ignored = {.on_rx_exception = modbus_null_exception_handler};
    for(unsigned attempt = 0; attempt < 2; attempt++) {
        exception_frame_injected = false;
        exception_attempt_ticks = exception_service_calls = 0;
        CHECK(!modbus_send(&message, attempt ? &ignored : NULL, true));
        CHECK(exception_frame_injected && tx_calls == attempt + 1 && exceptions == 0 && rx_calls == 0);
        for(unsigned tick = 0; tick < 500; tick++) poll_rtu();
    }
    modbus_callbacks_t callbacks = {.on_rx_packet = received, .on_rx_exception = failed};
    CHECK(modbus_send(&message, &callbacks, false));
    for(unsigned tick = 0; tick < 20 && tx_calls < 3; tick++) poll_rtu();
    CHECK(tx_calls == 3);
    poll_rtu(); inject_reply(false);
    for(unsigned tick = 0; tick < 20 && !rx_calls; tick++) poll_rtu();
    CHECK(rx_calls == 1 && exceptions == 0);
    return EXIT_SUCCESS;
}
