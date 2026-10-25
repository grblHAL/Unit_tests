#include "input_host.h"
static unsigned calls;
static bool last;
static void changed(uint8_t port, bool value)
{
    CHECK(port == 11);
    last = value;
    calls++;
}
static void rising(void)
{
    fire_mcp_irq(2, 2);
    run_mcp_irq();
    poll_action = NULL;
}
int main(void)
{
    accept_irq = true;
    start_inputs();
    CHECK(ports.register_interrupt_handler(1, 11, IRQ_Mode_Change, changed));
    poll_action = rising;
    CHECK(ports.wait_on_input(1, WaitMode_Rise, 0.1f) == 1);
    CHECK(calls == 1 && last);
    CHECK(device_registers[4 + (MCP23017_ENABLE == 1)] == 2);
    xbar_t *pin = ports.get_pin_info(Port_Input, 1);
    CHECK(pin->mode.irq_mode == IRQ_Mode_Change);
    fire_mcp_irq(2, 0);
    run_mcp_irq();
    CHECK(calls == 2 && !last);
    return 0;
}
