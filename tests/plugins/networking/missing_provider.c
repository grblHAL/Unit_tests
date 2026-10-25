#include "net_host.h"
static bool visit(network_info_t *info, network_flags_t flags, void *data)
{
    (void)info;
    (void)flags;
    (void)data;
    CHECK(false);
    return true;
}
int main(void)
{
    net_prepare();
    net_available[0] = false;
    net_add(0, (network_status_t){.changed.ip_aquired = On, .flags.ip_aquired = On});
    CHECK(!*net_output && !networking_enumerate_interfaces(visit, NULL));
    CHECK(net_command() == Status_OK && !*net_output);
    return 0;
}
