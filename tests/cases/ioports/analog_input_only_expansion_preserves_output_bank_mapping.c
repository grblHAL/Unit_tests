#include "support/multi_bank_ioports_host.h"
int main(void)
{
    prepare_multi_bank_ioports_counts(2, 2, 1, 0);
    CHECK(ioports_available(Port_Analog, Port_Input) == 3);
    CHECK(ioports_available(Port_Analog, Port_Output) == 2);
    CHECK(ioport_wait_on_input(Port_Analog, 2, WaitMode_Immediate, 0.0f) == 200);
    CHECK(last_bank == 1 && last_local_port == 0 && bank_input_calls == 1);
    CHECK(ioport_analog_out(1, 12.5f));
    CHECK(last_bank == 0 && last_local_port == 1 && bank_output_calls == 1);
    NEAR(bank_output_value, 12.5f);
    return EXIT_SUCCESS;
}
