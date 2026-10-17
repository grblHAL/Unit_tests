#include "support/multi_bank_ioports_host.h"
int main(void)
{
    prepare_multi_bank_ioports_counts(1, 2, 2, 1);
    CHECK(hal.port.get_pin_info(Port_Analog, Port_Input, 2) == &bank_analog_pins[1][Port_Input][1]);
    CHECK(hal.port.get_pin_info(Port_Analog, Port_Output, 2) == &bank_analog_pins[1][Port_Output][0]);
    hal.port.set_pin_description(Port_Analog, Port_Input, 2, "Expansion ADC");
    hal.port.set_pin_description(Port_Analog, Port_Output, 2, "Expansion DAC");
    CHECK(strcmp(bank_analog_pins[1][Port_Input][1].description, "Expansion ADC") == 0);
    CHECK(strcmp(bank_analog_pins[1][Port_Output][0].description, "Expansion DAC") == 0);
    CHECK(bank_input_calls == 0 && bank_output_calls == 0);
    return EXIT_SUCCESS;
}
