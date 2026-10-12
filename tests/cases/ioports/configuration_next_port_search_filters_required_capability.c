#include "support/ioports_cfg_host.h"
#include "check.h"

int main(void)
{
    prepare_port_configuration();
    digital_pins[Port_Output][0].cap.pwm = true;
    CHECK(port_configuration.get_next(&port_configuration, IOPORT_UNASSIGNED, NULL, (pin_cap_t){.pwm = true}) == 0);
    CHECK(port_configuration.get_next(&port_configuration, IOPORT_UNASSIGNED, NULL, (pin_cap_t){.servo_pwm = true}) == IOPORT_UNASSIGNED);
    return EXIT_SUCCESS;
}
