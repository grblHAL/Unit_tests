#include "support/ioports_legacy_host.h"
int main(void)
{
    prepare_legacy_ports();
    io_ports_data_t digital = {0}, analog = {0};
    CHECK(ioports_add(&digital, Port_Digital, 2, 1));
    CHECK(ioports_add(&analog, Port_Analog, 1, 2));
    CHECK(hal.port.num_digital_in == 2 && hal.port.num_digital_out == 1);
    CHECK(hal.port.num_analog_in == 1 && hal.port.num_analog_out == 2);
    CHECK(digital.in.n_ports == 2 && analog.in.n_ports == 1);
    return EXIT_SUCCESS;
}
