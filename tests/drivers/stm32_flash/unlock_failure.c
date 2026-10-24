#include "stm_host.h"
int main(void)
{
    stm_prepare(64);
    stm_unlock_ok = false;
    CHECK(!memcpy_to_flash((uint8_t *)stm_source));
    CHECK(stm_unlocks == 1 && !stm_erases && !stm_programs && !stm_locks);
    for (unsigned i = 0; i < 32; i++)
        CHECK(stm_flash_words[i] == 0xffffffff);
    return 0;
}
