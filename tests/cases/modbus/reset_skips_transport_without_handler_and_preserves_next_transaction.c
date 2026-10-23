#include "support/modbus_transaction_host.h"
static unsigned reset_calls, tcp_attempts;
static bool last_abort;
static bool transport_up(void) { return true; }
static bool decline_tcp(modbus_message_t *message, const modbus_callbacks_t *callbacks, bool block)
{
    CHECK(message != NULL && callbacks != NULL && block);
    tcp_attempts++;
    return false; /* This server belongs to the RTU transport. */
}
static void reset_tcp(bool abort) { reset_calls++; last_abort = abort; }

int main(void)
{
    const modbus_api_t rtu = {.interface = Modbus_InterfaceRTU,
        .is_up = transport_up, .send = bus_send_transaction};
    const modbus_api_t tcp = {.interface = Modbus_InterfaceTCP,
        .is_up = transport_up, .reset = reset_tcp, .send = decline_tcp};
    CHECK(modbus_register_api(&rtu) && modbus_register_api(&tcp));
    for(unsigned abort = 0; abort < 2; abort++) {
        modbus_reset(abort != 0);
        CHECK(reset_calls == abort + 1 && last_abort == (abort != 0));
        CHECK(modbus_isup().rtu && modbus_isup().tcp);
        CHECK(!modbus_isbusy());
        uint16_t value = (uint16_t)(0x5678 + abort);
        CHECK(modbus_message(7, ModBus_WriteRegister, 0x1234, &value, 1, bus_completed) == Status_OK);
        CHECK(bus_callbacks == abort + 1 && bus_requests == abort + 1);
        CHECK(tcp_attempts == abort + 1);
        CHECK(bus_response.exception == ModBus_NoException);
        CHECK(bus_response.function == ModBus_WriteRegister && bus_response.num_values == 2);
        CHECK(bus_response.values[0] == 0x1234 && bus_response.values[1] == value);
    }
    return EXIT_SUCCESS;
}
