#include "stm_host.h"
int main(void)
{
    stm_prepare(64);
    stm_erase_failures = 1;
    CHECK(memcpy_to_flash((uint8_t *)stm_source));
    stm_check_copy();
    CHECK(stm_erases == 2);
    return 0;
}
