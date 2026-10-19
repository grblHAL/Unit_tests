#include "support/ioports_cfg_host.h"
#include "support/ioports_assignment_host.h"

int main(void)
{
    xbar_t *pin = prepare_assignment(Port_Output);
    CHECK(ioports_cfg(&port_configuration, Port_Digital, Port_Output) == &port_configuration);
    CHECK(ioport_set_function(pin, Output_CoolantMist, (driver_caps_t){0}));
    CHECK(!ioport_claimable(Port_Digital, Port_Output, 0));
    uint8_t selected = IOPORT_UNASSIGNED;
    CHECK(port_configuration.set_value(&port_configuration, &selected, (pin_cap_t){0}, 0) == Status_AuxiliaryPortUnavailable);
    CHECK(selected == IOPORT_UNASSIGNED);
    CHECK(pin->function == Output_CoolantMist);
    return EXIT_SUCCESS;
}
