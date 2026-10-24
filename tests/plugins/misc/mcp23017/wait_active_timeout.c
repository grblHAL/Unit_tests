#include "input_host.h"
static unsigned calls;
static void changed(uint8_t port, bool value)
{
    CHECK(port == 11 && !value);
    calls++;
}
int main(void)
{
    accept_irq = true;
    start_inputs();
    CHECK(ports.register_interrupt_handler(1, 11, IRQ_Mode_Change, changed));
    CHECK(ports.wait_on_input(1, WaitMode_Rise, 0.1f) == -1 && calls == 0);
    CHECK(device_registers[4 + (MCP23017_ENABLE == 1)] == 2);
    xbar_t *pin = ports.get_pin_info(Port_Input, 1);
    CHECK(pin->mode.irq_mode == IRQ_Mode_Change);
    fire_mcp_irq(2, 0);
    run_mcp_irq();
    CHECK(calls == 1);
    return 0;
}
