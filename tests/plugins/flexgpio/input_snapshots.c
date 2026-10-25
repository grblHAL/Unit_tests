#include "flex_host.h"
int main(void)
{
    flex_start();
    const unsigned count = 5 + N_ABC_MOTORS;
    xbar_t pins[8];
    for (unsigned i = 0; i < count; i++)
    {
        pins[i] = flex_pin(Port_Input, i);
        CHECK(pins[i].get_value && pins[i].get_value(&pins[i]) == 0.0f);
    }
    unsigned before = receives;
    for (unsigned active = 0; active < count; active++)
    {
        flex_irq(1U << (3 + active));
        for (unsigned i = 0; i < count; i++)
            CHECK(pins[i].get_value(&pins[i]) == (i == active ? 1.0f : 0.0f));
    }
    CHECK(receives == before + count);
    before = receives;
    flex_irq(0);
    for (unsigned i = 0; i < count; i++)
        CHECK(pins[i].get_value(&pins[i]) == 0.0f);
    CHECK(receives == before + 1 && alarms == 0);
    return 0;
}
