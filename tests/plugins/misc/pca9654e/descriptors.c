#include "pca_host.h"
#include <string.h>
static unsigned visits;
static void inspect(xbar_t *pin, void *data)
{
    CHECK(data == &visits);
    if (visits < 2)
        CHECK(pin->function == Output_Aux0 + visits);
    else
    {
        CHECK(pin->id == visits - 2 && strcmp(pin->port, "PCA9654E:") == 0);
        if (pin->id == 4)
            CHECK(pin->function == Output_CoolantFlood &&
                  strcmp(pin->description, "Flood relay") == 0);
    }
    visits++;
}
int main(void)
{
    start_expander();
    xbar_t *pin = outputs.get_pin_info(Port_Output, 4);
    CHECK(pin->set_function(pin, Output_CoolantFlood));
    outputs.set_pin_description(Port_Output, 4, "Flood relay");
    hal.enumerate_pins(false, inspect, &visits);
    CHECK(visits == 10 && enumerations == 2 && writes == 3);
    pin = outputs.get_pin_info(Port_Output, 4);
    CHECK(pin->function == Output_CoolantFlood && strcmp(pin->description, "Flood relay") == 0);
    return 0;
}
