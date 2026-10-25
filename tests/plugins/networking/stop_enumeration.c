#include "net_host.h"
static unsigned calls;
static bool visit(network_info_t *info, network_flags_t flags, void *data)
{
    (void)flags;
    CHECK(data == &calls && info == &net_infos[0]);
    calls++;
    return true;
}
int main(void)
{
    net_prepare();
    net_add(0, (network_status_t){0});
    net_add(1, (network_status_t){0});
    CHECK(networking_enumerate_interfaces(visit, &calls) && calls == 1);
    return 0;
}
