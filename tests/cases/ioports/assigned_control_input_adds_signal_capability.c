#include "support/ioports_assignment_host.h"
#include "check.h"

int main(void)
{
    xbar_t *pin = prepare_assignment(Port_Input);
    control_signals_t capabilities = {0};
    capabilities.feed_hold = true;
    hal.signals_cap.feed_hold = false;
    CHECK(ioport_set_function(pin, Input_FeedHold, (driver_caps_t){.control = &capabilities}));
    CHECK(pin->function == Input_FeedHold);
    CHECK(hal.signals_cap.feed_hold);
    CHECK(assignment_calls == 1);
    CHECK(ioports_available(Port_Digital, Port_Input) == 1);
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 2);
    return EXIT_SUCCESS;
}
