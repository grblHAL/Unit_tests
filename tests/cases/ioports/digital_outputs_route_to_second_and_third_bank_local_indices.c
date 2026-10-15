#include "support/multi_bank_ioports_host.h"
int main(void)
{
    prepare_multi_bank_ioports();
    CHECK(ioport_digital_out(3, 1));
    CHECK(last_bank == 1 && last_local_port == 1 && bank_output_value == 1);
    CHECK(ioport_digital_out(4, 0));
    CHECK(last_bank == 2 && last_local_port == 0 && bank_output_value == 0);
    CHECK(bank_output_calls == 2 && output_calls == 0);
    return EXIT_SUCCESS;
}
