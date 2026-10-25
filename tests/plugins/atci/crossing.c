#include "atci_host.h"
int main(void)
{
    atci_start();
    atci_flags(1);
    position[0] = 0;
    position[1] = 30;
    CHECK(!atci_check(60, 30));
    CHECK(strstr(message, "Move crosses"));
    position[0] = 60;
    CHECK(!atci_check(0, 30));
    position[0] = 0;
    position[1] = 0;
    CHECK(!atci_check(60, 60));
    return 0;
}
