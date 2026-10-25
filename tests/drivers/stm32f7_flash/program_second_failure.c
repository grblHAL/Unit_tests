#include "stm_host.h"
int main(void)
{
    const unsigned failures[] = {2, 6};
    for (unsigned n = 0; n < 2; n++)
    {
        stm_prepare(64);
        stm_program_fail = failures[n];
        CHECK(!memcpy_to_flash((uint8_t *)stm_source));
        CHECK(stm_programs == failures[n] && stm_locks == 1 && stm_erases == 1);
        CHECK(!memcmp(stm_flash_words, stm_source, (failures[n] - 1) * 2));
    }
    return 0;
}
