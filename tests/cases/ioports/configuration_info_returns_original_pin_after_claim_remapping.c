#include "support/ioports_cfg_host.h"
#include "check.h"

int main(void)
{
    prepare_port_configuration();
    uint8_t claimed = 0;
    CHECK(ioport_claim(Port_Digital, Port_Output, &claimed, "relay") != NULL);
    CHECK(port_configuration.get_info(&port_configuration, 0) == &digital_pins[Port_Output][0]);
    CHECK(port_configuration.get_info(&port_configuration, 1) == &digital_pins[Port_Output][1]);
    return EXIT_SUCCESS;
}
