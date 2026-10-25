#include "rp_host.h"
int main(void)
{
    rp_prepare(1024);
    rp_corrupt = true;
    uint8_t data[1024] = {0};
    CHECK(!memcpy_to_flash(data));
    CHECK(rp_programs == 1 && !rp_irq_phase);
    return 0;
}
