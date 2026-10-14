#include "support/ioports_legacy_host.h"
int main(void)
{
    prepare_legacy_ports();
    io_ports_data_t ports = {0};
    CHECK(ioports_add(&ports, Port_Digital, 2, 0));
    CHECK(hal.port.num_digital_in == 2 && hal.port.num_digital_out == 0);
    CHECK(ports.in.n_ports == 2 && ports.out.n_ports == 0);
    CHECK(legacy_description_calls[Port_Input] == 2 && legacy_description_calls[Port_Output] == 0);
    return EXIT_SUCCESS;
}
