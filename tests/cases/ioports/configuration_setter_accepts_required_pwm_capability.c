#include "support/ioports_cfg_host.h"
#include "check.h"

int main(void)
{
    prepare_port_configuration();
    digital_pins[Port_Output][1].cap.pwm = true;
    uint8_t port = 0;
    CHECK(port_configuration.set_value(&port_configuration, &port, (pin_cap_t){.pwm = true}, 1) == Status_OK);
    CHECK(port == 1);
    return EXIT_SUCCESS;
}
