#include "analog_host.h"
#include <string.h>
static unsigned visits;
static void inspect(xbar_t *pin, void *data)
{
    CHECK(data == &visits);
    if (visits++ == 0)
        CHECK(pin->function == DEVICE_FUNCTION + 2);
    else
    {
        CHECK(pin->function == DEVICE_FUNCTION + 4);
        CHECK(pin->description && strcmp(pin->description, "External analog") == 0);
#ifdef MCP4725_ENABLE
        CHECK(strcmp(pin->port, "MCP4725:") == 0);
#else
        CHECK(strcmp(pin->port, "MCP3221:") == 0);
#endif
    }
}
int main(void)
{
    prepare_analog();
    initialize_analog();
    xbar_t *pin = bank.get_pin_info(DEVICE_DIRECTION, 0);
    CHECK(pin->pin == 3 && pin->set_function(pin, DEVICE_FUNCTION + 4));
    bank.set_pin_description(DEVICE_DIRECTION, 0, "External analog");
    hal.enumerate_pins(false, inspect, &visits);
    CHECK(visits == 2 && native_enumerations == 2);
    pin = bank.get_pin_info(DEVICE_DIRECTION, 0);
    CHECK(pin->function == DEVICE_FUNCTION + 4 && strcmp(pin->description, "External analog") == 0);
#ifdef MCP4725_ENABLE
    CHECK(sends == 2);
#else
    CHECK(sends == 0);
#endif
    return 0;
}
