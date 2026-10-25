#include "input_host.h"
static unsigned calls;
static void changed(uint8_t port, bool value)
{
    CHECK(port == 9);
    (void)value;
    calls++;
}
int main(void)
{
    accept_irq = true;
    start_inputs();
#ifdef TEST_RISING
    pin_irq_mode_t mode = IRQ_Mode_Rising;
    uint16_t matching = 4, opposite = 0;
#else
    pin_irq_mode_t mode = IRQ_Mode_Falling;
    uint16_t matching = 0, opposite = 4;
#endif
    CHECK(ports.register_interrupt_handler(2, 9, mode, changed));
    fire_mcp_irq(4, matching);
    run_mcp_irq();
    CHECK(calls == 1);
    fire_mcp_irq(4, opposite);
    run_mcp_irq();
    CHECK(calls == 1);
    return 0;
}
