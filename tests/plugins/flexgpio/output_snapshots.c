#include "flex_host.h"
int main(void)
{
    static const uint8_t bit[] = {23, 22, 21, 20, 19, 18, 17, 16, 11,
                                  12, 13, 14, 29, 28, 27, 26, 25, 24};
    flex_start();
    const unsigned count = 15 + N_ABC_MOTORS;
    xbar_t pins[18];
    for (unsigned i = 0; i < count; i++)
    {
        pins[i] = flex_pin(Port_Output, i);
        CHECK(pins[i].get_value && pins[i].set_value && pins[i].get_value(&pins[i]) == 0.0f);
    }
    for (unsigned active = 0; active < count; active++)
    {
        unsigned before = sends;
        pins[active].set_value(&pins[active], active & 1 ? -2.0f : 0.5f);
        CHECK(sends == before + 1 && last_size == 4);
        uint32_t mask = 1U << bit[active];
        for (unsigned byte = 0; byte < 4; byte++)
            CHECK(last_packet[byte] == (uint8_t)(mask >> (8 * byte)));
        for (unsigned i = 0; i < count; i++)
            CHECK(pins[i].get_value(&pins[i]) == (i == active ? 1.0f : 0.0f));
        pins[active].set_value(&pins[active], 0.0f);
        CHECK(sends == before + 2 && pins[active].get_value(&pins[active]) == 0.0f);
        for (unsigned byte = 0; byte < 4; byte++)
            CHECK(last_packet[byte] == 0);
    }
    CHECK(alarms == 0);
    return 0;
}
