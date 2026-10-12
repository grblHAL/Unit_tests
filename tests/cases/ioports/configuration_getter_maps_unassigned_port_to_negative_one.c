#include "support/ioports_cfg_host.h"
#include "check.h"

int main(void)
{
    prepare_port_configuration();
    NEAR(port_configuration.get_value(&port_configuration, 0), 0);
    NEAR(port_configuration.get_value(&port_configuration, 1), 1);
    NEAR(port_configuration.get_value(&port_configuration, IOPORT_UNASSIGNED), -1);
    return EXIT_SUCCESS;
}
