#include "mcp_host.h"
int main(void)
{
    start_mcp();
    uint16_t expected = 0;
    for (unsigned i = 0; i < 16; i++)
    {
        bank.digital_out(i, true);
        expected |= 1u << i;
        CHECK(gpio == expected && writes == 4 + i);
        bank.digital_out(i, true);
        CHECK(writes == 4 + i);
    }
    CHECK(gpio == 65535);
    for (unsigned i = 0; i < 16; i++)
    {
        bank.digital_out(i, false);
        expected &= ~(1u << i);
        CHECK(gpio == expected && writes == 20 + i);
    }
    CHECK(gpio == 0 && writes == 35);
    return 0;
}
