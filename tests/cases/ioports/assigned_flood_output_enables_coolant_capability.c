#include "support/ioports_assignment_host.h"
#include "check.h"

int main(void)
{
    xbar_t *pin = prepare_assignment(Port_Output);
    hal.coolant_cap.flood = false;
    CHECK(ioport_set_function(pin, Output_CoolantFlood, (driver_caps_t){0}));
    CHECK(assignment_calls == 1 && assigned_function == Output_CoolantFlood);
    CHECK(pin->function == Output_CoolantFlood);
    CHECK(hal.coolant_cap.flood);
    CHECK(ioports_available(Port_Digital, Port_Output) == 1);
    return EXIT_SUCCESS;
}
