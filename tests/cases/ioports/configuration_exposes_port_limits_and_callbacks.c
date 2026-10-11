#include "support/ioports_cfg_host.h"
#include "check.h"

int main(void)
{
    prepare_port_configuration();
    CHECK(port_configuration.port_max == 1);
    CHECK(strcmp(port_configuration.port_maxs, "1") == 0);
    CHECK(port_configuration.handle != NULL);
    CHECK(port_configuration.get_value && port_configuration.set_value);
    CHECK(port_configuration.get_info && port_configuration.get_next && port_configuration.claim);
    return EXIT_SUCCESS;
}
