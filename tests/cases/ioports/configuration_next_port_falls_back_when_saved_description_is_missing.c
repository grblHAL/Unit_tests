#include "support/ioports_cfg_host.h"

int main(void)
{
    prepare_port_configuration();
    digital_pins[Port_Output][0].cap.pwm = true;
    CHECK(port_configuration.get_next(&port_configuration, IOPORT_UNASSIGNED, "Removed accessory", (pin_cap_t){.pwm = true}) == 0);
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 2);
    return EXIT_SUCCESS;
}
