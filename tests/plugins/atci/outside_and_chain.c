#include "atci_host.h"
int main(void)
{
    atci_start();
    atci_flags(1);
    CHECK(atci_check(-10, -10));
    previous_accept = false;
    CHECK(!atci_check(-10, -10));
    CHECK(check_calls == 2);
    return 0;
}
