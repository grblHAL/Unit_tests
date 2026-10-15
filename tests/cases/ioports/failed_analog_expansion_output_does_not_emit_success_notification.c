#include "support/multi_bank_ioports_host.h"
int main(void)
{
    prepare_multi_bank_ioports();
    bank_analog_output_ok = false;
    CHECK(!ioport_analog_out(3, 42));
    CHECK(last_bank == 1 && last_local_port == 1 && bank_output_calls == 1);
    CHECK(bank_event_calls == 0);
    return EXIT_SUCCESS;
}
