#include "support/modbus_transaction_host.h"
int main(void)
{
    prepare_bus_transactions();
    uint16_t values[2] = {0xA55A, 0x3CC3};
    CHECK(modbus_message(7, ModBus_WriteCoils, 0x1234, values, 32, bus_completed) == Status_OK);
    const uint8_t expected[] = {7, 15, 0x12, 0x34, 0, 32, 4, 0x5A, 0xA5, 0xC3, 0x3C};
    CHECK(memcmp(bus_request.adu, expected, sizeof(expected)) == 0);
    CHECK(bus_request.tx_length == 13 && bus_request.rx_length == 8);
    CHECK(bus_response.function == ModBus_WriteCoils && bus_response.values[0] == 0x1234 && bus_response.values[1] == 32);
    return EXIT_SUCCESS;
}
