#include "rp_host.h"
int main(void)
{
    rp_prepare(500);
    uint8_t data[512], readback[500];
    memset(data, 0x5A, sizeof(data));
    CHECK(memcpy_to_flash(data));
    CHECK(rp_program_size == 512);
    CHECK(memcpy_from_flash(readback) && !memcmp(data, readback, sizeof(readback)));
    CHECK(rp_memory[RP_OFFSET + 512] == 255);
    return 0;
}
