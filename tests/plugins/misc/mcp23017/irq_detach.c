#include "input_host.h"
static unsigned calls;
static void changed(uint8_t port, bool value)
{
    CHECK(port == 7 && value);
    calls++;
}
int main(void)
{
    accept_irq = true;
    start_inputs();
    CHECK(ports.register_interrupt_handler(0, 7, IRQ_Mode_Change, changed));
    fire_mcp_irq(1, 1);
    ports.register_interrupt_handler(0, 7, IRQ_Mode_None, NULL);
    run_mcp_irq();
    CHECK(calls == 0);
    CHECK(ports.register_interrupt_handler(0, 7, IRQ_Mode_Change, changed));
    fire_mcp_irq(1, 1);
    run_mcp_irq();
    CHECK(calls == 1);
    return 0;
}
