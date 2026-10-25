#include "f3_host.h"
int main(void)
{
    const unsigned failures[] = {2, 6};
    for (unsigned n = 0; n < 2; n++)
    {
        f3_prepare(128, 64);
        f3_fail_program = failures[n];
        CHECK(!memcpy_to_flash((uint8_t *)f3_source));
        CHECK(f3_programs == failures[n] && f3_locks == 1 && f3_erases == 1);
        CHECK(!memcmp((void *)f3_address, f3_source, (failures[n] - 1) * 2));
    }
    return 0;
}
