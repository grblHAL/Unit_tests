#include "support/modbus_transaction_host.h"
int main(void)
{
    prepare_bus_transactions();
    uint16_t values[4] = {1, 2, 3, 4};
    CHECK(modbus_message(7, ModBus_WriteRegisters, 16, values, 4, bus_completed) == Status_InvalidStatement);
    CHECK(bus_requests == 0 && bus_callbacks == 0);
    CHECK(modbus_message(7, ModBus_WriteRegisters, 16, values, 3, bus_completed) == Status_OK);
    CHECK(bus_requests == 1 && bus_callbacks == 1 && bus_request.tx_length == MODBUS_MAX_ADU_SIZE);
    const uint8_t expected[] = {7, 16, 0, 16, 0, 3, 6, 0, 1, 0, 2, 0, 3};
    CHECK(memcmp(bus_request.adu, expected, sizeof(expected)) == 0);
    return EXIT_SUCCESS;
}
