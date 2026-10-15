#include "support/multi_bank_ioports_host.h"
int main(void)
{
    prepare_multi_bank_ioports();
    io_ports_data_t empty = {0};
    io_analog_t absent = {.ports = &empty};
    CHECK(!ioports_add_analog(&absent));
    CHECK(ioports_available(Port_Analog, Port_Output) == 4);
    CHECK(ioports_available(Port_Digital, Port_Output) == 5);
    CHECK(ioport_analog_out(3, 12.5f));
    CHECK(last_bank == 1 && last_local_port == 1 && bank_output_calls == 1);
    return EXIT_SUCCESS;
}
