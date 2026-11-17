#include "support/rtu_host.h"
#include "system.h"

static unsigned service_calls;
static bool partial_injected;
static void service_partial_normal_reply(sys_state_t state)
{
    (void)state;
    CHECK(++service_calls < 2000);
    poll_rtu();
    if(tx_calls && service_calls >= 2 && !partial_injected) {
        const uint8_t partial[] = {1, 3, 2, 0x12, 0x34};
        memcpy(rx_bytes, partial, sizeof(partial));
        rx_position = 0;
        rx_length = sizeof(partial);
        partial_injected = true;
    }
}
int main(void)
{
    prepare_rtu();
    modbus_message_t message = {.tx_length = 8, .rx_length = 7, .crc_check = true,
        .adu = {1, 3, 0, 0, 0, 1, 0, 0}};
    modbus_callbacks_t callbacks = {.on_rx_packet = received, .on_rx_exception = failed};
    grbl.on_execute_realtime = service_partial_normal_reply;
    CHECK(!modbus_send(&message, &callbacks, true));
    CHECK(partial_injected && tx_calls == 1 && rx_calls == 0 && exceptions == 1);
    CHECK(exception_code == ModBus_Timeout);
    for(unsigned tick = 0; tick < 4; tick++) poll_rtu();
    char command[] = "$MODBUSSTATS";
    CHECK(system_execute_line(command, hal.stream.write) == Status_OK);
    CHECK(strstr(engine_output, "No connection to modbus device?") == NULL);
    CHECK(strstr(engine_output, "timeouts: 1") != NULL);
    CHECK(strstr(engine_output, "RX exceptions: 0") != NULL);
    CHECK(strstr(engine_output, "CRC errors: 0") != NULL);
    return EXIT_SUCCESS;
}
