#include "support/ioports_host.h"
#include "check.h"

int main(void)
{
    prepare_ioports();
    io_ports_data_t ports = {0};
    io_digital_t digital = {.ports = &ports};
    CHECK(!ioports_add_digital(&digital));
    CHECK(ioports_available(Port_Digital, Port_Output) == 2);
    return EXIT_SUCCESS;
}
