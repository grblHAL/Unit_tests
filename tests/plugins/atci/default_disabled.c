#include "atci_host.h"
int main(void)
{
    atci_start();
    CHECK(saves == 1 && atci_check(20, 20) && check_calls == 1);
    return 0;
}
