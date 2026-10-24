#include "f3_host.h"
int main(void)
{
    f3_prepare(128, 64);
    f3_unlock_ok = false;
    CHECK(!memcpy_to_flash((uint8_t *)f3_source));
    CHECK(f3_unlocks == 1 && f3_erases == 1 && !f3_programs && f3_locks == 1);
    return 0;
}
