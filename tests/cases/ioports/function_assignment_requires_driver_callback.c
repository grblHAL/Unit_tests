#include "support/ioports_assignment_host.h"
#include "check.h"

int main(void)
{
    xbar_t *pin = prepare_assignment(Port_Output);
    pin->set_function = NULL;
    CHECK(!ioport_set_function(pin, Output_CoolantMist, (driver_caps_t){0}));
    CHECK(assignment_calls == 0);
    CHECK(pin->function == Output_Aux0);
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 2);
    return EXIT_SUCCESS;
}
