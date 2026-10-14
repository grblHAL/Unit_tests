#include "support/ioports_legacy_host.h"
int main(void)
{
    prepare_legacy_ports();
    io_ports_data_t ports = {0};
    CHECK(ioports_add(&ports, Port_Analog, 255, 255));
    CHECK(ports.in.n_ports == 8 && ports.out.n_ports == 8);
    CHECK(hal.port.num_analog_in == 8 && hal.port.num_analog_out == 8);
    CHECK(strcmp(legacy_descriptions[Port_Input][7], "E7") == 0);
    return EXIT_SUCCESS;
}
