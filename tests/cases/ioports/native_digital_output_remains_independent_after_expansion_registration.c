#include "support/multi_bank_ioports_host.h"
int main(void)
{
    prepare_multi_bank_ioports();
    CHECK(ioport_digital_out(1, 1));
    CHECK(output_calls == 1 && physical_output == 1 && output_value);
    CHECK(bank_output_calls == 0);
    CHECK(bank_event_calls == 1 && event_port[0] == 1 && event_type[0] == Port_Digital);
    NEAR(event_value[0], 1);
    return EXIT_SUCCESS;
}
