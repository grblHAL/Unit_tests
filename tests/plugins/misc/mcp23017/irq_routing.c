#include "input_host.h"
static unsigned calls;
static void changed(uint8_t port, bool value)
{
    CHECK(port == (calls == 0 ? 7 : 9));
    CHECK(value == (calls == 0));
    calls++;
}
int main(void)
{
    accept_irq = true;
    start_inputs();
    CHECK(ports.register_interrupt_handler(0, 7, IRQ_Mode_Change, changed));
    CHECK(ports.register_interrupt_handler(INPUT_COUNT - 1, 9, IRQ_Mode_Change, changed));
    fire_mcp_irq(1u | (1u << (INPUT_COUNT - 1)), 1);
    CHECK(calls == 0);
    run_mcp_irq();
    CHECK(calls == 2);
    fire_mcp_irq(0, 0);
    run_mcp_irq();
    CHECK(calls == 2);
    return 0;
}
