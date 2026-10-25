#include "flex_host.h"
int main(void)
{
    flex_start();
    CHECK(bank.register_interrupt_handler(0, 9, IRQ_Mode_Change, flex_event));
    flex_run();
    xbar_t pin = flex_pin(Port_Input, 0);
    flex_irq(1U << 3);
    CHECK(pin.get_value(&pin) == 1.0f && events == 1 && event_value);
    receive_ok = false;
    flex_irq(0);
    CHECK(alarms == 1 && pin.get_value(&pin) == 1.0f && events == 1);
    receive_ok = true;
    flex_irq(0);
    CHECK(alarms == 1 && pin.get_value(&pin) == 0.0f && events == 2 && event_port == 9 &&
          !event_value);
    flex_irq(0);
    CHECK(events == 2);
    return 0;
}
