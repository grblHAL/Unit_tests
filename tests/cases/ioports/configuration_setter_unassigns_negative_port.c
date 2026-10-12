#include "support/ioports_cfg_host.h"
#include "check.h"

int main(void)
{
    prepare_port_configuration();
    uint8_t port = 1;
    CHECK(port_configuration.set_value(&port_configuration, &port, (pin_cap_t){0}, -1) == Status_OK);
    CHECK(port == IOPORT_UNASSIGNED);
    return EXIT_SUCCESS;
}
