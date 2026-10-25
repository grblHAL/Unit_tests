#include "support/rtu_host.h"
#include "system.h"
static unsigned completed, replied_transmissions, realtime_polls;
static modbus_response_t response;
static void completed_read(modbus_response_t *result)
{
    completed++;
    response = *result;
}
static void serve_addressed_reply(sys_state_t state)
{
    (void)state;
    CHECK(++realtime_polls < 2000);
    poll_rtu();
    if(tx_calls != replied_transmissions) {
        CHECK(tx_calls == replied_transmissions + 1 && tx_length == 8);
        CHECK(tx_bytes[1] == ModBus_ReadHoldingRegisters && tx_bytes[3] == 16);
        uint16_t tx_crc = modbus_crc16x(tx_bytes, 6);
        CHECK(tx_bytes[6] == (uint8_t)tx_crc && tx_bytes[7] == (uint8_t)(tx_crc >> 8));
        inject_reply(false);
        rx_bytes[0] = tx_bytes[0];
        uint16_t crc = modbus_crc16x(rx_bytes, 5);
        rx_bytes[5] = (uint8_t)crc;
        rx_bytes[6] = (uint8_t)(crc >> 8);
        replied_transmissions = tx_calls;
    }
}
int main(void)
{
    prepare_rtu();
    grbl.on_execute_realtime = serve_addressed_reply;
    uint16_t values[1] = {0};
    CHECK(modbus_message(7, ModBus_ReadHoldingRegisters, 16, values, 1, completed_read) == Status_OK);
    CHECK(completed == 1 && response.num_values == 1 && response.values[0] == 0x1234);
    response = (modbus_response_t){0};
    CHECK(modbus_message(200, ModBus_ReadHoldingRegisters, 16, values, 1, completed_read) == Status_OK);
    CHECK(tx_calls == 2 && tx_bytes[0] == 200 && rx_position == 7);
    unsigned high_address_callbacks = completed - 1;
    modbus_response_t high_address_response = response;
    unsigned before_recovery = completed;
    CHECK(modbus_message(7, ModBus_ReadHoldingRegisters, 16, values, 1, completed_read) == Status_OK);
    CHECK(tx_calls == 3 && completed == before_recovery + 1);
    CHECK(response.exception == 0 && response.function == ModBus_ReadHoldingRegisters);
    CHECK(response.num_values == 1 && response.values[0] == 0x1234);
    char stats[] = "$MODBUSSTATS";
    CHECK(system_execute_line(stats, hal.stream.write) == Status_OK);
    CHECK(strstr(engine_output, "TX: 3") && replied_transmissions == 3 && rx_position == 7);
    CHECK(strstr(engine_output, "CRC errors: 0") && strstr(engine_output, "timeouts: 0"));
    fprintf(stderr, "RTU server200 callbacks=%u; three CRC-valid replies, server7 controls completed\n",
        high_address_callbacks);
    CHECK(high_address_callbacks == 1);
    CHECK(high_address_response.exception == 0 && high_address_response.function == ModBus_ReadHoldingRegisters);
    CHECK(high_address_response.num_values == 1 && high_address_response.values[0] == 0x1234);
    return EXIT_SUCCESS;
}
