#include "rp_host.h"
int main(void)
{
    rp_prepare(1024);
    uint8_t data[1024], readback[1024];
    for (unsigned i = 0; i < sizeof(data); i++)
        data[i] = i * 17;
    CHECK(memcpy_to_flash(data));
    CHECK(rp_erases == 1 && rp_programs == 1 && rp_program_size == 1024 && !rp_irq_phase);
    CHECK(memcpy_from_flash(readback) && !memcmp(data, readback, sizeof(data)));
    CHECK(rp_memory[RP_OFFSET - 1] == 255 && rp_memory[RP_OFFSET + 1024] == 255);
    return 0;
}
