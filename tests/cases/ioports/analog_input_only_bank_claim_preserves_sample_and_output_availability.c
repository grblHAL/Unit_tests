#include "support/multi_bank_ioports_host.h"
int main(void)
{
    prepare_multi_bank_ioports_counts(2, 2, 1, 0);
    uint8_t port = 2;
    CHECK(ioport_claim(Port_Analog, Port_Input, &port, "Expansion sensor") != NULL);
    CHECK(ioports_unclaimed(Port_Analog, Port_Input) == 2);
    CHECK(ioports_available(Port_Analog, Port_Output) == 2);
    CHECK(ioport_wait_on_input(Port_Analog, port, WaitMode_Immediate, 0) == 200);
    CHECK(last_bank == 1 && last_local_port == 0);
    CHECK(bank_input_calls == 1 && bank_output_calls == 0 && bank_event_calls == 0);
    return EXIT_SUCCESS;
}
