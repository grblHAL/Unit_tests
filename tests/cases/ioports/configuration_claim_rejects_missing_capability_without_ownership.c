#include "support/ioports_cfg_host.h"
#include "check.h"

int main(void)
{
    prepare_port_configuration();
    uint8_t port = 0;
    CHECK(port_configuration.claim(&port_configuration, &port, "relay", (pin_cap_t){.pwm = true}) == NULL);
    CHECK(port == 0);
    CHECK(!digital_pins[Port_Output][0].mode.claimed);
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 2);
    return EXIT_SUCCESS;
}
