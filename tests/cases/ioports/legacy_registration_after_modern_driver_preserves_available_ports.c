#include "support/ioports_host.h"
int main(void)
{
    prepare_ioports(); io_ports_data_t extra = {0};
    CHECK(!ioports_add(&extra, Port_Digital, 1, 1));
    CHECK(extra.in.n_ports == 0 && extra.out.n_ports == 0);
    CHECK(hal.port.num_digital_in == 2 && hal.port.num_digital_out == 2);
    CHECK(ioport_get_info(Port_Digital, Port_Input, 0) == &digital_pins[Port_Input][0]);
    return EXIT_SUCCESS;
}
