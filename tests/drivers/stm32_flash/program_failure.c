#include "stm_host.h"
int main(void)
{
    const unsigned fail_at[] = {1, 2, 5};
    for (unsigned n = 0; n < 3; n++)
    {
        stm_prepare(64);
        stm_program_fail = fail_at[n];
        CHECK(!memcpy_to_flash((uint8_t *)stm_source));
        CHECK(stm_programs == fail_at[n] && stm_locks == 1 && stm_erases == 1);
        CHECK(!memcmp(stm_flash_words, stm_source, (fail_at[n] - 1) * 2));
        CHECK(((uint16_t *)stm_flash_words)[fail_at[n] - 1] == 0xffff);
    }
    return 0;
}
