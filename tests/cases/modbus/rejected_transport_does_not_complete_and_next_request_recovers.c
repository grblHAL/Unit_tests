#include "support/modbus_transaction_host.h"
int main(void)
{
    prepare_bus_transactions();
    uint16_t value = 0;
    bus_result = BusReject;
    CHECK(modbus_message(7, ModBus_ReadHoldingRegisters, 16, &value, 1, bus_completed) == Status_AccessDenied);
    CHECK(bus_requests == 1 && bus_callbacks == 0);
    bus_result = BusReply;
    CHECK(modbus_message(7, ModBus_ReadHoldingRegisters, 17, &value, 1, bus_completed) == Status_OK);
    CHECK(bus_requests == 2 && bus_callbacks == 1 && bus_response.exception == 0);
    CHECK(bus_response.values[0] == 0x1234);
    return EXIT_SUCCESS;
}
