#include "analog_host.h"
int main(void)
{
    prepare_analog();
    initialize_analog();
    xbar_t *pin = bank.get_pin_info(Port_Output, 0);
    const uint16_t values[] = {0, 1, 0x123, 4095, 2048};
    for (unsigned i = 0; i < sizeof(values) / sizeof(values[0]); i++)
    {
        CHECK(bank.analog_out(0, values[i]));
        CHECK(packet[0] == 0x40 && packet[1] == values[i] >> 4);
        CHECK(packet[2] == (values[i] & 15) << 4 && pin->get_value(pin) == values[i]);
    }
    CHECK(sends == 7 && !bank.analog_out(1, 0));
    CHECK(sends == 7 && pin->get_value(pin) == 2048);
    pin->set_value(pin, 511);
    CHECK(sends == 8 && packet[1] == 31 && packet[2] == 240 && pin->get_value(pin) == 511);
    return 0;
}
