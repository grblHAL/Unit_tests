#include "stm_host.h"
int main(void)
{
    stm_prepare(64);
    stm_erase_failures = 2;
    CHECK(!memcpy_to_flash((uint8_t *)stm_source));
    CHECK(stm_unlocks == 1 && stm_erases == 2 && !stm_programs && stm_locks == 1);
    return 0;
}
