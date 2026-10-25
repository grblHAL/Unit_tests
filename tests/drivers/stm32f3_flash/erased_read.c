#include "f3_host.h"
int main(void)
{
    f3_prepare(128, 64);
    memset((void *)f3_address, 0xff, FLASH_PAGE_SIZE);
    uint8_t data[68] = {0};
    CHECK(memcpy_from_flash(data));
    for (unsigned i = 0; i < 64; i++)
        CHECK(data[i] == 255);
    CHECK(data[64] == 0 && !f3_unlocks && !f3_erases && !f3_programs);
    return 0;
}
