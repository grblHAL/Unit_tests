#include "support/multi_bank_ioports_host.h"
int main(void)
{
    prepare_multi_bank_ioports();
    CHECK(ioport_analog_out(3, 27.5f));
    CHECK(last_bank == 1 && last_local_port == 1 && last_bank_type == Port_Analog);
    NEAR(bank_output_value, 27.5f);
    CHECK(bank_event_calls == 1 && event_port[0] == 3 && event_type[0] == Port_Analog);
    NEAR(event_value[0], 27.5f);
    return EXIT_SUCCESS;
}
