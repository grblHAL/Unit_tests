#include "atci_host.h"
int main(void)
{
    atci_start();
    atci_flags(1);
    atci_bounds(100, 100, 150, 150);
    registered_settings->load();
    CHECK(!atci_check(120, 120));
    CHECK(atci_check(20, 20));
    atci_poll();
    return 0;
}
