#include "support/ioports_legacy_host.h"
int main(void)
{
    prepare_legacy_ports();
    io_ports_data_t ports = {0};
    CHECK(!ioports_add(&ports, Port_Digital, 0, 0));
    CHECK(hal.port.num_digital_in == 0 && hal.port.num_digital_out == 0);
    CHECK(legacy_description_calls[0] == 0 && legacy_description_calls[1] == 0);
    return EXIT_SUCCESS;
}
