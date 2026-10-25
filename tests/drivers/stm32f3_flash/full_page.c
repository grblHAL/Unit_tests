#include "f3_host.h"
int main(void)
{
    f3_prepare(256, 2048);
    CHECK(memcpy_to_flash((uint8_t *)f3_source));
    f3_check_copy();
    return 0;
}
