#include "support/modbus_transaction_host.h"
int main(void)
{
    prepare_bus_transactions();
    uint16_t value = 0x5678;
    bus_result = BusException;
    CHECK(modbus_message(7, ModBus_WriteRegister, 0x1234, &value, 1, bus_completed) == Status_OK);
    CHECK(bus_response.exception == ModBus_IllegalDataAddress);
    bus_result = BusReply;
    CHECK(modbus_message(7, ModBus_WriteRegister, 0x1234, &value, 1, bus_completed) == Status_OK);
    CHECK(bus_callbacks == 2 && bus_response.exception == 0);
    CHECK(bus_response.function == ModBus_WriteRegister && bus_response.num_values == 2);
    CHECK(bus_response.values[0] == 0x1234 && bus_response.values[1] == value);
    return EXIT_SUCCESS;
}
