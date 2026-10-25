#include "flex_host.h"
int main(void)
{
    flex_prepare();
    send_ok = false;
    input_bits = 1U << 3;
    flexgpio_init();
    CHECK(bank.ports && sends == 0 && alarms == 0);
    flex_run();
    CHECK(sends == 1 && last_size == 8 && alarms == 1 && receives == 1);
    xbar_t input = flex_pin(Port_Input, 0);
    CHECK(input.get_value(&input) == 1.0f);
    send_ok = true;
    bank.digital_out(0, true);
    CHECK(sends == 2 && last_size == 4 && alarms == 1);
    flex_irq(0);
    CHECK(input.get_value(&input) == 0.0f && alarms == 1);
    return 0;
}
