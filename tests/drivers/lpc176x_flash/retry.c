#include "lpc_host.h"
int main(void)
{
    lpc_prepare(1024);
    lpc_fail_at = 4;
    CHECK(!memcpy_to_flash((uint8_t *)lpc_source));
    CHECK(!lpc_irqs_disabled && !lpc_copied);
    lpc_fail_at = 0;
    CHECK(memcpy_to_flash((uint8_t *)lpc_source));
    CHECK(!memcmp((void *)LPC_FLASH_ADDRESS, lpc_source, 1024));
    CHECK(lpc_disables == 2 && lpc_enables == 2 && !lpc_irqs_disabled && lpc_copied == 1024);
    return 0;
}
