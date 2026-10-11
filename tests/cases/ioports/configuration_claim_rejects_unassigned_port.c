#include "support/ioports_cfg_host.h"
#include "check.h"

int main(void)
{
    prepare_port_configuration();
    uint8_t port = IOPORT_UNASSIGNED;
    CHECK(port_configuration.claim(&port_configuration, &port, "relay", (pin_cap_t){0}) == NULL);
    CHECK(port == IOPORT_UNASSIGNED);
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 2);
    return EXIT_SUCCESS;
}
