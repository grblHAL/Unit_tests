#include "rp_host.h"
int main(void)
{
    rp_prepare(1024);
    uint8_t data[1024];
    memset(data, 255, sizeof(data));
    CHECK(memcpy_to_flash(data));
    CHECK(!rp_erases && !rp_programs && !rp_irq_phase);
    return 0;
}
