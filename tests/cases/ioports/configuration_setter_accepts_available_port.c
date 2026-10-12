#include "support/ioports_cfg_host.h"
#include "check.h"

int main(void)
{
    prepare_port_configuration();
    uint8_t port = IOPORT_UNASSIGNED;
    CHECK(port_configuration.set_value(&port_configuration, &port, (pin_cap_t){0}, 1) == Status_OK);
    CHECK(port == 1);
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 2);
    return EXIT_SUCCESS;
}
