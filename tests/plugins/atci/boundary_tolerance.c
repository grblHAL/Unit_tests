#include "atci_host.h"
int main(void)
{
    atci_start();
    atci_flags(1);
    position[0] = 0;
    position[1] = 10;
    CHECK(atci_check(60, 10));
    position[1] = 10.25f;
    CHECK(atci_check(60, 10.25f));
    return 0;
}
