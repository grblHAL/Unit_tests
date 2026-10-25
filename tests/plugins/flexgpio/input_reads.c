#include "flex_host.h"
int main(void)
{
    flex_start();
    flex_irq((1U << 3) | (1U << 7));
    CHECK(bank.wait_on_input(0, WaitMode_Immediate, 0) == 1 &&
          bank.wait_on_input(1, WaitMode_Immediate, 0) == 0 &&
          bank.wait_on_input(4, WaitMode_Immediate, 0) == 1);
    xbar_t pin = flex_pin(Port_Input, 0);
    gpio_in_config_t cfg = {.inverted = true, .pull_mode = PullMode_Up};
    CHECK(pin.config(&pin, &cfg, true));
    CHECK(saved == 1);
    CHECK(bank.wait_on_input(0, WaitMode_Immediate, 0) == 0);
    CHECK(bank.wait_on_input(255, WaitMode_Immediate, 0) == -1);
    return 0;
}
