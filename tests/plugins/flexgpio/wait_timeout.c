#include "flex_host.h"
int main(void)
{
    flex_start();
    CHECK(bank.wait_on_input(0, WaitMode_High, 0) == -1);
    flex_irq(1U << 3);
    CHECK(bank.wait_on_input(0, WaitMode_High, 0) == 1);
    CHECK(bank.wait_on_input(0, WaitMode_Low, 0) == -1);
    return 0;
}
