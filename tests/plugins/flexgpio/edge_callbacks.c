#include "flex_host.h"
int main(void)
{
    flex_start();
    CHECK(bank.register_interrupt_handler(0, 9, IRQ_Mode_Rising, flex_event));
    flex_run();
    flex_irq(1U << 3);
    CHECK(events == 1 && event_port == 9 && event_value);
    flex_irq(1U << 3);
    CHECK(events == 1);
    flex_irq(0);
    CHECK(events == 1);
    CHECK(bank.register_interrupt_handler(0, 9, IRQ_Mode_Falling, flex_event));
    flex_run();
    flex_irq(1U << 3);
    flex_irq(0);
    CHECK(events == 2 && !event_value);
    CHECK(bank.register_interrupt_handler(0, 9, IRQ_Mode_None, NULL));
    flex_run();
    flex_irq(1U << 3);
    CHECK(events == 2);
    return 0;
}
