#include "mcp_host.h"
int main(void)
{
    pin_base = 2;
    start_mcp();
    bank.digital_out(0, true);
    xbar_t *pin = bank.get_pin_info(Port_Output, 0);
    CHECK(pin->id == 0 && pin->pin == 2 && pin->get_value(pin) == 1 && gpio == 1);
    pin->set_value(pin, 0);
    CHECK(gpio == 0 && pin->get_value(pin) == 0);
    pin = bank.get_pin_info(Port_Output, 15);
    CHECK(pin->id == 15 && pin->pin == 17);
    pin->set_value(pin, 1);
    CHECK(gpio == 32768 && pin->get_value(pin) == 1);
    return 0;
}
