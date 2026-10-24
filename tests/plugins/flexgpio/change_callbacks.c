#include "flex_host.h"
int main(void)
{
    flex_start();
    CHECK(bank.register_interrupt_handler(0, 7, IRQ_Mode_Change, flex_event));
    flex_run();
    flex_irq(1U << 3);
    flex_irq(0);
    CHECK(events == 2 && event_port == 7 && !event_value);
    return 0;
}
