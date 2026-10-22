#include "support/modbus_transaction_host.h"

static uint8_t reply_function;
static bool transport_send(modbus_message_t *message, const modbus_callbacks_t *callbacks, bool block)
{
    if(reply_function == ModBus_ReadHoldingRegisters)
        return bus_send_transaction(message, callbacks, block);
    CHECK(block && callbacks != NULL);
    bus_requests++;
    modbus_message_t reply = {.adu = {message->adu[0], reply_function, 0}, .rx_length = 5};
    callbacks->on_rx_packet(&reply);
    return true;
}

int main(void)
{
    const modbus_api_t api = {.interface = Modbus_InterfaceRTU, .send = transport_send};
    CHECK(modbus_register_api(&api));
    uint16_t values[1] = {0};
    const uint8_t invalid_functions[] = {0, 255};
    for(unsigned i = 0; i < sizeof(invalid_functions); i++) {
        reply_function = invalid_functions[i];
        CHECK(modbus_message(7, ModBus_ReadHoldingRegisters, 16, values, 1, bus_completed) == Status_OK);
        CHECK(bus_callbacks == 2 * i + 1 && bus_response.exception == 255);
        CHECK(bus_response.num_values == 0);
        reply_function = ModBus_ReadHoldingRegisters;
        CHECK(modbus_message(7, ModBus_ReadHoldingRegisters, 16, values, 1, bus_completed) == Status_OK);
        CHECK(bus_callbacks == 2 * i + 2 && bus_response.exception == 0);
        CHECK(bus_response.function == ModBus_ReadHoldingRegisters && bus_response.num_values == 1);
        CHECK(bus_response.values[0] == 0x1234);
    }
    CHECK(bus_requests == 4);
    return EXIT_SUCCESS;
}
