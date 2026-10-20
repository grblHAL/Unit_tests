#include "support/ioports_cfg_host.h"

int main(void)
{
    prepare_port_configuration();
    uint8_t selected = 0;
    CHECK(port_configuration.set_value(&port_configuration, &selected, (pin_cap_t){0}, 2) == Status_AuxiliaryPortUnavailable);
    CHECK(selected == 0);
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 2);
    return EXIT_SUCCESS;
}
