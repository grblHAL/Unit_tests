#include "flex_host.h"
int main(void)
{
    flex_start();
    inject_inputs = true;
    delay_bits = 1U << 3;
    CHECK(bank.wait_on_input(0, WaitMode_Rise, 0.1f) == 1);
    inject_inputs = true;
    delay_bits = 0;
    CHECK(bank.wait_on_input(0, WaitMode_Fall, 0.1f) == 0);
    CHECK(bank.wait_on_input(0, WaitMode_Rise, 0) == -1);
    return 0;
}
