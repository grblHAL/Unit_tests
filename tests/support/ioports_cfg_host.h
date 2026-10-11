#pragma once
#include "support/ioports_host.h"
static io_port_cfg_t port_configuration;
static inline void prepare_port_configuration(void)
{
    prepare_ioports();
    CHECK(ioports_cfg(&port_configuration, Port_Digital, Port_Output) == &port_configuration);
    CHECK(port_configuration.n_ports == 2);
}
