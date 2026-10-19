#include "support/modbus_transaction_host.h"
int main(void)
{
    prepare_bus_transactions();
    uint16_t value = 0;
    CHECK(modbus_message(7, ModBus_ReadHoldingRegisters, 16, &value, 1, NULL) == Status_OK);
    bus_result = BusTimeout;
    CHECK(modbus_message(7, ModBus_ReadHoldingRegisters, 16, &value, 1, NULL) == Status_OK);
    bus_result = BusException;
    CHECK(modbus_message(7, ModBus_ReadHoldingRegisters, 16, &value, 1, NULL) == Status_OK);
    CHECK(bus_requests == 3 && bus_callbacks == 0);
    return EXIT_SUCCESS;
}
