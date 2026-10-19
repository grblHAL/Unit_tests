#include "support/modbus_transaction_host.h"
int main(void)
{
    prepare_bus_transactions();
    uint16_t values[MODBUS_MAX_REGISTERS] = {0};
    CHECK(modbus_message(7, ModBus_ReadHoldingRegisters, 16, values, MODBUS_MAX_REGISTERS, bus_completed) == Status_OK);
    CHECK(bus_requests == 1 && bus_callbacks == 1 && bus_response.num_values == MODBUS_MAX_REGISTERS);
    for(unsigned i = 0; i < MODBUS_MAX_REGISTERS; i++) CHECK(bus_response.values[i] == bus_read_values[i]);
    CHECK(bus_request.rx_length == 5 + 2 * MODBUS_MAX_REGISTERS);
    return EXIT_SUCCESS;
}
