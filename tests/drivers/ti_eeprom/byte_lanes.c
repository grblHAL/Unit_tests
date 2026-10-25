#include "ti_host.h"
int main(void)
{
    ti_prepare();
    uint8_t expected[8];
    memset(expected, 0xA5, sizeof(expected));
    for (unsigned lane = 0; lane < 4; lane++)
    {
        expected[lane + 1] = (uint8_t)(0x31 + lane);
        hal.nvs.put_byte(33 + lane, expected[lane + 1]);
        CHECK(hal.nvs.get_byte(33 + lane) == expected[lane + 1]);
        CHECK(memcmp(memory + 32, expected, sizeof(expected)) == 0);
    }
    return 0;
}
