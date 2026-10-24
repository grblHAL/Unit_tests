#include "pca_host.h"
int main(void)
{
    start_expander();
    uint8_t expected = 0;
    for (unsigned i = 0; i < 8; i++)
    {
        outputs.digital_out(i, true);
        expected |= 1u << i;
        CHECK(register_values[1] == expected && writes == 4 + i);
        outputs.digital_out(i, true);
        CHECK(writes == 4 + i);
    }
    CHECK(register_values[1] == 255);
    for (unsigned i = 0; i < 8; i++)
    {
        outputs.digital_out(i, false);
        expected &= ~(1u << i);
        CHECK(register_values[1] == expected && writes == 12 + i);
        xbar_t *pin = outputs.get_pin_info(Port_Output, i);
        CHECK(pin->get_value(pin) == 0);
    }
    CHECK(writes == 19 && register_values[1] == 0);
    return 0;
}
