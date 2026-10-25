#include "atci_host.h"
int main(void)
{
    atci_start();
    atci_flags(1);
    CHECK(!atci_check(20, 20));
    CHECK(atci_command(0, STATE_IDLE) == Status_OK);
    CHECK(atci_check(20, 20));
    atci_report();
    CHECK(strstr(output, "|ATCI:M|previous"));
    return 0;
}
