#include "rp_host.h"
int main(void)
{
    rp_prepare(1024);
    uint8_t data[1024];
    CHECK(memcpy_from_flash(data));
    for (unsigned i = 0; i < sizeof(data); i++)
        CHECK(data[i] == 255);
    CHECK(!rp_erases && !rp_programs);
    return 0;
}
