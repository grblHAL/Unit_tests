#include "f3_host.h"
int main(void)
{
    f3_prepare(F3_FLASH_KB, 1024);
    CHECK(memcpy_to_flash((uint8_t *)f3_source));
    f3_check_copy();
    CHECK(f3_address == FLASH_BASE + F3_FLASH_KB * 1024 - 4096);
    return 0;
}
