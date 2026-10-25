#include "lpc_host.h"
int main(void)
{
    lpc_prepare(2048);
    CHECK(memcpy_to_flash((uint8_t *)lpc_source));
    lpc_check_copy();
    CHECK(lpc_copied == 4096 && !memcmp((void *)LPC_FLASH_ADDRESS, lpc_source, 4096));
    return 0;
}
