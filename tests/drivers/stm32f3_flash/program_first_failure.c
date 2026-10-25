#include "f3_host.h"
int main(void)
{
    f3_prepare(128, 64);
    f3_fail_program = 1;
    bool ok = memcpy_to_flash((uint8_t *)f3_source);
    CHECK(f3_locks == 1 && *(uint16_t *)f3_address == 65535);
    CHECK(!ok);
    CHECK(f3_programs == 1);
    return 0;
}
