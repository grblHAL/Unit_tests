#include "spi_host.h"
#include <string.h>
static unsigned visits;
static void inspect(xbar_t *pin, void *data)
{
    CHECK(data == &visits);
    if (visits++ == 0)
        CHECK(pin->function == Output_Aux1);
    else
        CHECK(strcmp(pin->port, "HC595.") == 0);
}
int main(void)
{
    start_hc595();
    xbar_t *pin = bank.get_pin_info(Port_Output, 3);
    CHECK(pin->set_function(pin, Output_CoolantFlood));
    bank.set_pin_description(Port_Output, 3, "Flood");
    pin = bank.get_pin_info(Port_Output, 3);
    CHECK(pin->function == Output_CoolantFlood && strcmp(pin->description, "Flood") == 0);
    pin->set_value(pin, 1);
    CHECK(shifted == 8 && pin->get_value(pin) == 1);
    pin->set_value(pin, 0);
    CHECK(shifted == 0);
    hal.enumerate_pins(false, inspect, &visits);
    CHECK(visits == HC595_ENABLE * 8 + 1 && transfers == 2);
    return 0;
}
