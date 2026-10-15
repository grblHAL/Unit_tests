#include "support/multi_bank_ioports_host.h"
int main(void)
{
    prepare_multi_bank_ioports();
    CHECK(ioport_get_info(Port_Digital, Port_Output, 4) == &bank_digital_pins[2][Port_Output][0]);
    CHECK(ioport_set_description(Port_Digital, Port_Output, 4, "Expansion valve"));
    CHECK(strcmp(bank_digital_pins[2][Port_Output][0].description, "Expansion valve") == 0);
    CHECK(ioport_get_info(Port_Analog, Port_Input, 3) == &bank_analog_pins[1][Port_Input][1]);
    return EXIT_SUCCESS;
}
