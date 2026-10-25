#include "mcp_host.h"
#include <string.h>
static unsigned visits;
static void inspect(xbar_t *pin, void *data)
{
    CHECK(data == &visits);
    if (visits++ == 0)
        CHECK(pin->function == Output_Aux1);
    else
    {
        CHECK(pin->pin == pin->id % 8);
        CHECK(strcmp(pin->port, pin->id < 8 ? "MCP23017:A" : "MCP23017:B") == 0);
        if (pin->id == 9)
            CHECK(pin->function == Output_CoolantFlood && strcmp(pin->description, "Flood") == 0);
    }
}
int main(void)
{
    start_mcp();
    xbar_t *pin = bank.get_pin_info(Port_Output, 9);
    CHECK(pin->set_function(pin, Output_CoolantFlood));
    bank.set_pin_description(Port_Output, 9, "Flood");
    hal.enumerate_pins(false, inspect, &visits);
    CHECK(visits == 17 && writes == 3);
    return 0;
}
