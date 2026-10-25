#include "atci_host.h"
int main(void)
{
    atci_start();
    atci_flags(1);
    CHECK(atci_command(0.5f, STATE_IDLE) == Status_GcodeValueOutOfRange);
    CHECK(atci_command(2, STATE_IDLE) == Status_GcodeValueOutOfRange);
    CHECK(!atci_check(20, 20));
    CHECK(atci_command(0, STATE_CHECK_MODE) == Status_OK);
    CHECK(!atci_check(20, 20));
    return 0;
}
