#include "flex_host.h"
int main(void)
{
    flex_start();
    send_ok = false;
    bank.digital_out(0, true);
    CHECK(alarms == 1);
    receive_ok = false;
    flex_irq(1U << 3);
    CHECK(alarms == 2 && bank.wait_on_input(0, WaitMode_Immediate, 0) == 0);
    return 0;
}
