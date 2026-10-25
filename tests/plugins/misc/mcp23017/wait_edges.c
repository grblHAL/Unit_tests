#include "input_host.h"
static void rising(void)
{
    fire_mcp_irq(2, 2);
    run_mcp_irq();
    poll_action = NULL;
}
static void falling(void)
{
    fire_mcp_irq(2, 0);
    run_mcp_irq();
    poll_action = NULL;
}
int main(void)
{
    accept_irq = true;
    start_inputs();
    poll_action = rising;
    CHECK(ports.wait_on_input(1, WaitMode_Rise, 0.1f) == 1);
    CHECK(device_registers[4 + (MCP23017_ENABLE == 1)] == 0);
    poll_action = falling;
    CHECK(ports.wait_on_input(1, WaitMode_Fall, 0.1f) == 0);
    CHECK(device_registers[4 + (MCP23017_ENABLE == 1)] == 0);
    CHECK(polls > 0 && delays > 0);
    return 0;
}
