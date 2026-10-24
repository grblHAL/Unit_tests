#include "f3_host.h"
int main(void)
{
    f3_prepare(128, 64);
    f3_fail_program = 2;
    CHECK(!memcpy_to_flash((uint8_t *)f3_source));
    f3_fail_program = 0;
    f3_programs = 0;
    CHECK(memcpy_to_flash((uint8_t *)f3_source));
    CHECK(!memcmp((void *)f3_address, f3_source, 64) && f3_unlocks == 2 && f3_erases == 2 &&
          f3_locks == 2);
    return 0;
}
