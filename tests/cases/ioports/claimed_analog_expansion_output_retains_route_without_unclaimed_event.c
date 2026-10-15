#include "support/multi_bank_ioports_host.h"
int main(void)
{
    prepare_multi_bank_ioports();
    uint8_t port = 2;
    CHECK(ioport_claim(Port_Analog, Port_Output, &port, "Spindle setpoint") != NULL);
    CHECK(port != IOPORT_UNASSIGNED && ioports_unclaimed(Port_Analog, Port_Output) == 3);
    CHECK(ioport_analog_out(port, 50.5f));
    CHECK(last_bank == 1 && last_local_port == 0 && bank_output_calls == 1);
    CHECK(bank_event_calls == 0); NEAR(bank_output_value, 50.5f);
    return EXIT_SUCCESS;
}
