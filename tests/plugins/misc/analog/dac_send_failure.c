#include "analog_host.h"
int main(void)
{
    prepare_analog();
    initialize_analog();
    xbar_t *pin = bank.get_pin_info(Port_Output, 0);
    CHECK(bank.analog_out(0, 100));
    send_ok = false;
    bool accepted = bank.analog_out(0, 200);
    CHECK(pin->get_value(pin) == 100 && sends == 4);
    send_ok = true;
    CHECK(bank.analog_out(0, 300) && pin->get_value(pin) == 300 && sends == 5);
    CHECK(!accepted);
    return 0;
}
