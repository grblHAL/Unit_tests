#include "support/ioports_cfg_host.h"

int main(void)
{
    prepare_port_configuration();
    CHECK(ioport_set_description(Port_Digital, Port_Output, 0, "Dust extraction"));
    CHECK(port_configuration.get_next(&port_configuration, IOPORT_UNASSIGNED, "Dust extraction", (pin_cap_t){0}) == 0);
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 2);
    return EXIT_SUCCESS;
}
