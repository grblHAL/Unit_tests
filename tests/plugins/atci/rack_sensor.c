#include "atci_host.h"
int main(void)
{
    atci_start();
    atci_flags(3);
    gpio[7] = false;
    atci_poll();
    CHECK(!atci_check(20, 20));
    gpio[7] = true;
    atci_poll();
    CHECK(atci_check(20, 20));
    atci_report();
    CHECK(strstr(output, "|ATCI:R|previous"));
    return 0;
}
