#include "flex_host.h"
int main(void)
{
    flex_start();
    xbar_t pin = flex_pin(Port_Input, 1);
    CHECK(pin.set_function(&pin, Input_Probe));
    CHECK(bank.register_interrupt_handler(1, 1, IRQ_Mode_All, NULL));
    flex_run();
    CHECK(last_packet[6] & (1U << 4));
    pin = flex_pin(Port_Input, 1);
    gpio_in_config_t cfg = {.pull_mode = PullMode_Up};
    CHECK(pin.config(&pin, &cfg, false));
    flex_run();
    CHECK(!(last_packet[4] & (1U << 4)));
    return 0;
}
