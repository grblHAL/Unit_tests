#include "support/ioports_cfg_host.h"
#include "check.h"

int main(void)
{
    prepare_port_configuration();
    uint8_t port = 0;
    CHECK(port_configuration.set_value(&port_configuration, &port, (pin_cap_t){.pwm = true}, 1) == Status_AuxiliaryPortUnusable);
    CHECK(port == 0);
    return EXIT_SUCCESS;
}
