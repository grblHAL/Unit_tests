#include "net_host.h"
static unsigned calls;
static bool visit(network_info_t *info, network_flags_t flags, void *data)
{
    CHECK(data == &calls && info == &net_infos[calls] && flags.interface_up);
    calls++;
    return false;
}
int main(void)
{
    net_prepare();
    CHECK(!networking_enumerate_interfaces(visit, &calls) && calls == 0);
    net_add(0, (network_status_t){.flags.interface_up = On});
    net_add(1, (network_status_t){.flags.interface_up = On});
    CHECK(!networking_enumerate_interfaces(visit, &calls) && calls == 2);
    return 0;
}
