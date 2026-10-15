#include "support/multi_bank_ioports_host.h"
int main(void)
{
    prepare_multi_bank_ioports_counts(2, 2, 0, 1);
    CHECK(ioports_available(Port_Analog, Port_Input) == 2);
    CHECK(ioports_available(Port_Analog, Port_Output) == 3);
    CHECK(ioport_analog_out(2, 7.25f));
    CHECK(last_bank == 1 && last_local_port == 0 && bank_output_calls == 1);
    NEAR(bank_output_value, 7.25f);
    CHECK(ioport_wait_on_input(Port_Analog, 1, WaitMode_Immediate, 0.0f) == 101);
    CHECK(last_bank == 0 && last_local_port == 1 && bank_input_calls == 1);
    return EXIT_SUCCESS;
}
