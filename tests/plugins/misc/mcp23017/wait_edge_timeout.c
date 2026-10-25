#include "input_host.h"
int main(void)
{
    accept_irq = true;
    start_inputs();
    CHECK(ports.wait_on_input(1, WaitMode_Rise, 0.1f) == -1);
    CHECK(polls > 0 && polls < 16 && delays == polls);
    CHECK(device_registers[4 + (MCP23017_ENABLE == 1)] == 0);
    xbar_t *pin = ports.get_pin_info(Port_Input, 1);
    CHECK(pin->mode.irq_mode == IRQ_Mode_None);
    CHECK(ports.wait_on_input(1, WaitMode_Immediate, 0) == 0);
    return 0;
}
