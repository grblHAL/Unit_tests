#include "support/rtu_host.h"
static unsigned described;
static void describe_modbus_pin(pin_function_t function, pin_group_t group, const char *description)
{
    CHECK(group == PinGroup_UART);
    CHECK(strcmp(description, "Modbus") == 0);
    CHECK(function == Output_TX || function == Input_RX);
    unsigned bit = function == Output_TX ? 1 : 2;
    CHECK(!(described & bit));
    described |= bit;
}
static void configure_pin_descriptions(void) { hal.periph_port.set_pin_description = describe_modbus_pin; }
int main(void)
{
    prepare_rtu_transport(NULL, -2, configure_pin_descriptions);
    CHECK(described == 3);
    send_request(); inject_reply(false);
    for(unsigned tick = 0; tick < 20 && !rx_calls; tick++) poll_rtu();
    CHECK(rx_calls == 1 && exceptions == 0);
    return EXIT_SUCCESS;
}
