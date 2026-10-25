#include "lpc_host.h"
int main(void)
{
    lpc_prepare(1024);
    lpc_fail_at = LPC_FAIL_STAGE;
    CHECK(!memcpy_to_flash((uint8_t *)lpc_source));
    CHECK(lpc_disables == 1 && lpc_enables == 1 && !lpc_irqs_disabled && !lpc_copied);
    return 0;
}
