#include "support/multi_bank_ioports_host.h"
int main(void)
{
    prepare_multi_bank_ioports();
    CHECK(ioport_wait_on_input(Port_Analog, 2, WaitMode_Immediate, 0) == 200);
    CHECK(last_bank == 1 && last_local_port == 0 && bank_input_calls == 1);
    CHECK(bank_wait_mode == WaitMode_Immediate && bank_wait_timeout == 0);
    CHECK(read_calls == 0);
    return EXIT_SUCCESS;
}
