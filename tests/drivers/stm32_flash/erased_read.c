#include "stm_host.h"
int main(void)
{
    stm_prepare(64);
    uint8_t data[68];
    memset(data, 0, sizeof(data));
    CHECK(memcpy_from_flash(data));
    for (unsigned i = 0; i < 64; i++)
        CHECK(data[i] == 255);
    CHECK(data[64] == 0 && !stm_unlocks && !stm_erases && !stm_programs);
    return 0;
}
