#include "support/modbus_transaction_host.h"
int main(void)
{
    prepare_bus_transactions();
    uint16_t value = 0;
    CHECK(modbus_message(7, ModBus_ReadInputRegisters, 16, &value, 1, bus_completed) == Status_OK);
    CHECK(bus_response.num_values == 1 && bus_response.values[0] == 0x1234);
    bus_result = BusTimeout;
    CHECK(modbus_message(7, ModBus_ReadInputRegisters, 17, &value, 1, bus_completed) == Status_OK);
    CHECK(bus_callbacks == 2 && bus_response.exception == ModBus_Timeout);
    CHECK(bus_response.num_values == 0 && bus_response.values[0] == 0);
    return EXIT_SUCCESS;
}
