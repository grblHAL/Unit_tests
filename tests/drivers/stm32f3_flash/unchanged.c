#include "f3_host.h"
int main(void)
{
    f3_prepare(128, 64);
    memcpy((void *)f3_address, f3_source, 64);
    CHECK(memcpy_to_flash((uint8_t *)f3_source));
    CHECK(!f3_unlocks && !f3_erases && !f3_programs && !f3_locks);
    return 0;
}
