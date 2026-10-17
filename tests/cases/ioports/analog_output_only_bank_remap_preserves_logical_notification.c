#include "support/multi_bank_ioports_host.h"
int main(void)
{
    prepare_multi_bank_ioports_counts(2, 2, 0, 1);
    CHECK(ioport_remap(Port_Analog, Port_Output, 0, 2));
    CHECK(ioport_analog_out(0, 12.5f));
    CHECK(last_bank == 1 && last_local_port == 0 && bank_output_calls == 1);
    CHECK(bank_event_calls == 1 && event_port[0] == 0 && event_type[0] == Port_Analog);
    NEAR(event_value[0], 12.5f);
    CHECK(ioport_wait_on_input(Port_Analog, 0, WaitMode_Immediate, 0) == 100);
    CHECK(last_bank == 0 && last_local_port == 0);
    return EXIT_SUCCESS;
}
