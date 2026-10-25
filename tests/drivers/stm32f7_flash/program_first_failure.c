#include "stm_host.h"
int main(void)
{
    stm_prepare(64);
    stm_program_fail = 1;
    bool ok = memcpy_to_flash((uint8_t *)stm_source);
    CHECK(stm_locks == 1);
    CHECK(!ok);
    CHECK(stm_programs == 1);
    return 0;
}
