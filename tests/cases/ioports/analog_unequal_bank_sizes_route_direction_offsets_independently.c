#include "support/multi_bank_ioports_host.h"
int main(void)
{
    prepare_multi_bank_ioports_counts(1, 2, 2, 1);
    CHECK(ioports_available(Port_Analog, Port_Input) == 3);
    CHECK(ioports_available(Port_Analog, Port_Output) == 3);
    CHECK(ioport_wait_on_input(Port_Analog, 2, WaitMode_Immediate, 0.0f) == 201);
    CHECK(last_bank == 1 && last_local_port == 1);
    CHECK(ioport_analog_out(2, 3.5f));
    CHECK(last_bank == 1 && last_local_port == 0);
    CHECK(bank_input_calls == 1 && bank_output_calls == 1);
    return EXIT_SUCCESS;
}
