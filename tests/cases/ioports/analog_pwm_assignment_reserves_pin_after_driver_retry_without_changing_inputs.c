#include "support/multi_bank_ioports_host.h"
static bool assignment_allowed;
static unsigned assignment_calls;
static bool assign_spindle_pwm(xbar_t *pin, pin_function_t function)
{
    CHECK(pin == &bank_analog_pins[0][Port_Output][0]);
    CHECK(function == Output_SpindlePWM && pin->mode.analog && pin->cap.pwm);
    assignment_calls++;
    return assignment_allowed;
}
int main(void)
{
    bank_analog_pins[0][Port_Output][0].cap.pwm = true;
    bank_analog_pins[0][Port_Output][0].mode.pwm = true;
    prepare_multi_bank_ioports();
    xbar_t *pin = hal.port.get_pin_info(Port_Analog, Port_Output, 0);
    CHECK(pin != NULL && pin->function == Output_Analog_Aux0);
    pin->set_function = assign_spindle_pwm;
    CHECK(!ioport_set_function(pin, Output_SpindlePWM, (driver_caps_t){0}));
    CHECK(assignment_calls == 1 && pin->function == Output_Analog_Aux0);
    CHECK(ioports_available(Port_Analog, Port_Output) == 4);
    assignment_allowed = true;
    CHECK(ioport_set_function(pin, Output_SpindlePWM, (driver_caps_t){0}));
    CHECK(assignment_calls == 2 && pin->function == Output_SpindlePWM);
    CHECK(ioports_available(Port_Analog, Port_Output) == 3);
    CHECK(!ioport_claimable(Port_Analog, Port_Output, 0));
    CHECK(ioport_claimable(Port_Analog, Port_Output, 1));
    CHECK(ioports_available(Port_Analog, Port_Input) == 4);
    CHECK(ioport_wait_on_input(Port_Analog, 0, WaitMode_Immediate, 0) == 100);
    CHECK(ioport_analog_out(1, 25));
    CHECK(last_bank == 0 && last_local_port == 1 && bank_output_calls == 1);
    NEAR(bank_output_value, 25);
    return EXIT_SUCCESS;
}
