#include "support/multi_bank_ioports_host.h"
int main(void)
{
    prepare_multi_bank_ioports();
    uint8_t port = 2;
    CHECK(ioport_claim(Port_Digital, Port_Output, &port, "Vacuum") != NULL);
    CHECK(port != IOPORT_UNASSIGNED && ioports_unclaimed(Port_Digital, Port_Output) == 4);
    CHECK(ioport_digital_out(port, 1));
    CHECK(last_bank == 1 && last_local_port == 0 && bank_output_calls == 1);
    CHECK(bank_event_calls == 0);
    CHECK(ioport_digital_out(2, 0));
    CHECK(last_bank == 1 && last_local_port == 1);
    CHECK(bank_event_calls == 1 && event_port[0] == 2);
    return EXIT_SUCCESS;
}
