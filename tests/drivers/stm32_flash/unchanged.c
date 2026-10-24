#include "stm_host.h"
int main(void)
{
    stm_prepare(64);
    memcpy(stm_flash_words, stm_source, 64);
    CHECK(memcpy_to_flash((uint8_t *)stm_source));
    CHECK(!stm_unlocks && !stm_locks && !stm_erases && !stm_programs);
    return 0;
}
