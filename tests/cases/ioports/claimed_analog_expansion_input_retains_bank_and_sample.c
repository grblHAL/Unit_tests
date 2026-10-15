#include "support/multi_bank_ioports_host.h"
int main(void)
{
    prepare_multi_bank_ioports();
    uint8_t port = 2;
    CHECK(ioport_claim(Port_Analog, Port_Input, &port, "ADC sensor") != NULL);
    CHECK(ioports_unclaimed(Port_Analog, Port_Input) == 3);
    CHECK(ioport_wait_on_input(Port_Analog, port, WaitMode_Immediate, 0) == 200);
    CHECK(last_bank == 1 && last_local_port == 0);
    CHECK(ioport_wait_on_input(Port_Analog, 2, WaitMode_Immediate, 0) == 201);
    CHECK(last_bank == 1 && last_local_port == 1 && bank_input_calls == 2);
    CHECK(read_calls == 0 && bank_event_calls == 0);
    return EXIT_SUCCESS;
}
