#include "input_host.h"
int main(void)
{
    start_inputs();
    const uint16_t patterns[] = {0, INPUT_COUNT == 8 ? 255 : 65535,
                                 INPUT_COUNT == 8 ? 0xa5 : 0xa55a};
    for (unsigned n = 0; n < 3; n++)
    {
        sample = patterns[n];
        for (unsigned i = 0; i < INPUT_COUNT; i++)
        {
            int expected = !!(sample & (1u << i));
            CHECK(ports.wait_on_input(i, WaitMode_Immediate, 0) == expected);
            xbar_t *pin = ports.get_pin_info(Port_Input, i);
            CHECK(pin->get_value(pin) == expected);
        }
    }
    CHECK(reads == 1 + 6 * INPUT_COUNT);
    return 0;
}
