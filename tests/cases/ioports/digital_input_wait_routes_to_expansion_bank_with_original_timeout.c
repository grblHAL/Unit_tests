#include "support/multi_bank_ioports_host.h"
int main(void)
{
    prepare_multi_bank_ioports();
    CHECK(ioport_wait_on_input(Port_Digital, 3, WaitMode_High, 2.5f) == 21);
    CHECK(last_bank == 1 && last_local_port == 1 && bank_input_calls == 1);
    CHECK(bank_wait_mode == WaitMode_High); NEAR(bank_wait_timeout, 2.5f);
    CHECK(read_calls == 0);
    return EXIT_SUCCESS;
}
