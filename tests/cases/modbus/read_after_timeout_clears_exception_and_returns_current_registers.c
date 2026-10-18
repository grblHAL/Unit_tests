#include "support/modbus_transaction_host.h"
int main(void)
{
    prepare_bus_transactions();
    uint16_t values[2] = {0};
    bus_result = BusTimeout;
    CHECK(modbus_message(7, ModBus_ReadHoldingRegisters, 16, values, 2, bus_completed) == Status_OK);
    CHECK(bus_callbacks == 1 && bus_response.exception == ModBus_Timeout);
    bus_result = BusReply;
    CHECK(modbus_message(7, ModBus_ReadHoldingRegisters, 16, values, 2, bus_completed) == Status_OK);
    CHECK(bus_callbacks == 2 && bus_requests == 2 && bus_response.exception == 0);
    CHECK(bus_response.function == ModBus_ReadHoldingRegisters && bus_response.num_values == 2);
    CHECK(bus_response.values[0] == 0x1234 && bus_response.values[1] == 0x5678);
    return EXIT_SUCCESS;
}
