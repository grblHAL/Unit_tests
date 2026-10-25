#include "lpc_host.h"
int main(void)
{
    lpc_prepare(1024);
    memcpy((void *)LPC_FLASH_ADDRESS, lpc_source, 1024);
    CHECK(memcpy_to_flash((uint8_t *)lpc_source));
    CHECK(!lpc_stage && !lpc_disables && !lpc_enables && !lpc_irqs_disabled);
    return 0;
}
