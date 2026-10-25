#include "atci_host.h"
int main(void)
{
    atci_start();
    atci_flags(1);
    CHECK(!atci_check(20, 20) && check_calls == 0);
    CHECK(strstr(message, "Target inside region"));
    return 0;
}
