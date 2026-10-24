#include "lpc_host.h"
int main(void)
{
    lpc_prepare(1024);
    memset((void *)LPC_FLASH_ADDRESS, 0xff, 4096);
    uint8_t data[1028] = {0};
    CHECK(memcpy_from_flash(data));
    for (unsigned i = 0; i < 1024; i++)
        CHECK(data[i] == 255);
    CHECK(data[1024] == 0 && !lpc_stage && !lpc_disables && !lpc_irqs_disabled);
    return 0;
}
