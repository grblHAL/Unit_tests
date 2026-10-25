#include "input_host.h"
int main(void)
{
    start_inputs();
#if MCP23017_ENABLE == 1
    CHECK(sends == 5 && device_registers[0x0a] == 0x24);
    CHECK(device_registers[0] == 0 && device_registers[1] == 255 && device_registers[5] == 0);
#else
    CHECK(sends == 3 && device_registers[0x0a] == 0x44);
    CHECK(device_registers[0] == 255 && device_registers[1] == 255);
    CHECK(device_registers[4] == 0 && device_registers[5] == 0);
#endif
    for (unsigned i = 0; i < INPUT_COUNT; i++)
    {
        xbar_t *pin = ports.get_pin_info(Port_Input, i);
        CHECK(pin && pin->id == i && pin->function == Input_Aux2 + i);
        CHECK(pin->cap.input && pin->cap.external && pin->cap.claimable && pin->mode.input);
        CHECK(pin->cap.irq_mode == IRQ_Mode_None && pin->cap.pull_mode == PullMode_Up);
    }
    CHECK(ports.get_pin_info(Port_Input, INPUT_COUNT) == NULL);
    return 0;
}
