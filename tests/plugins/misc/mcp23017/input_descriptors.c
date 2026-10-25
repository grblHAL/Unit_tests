#include "input_host.h"
#include <string.h>
static unsigned inputs_seen, outputs_seen;
static void inspect(xbar_t *pin, void *data)
{
    CHECK(data == &inputs_seen);
    if (pin->function == Input_Aux1 || pin->function == Output_Aux1)
        return;
    if (pin->group == PinGroup_AuxInput)
    {
#if MCP23017_ENABLE == 1
        CHECK(strcmp(pin->port, "MCP23017:B") == 0 && pin->pin == pin->id);
#else
        CHECK(strcmp(pin->port, pin->id < 8 ? "MCP23017:A" : "MCP23017:B") == 0 &&
              pin->pin == pin->id % 8);
#endif
        inputs_seen++;
    }
    else
        outputs_seen++;
}
int main(void)
{
    start_inputs();
    hal.enumerate_pins(false, inspect, &inputs_seen);
    CHECK(inputs_seen == INPUT_COUNT && outputs_seen == (MCP23017_ENABLE == 1 ? 8 : 0));
    return 0;
}
