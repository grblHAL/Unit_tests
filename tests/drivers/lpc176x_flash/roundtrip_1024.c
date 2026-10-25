#include "lpc_host.h"
int main(void)
{
    lpc_prepare(1024);
    CHECK(memcpy_to_flash((uint8_t *)lpc_source));
    lpc_check_copy();
    CHECK(lpc_copied == 1024);
    for (unsigned i = 1024; i < 4096; i++)
        CHECK(((uint8_t *)LPC_FLASH_ADDRESS)[i] == 255);
    return 0;
}
