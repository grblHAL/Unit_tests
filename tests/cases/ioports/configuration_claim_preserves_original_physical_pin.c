#include "support/ioports_cfg_host.h"
#include "check.h"

int main(void)
{
    prepare_port_configuration();
    uint8_t port = 0;
    xbar_t *pin = port_configuration.claim(&port_configuration, &port, "relay", (pin_cap_t){0});
    CHECK(pin == &digital_pins[Port_Output][0]);
    CHECK(pin->mode.claimed);
    CHECK(strcmp(pin->description, "relay") == 0);
    CHECK(ioport_digital_out(port, true));
    CHECK(physical_output == 0 && output_value);
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 1);
    return EXIT_SUCCESS;
}
