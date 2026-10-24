#include "support/rtu_host.h"
#include "system.h"

int main(void)
{
    prepare_rtu();
    modbus_message_t message = {.tx_length = 8, .rx_length = 7, .crc_check = true,
        .adu = {1, 3, 0, 0, 0, 1, 0, 0}};
    const modbus_callbacks_t callbacks = {.on_rx_packet = received};
    for(unsigned byte = 5; byte <= 6; byte++) {
        CHECK(modbus_send(&message, &callbacks, false));
        poll_rtu(); poll_rtu();
        CHECK(tx_calls == byte - 4);
        inject_reply(false);
        rx_bytes[byte] ^= 1;
        poll_rtu();
        CHECK(rx_calls == 0 && exceptions == 0);
        for(unsigned tick = 0; tick < 20; tick++) poll_rtu();
        CHECK(!modbus_isbusy());
    }
    char statistics[] = "$MODBUSSTATS";
    CHECK(system_execute_line(statistics, hal.stream.write) == Status_OK);
    CHECK(strstr(engine_output, "CRC errors: 2") != NULL);
    CHECK(strstr(engine_output, "timeouts: 0") != NULL);
    CHECK(modbus_send(&message, &callbacks, false));
    poll_rtu(); poll_rtu();
    CHECK(tx_calls == 3);
    inject_reply(false); poll_rtu();
    CHECK(rx_calls == 1 && exceptions == 0);
    CHECK(reply.rx_length == 7 && reply.adu[3] == 0x12 && reply.adu[4] == 0x34);
    for(unsigned tick = 0; tick < 20; tick++) poll_rtu();
    CHECK(!modbus_isbusy());
    return EXIT_SUCCESS;
}
