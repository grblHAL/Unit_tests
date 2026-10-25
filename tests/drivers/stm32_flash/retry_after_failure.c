#include "stm_host.h"
int main(void)
{
    stm_prepare(64);
    stm_program_fail = 3;
    CHECK(!memcpy_to_flash((uint8_t *)stm_source));
    stm_program_fail = 0;
    stm_programs = 0;
    CHECK(memcpy_to_flash((uint8_t *)stm_source));
    CHECK(!memcmp(stm_flash_words, stm_source, 64) && stm_unlocks == 2 && stm_erases == 2 &&
          stm_locks == 2 && stm_programs == 32);
    return 0;
}
