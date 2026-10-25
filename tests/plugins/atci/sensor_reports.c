#include "atci_host.h"
int main(void)
{
    atci_start();
    atci_flags(3);
    gpio[0] = gpio[1] = gpio[2] = gpio[7] = false;
    position[0] = position[1] = 10;
    atci_poll();
    atci_report();
    CHECK(strstr(output, "|ATCI:REIBLPZ|previous"));
    return 0;
}
