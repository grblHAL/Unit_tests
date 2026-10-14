#include "support/ioports_legacy_host.h"
int main(void)
{
    prepare_legacy_ports();
    hal.port.set_pin_description = NULL;
    io_ports_data_t ports = {0};
    CHECK(ioports_add(&ports, Port_Digital, 2, 1));
    CHECK(hal.port.num_digital_in == 2 && hal.port.num_digital_out == 1);
    CHECK(legacy_description_calls[0] == 0 && legacy_description_calls[1] == 0);
    return EXIT_SUCCESS;
}
