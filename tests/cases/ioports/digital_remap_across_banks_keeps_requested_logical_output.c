#include "support/multi_bank_ioports_host.h"
int main(void)
{
    prepare_multi_bank_ioports();
    CHECK(ioport_remap(Port_Digital, Port_Output, 0, 4));
    CHECK(ioport_digital_out(0, 1));
    CHECK(last_bank == 2 && last_local_port == 0 && output_calls == 0);
    CHECK(bank_event_calls == 1 && event_port[0] == 0 && event_type[0] == Port_Digital);
    return EXIT_SUCCESS;
}
