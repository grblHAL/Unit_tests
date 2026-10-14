#include "support/ioports_legacy_host.h"
int main(void)
{
    prepare_legacy_ports();
    io_ports_data_t ports = {0};
    CHECK(ioports_add(&ports, Port_Digital, 0, 2));
    CHECK(hal.port.num_digital_in == 0 && hal.port.num_digital_out == 2);
    CHECK(ports.in.n_ports == 0 && ports.out.n_ports == 2);
    CHECK(legacy_description_calls[Port_Input] == 0 && legacy_description_calls[Port_Output] == 2);
    return EXIT_SUCCESS;
}
