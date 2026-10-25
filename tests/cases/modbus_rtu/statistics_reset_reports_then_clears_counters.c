#include "support/rtu_host.h"
#include "system.h"

int main(void)
{
    prepare_rtu();
    send_request(); inject_reply(false); poll_rtu();
    char reset[] = "$MODBUSSTATS=R";
    CHECK(system_execute_line(reset, hal.stream.write) == Status_OK);
    CHECK(strstr(engine_output, "TX: 1") != NULL);
    engine_output[0] = '\0';
    char report[] = "$MODBUSSTATS";
    CHECK(system_execute_line(report, hal.stream.write) == Status_OK);
    CHECK(strstr(engine_output, "TX: 0") != NULL);
    CHECK(strstr(engine_output, "CRC errors: 0") != NULL);
    for(unsigned tick = 0; tick < 20; tick++) poll_rtu();
    modbus_message_t message = {.tx_length = 8, .rx_length = 7, .crc_check = true,
        .adu = {1, 3, 0, 0, 0, 1, 0, 0}};
    const modbus_callbacks_t callbacks = {.on_rx_packet = received, .on_rx_exception = failed};
    CHECK(modbus_send(&message, &callbacks, false));
    poll_rtu(); poll_rtu();
    CHECK(tx_calls == 2);
    inject_reply(true); poll_rtu();
    CHECK(rx_calls == 1 && exceptions == 1 && exception_code == ModBus_CRCError);
    engine_output[0] = 0;
    char lower_reset[] = "$MODBUSSTATS=r";
    CHECK(system_execute_line(lower_reset, hal.stream.write) == Status_OK);
    CHECK(strstr(engine_output, "TX: 1") != NULL);
    CHECK(strstr(engine_output, "CRC errors: 1") != NULL);
    engine_output[0] = 0;
    char after_reset[] = "$MODBUSSTATS";
    CHECK(system_execute_line(after_reset, hal.stream.write) == Status_OK);
    CHECK(strstr(engine_output, "TX: 0") != NULL);
    CHECK(strstr(engine_output, "CRC errors: 0") != NULL);
    return EXIT_SUCCESS;
}
