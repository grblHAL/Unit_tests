#include "support/ioports_assignment_host.h"
#include "check.h"

int main(void)
{
    xbar_t *pin = prepare_assignment(Port_Output);
    CHECK(ioport_claimable(Port_Digital, Port_Output, 0));
    CHECK(ioport_set_function(pin, Output_CoolantMist, (driver_caps_t){0}));
    CHECK(!ioport_claimable(Port_Digital, Port_Output, 0));
    CHECK(ioport_claimable(Port_Digital, Port_Output, 1));
    return EXIT_SUCCESS;
}
