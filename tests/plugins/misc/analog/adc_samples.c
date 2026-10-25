#include "analog_host.h"
int main(void)
{
    prepare_analog();
    initialize_analog();
    const uint16_t values[] = {0, 1, 0x123, 4095, 2048};
    xbar_t *pin = bank.get_pin_info(Port_Input, 0);
    for (unsigned i = 0; i < sizeof(values) / sizeof(values[0]); i++)
    {
        sample = values[i];
        CHECK(bank.wait_on_input(0, WaitMode_Immediate, 0) == sample);
        CHECK(pin->get_value(pin) == sample);
    }
    CHECK(reads == 10 && bank.wait_on_input(1, WaitMode_Immediate, 0) == -1);
    CHECK(reads == 10 && sends == 0);
    return 0;
}
