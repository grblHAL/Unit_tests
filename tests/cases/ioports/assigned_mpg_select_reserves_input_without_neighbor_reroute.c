#include "support/ioports_assignment_host.h"

int main(void)
{
    xbar_t *pin = prepare_assignment(Port_Input);
    control_signals_t previous = hal.signals_cap;
    CHECK(ioport_set_function(pin, Input_MPGSelect, (driver_caps_t){0}));
    CHECK(assignment_calls == 1 && assigned_function == Input_MPGSelect);
    CHECK(pin->function == Input_MPGSelect && hal.signals_cap.mask == previous.mask);
    CHECK(!ioport_claimable(Port_Digital, Port_Input, 0));
    CHECK(ioport_claimable(Port_Digital, Port_Input, 1));
    CHECK(ioports_available(Port_Digital, Port_Input) == 1);
    uint8_t neighbor = 1;
    CHECK(ioport_claim(Port_Digital, Port_Input, &neighbor, "Panel sensor") == &digital_pins[Port_Input][1]);
    CHECK(ioport_wait_on_input(Port_Digital, neighbor, WaitMode_Immediate, 0) == 1);
    CHECK(read_calls == 1 && physical_input == 1 && input_mode == WaitMode_Immediate);
    CHECK(pin->function == Input_MPGSelect && assignment_calls == 1);
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 2 && output_calls == 0);
    return EXIT_SUCCESS;
}
