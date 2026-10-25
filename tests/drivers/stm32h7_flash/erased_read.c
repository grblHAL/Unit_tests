#include "h7_host.h"
int main(void)
{
    h7_prepare(64);
    uint8_t dest[68] = {0};
    CHECK(memcpy_from_flash(dest));
    for (unsigned i = 0; i < 64; i++)
        CHECK(dest[i] == 255);
    CHECK(dest[64] == 0 && !h7_unlocks && !h7_erases && !h7_programs);
    h7_close();
    return 0;
}
