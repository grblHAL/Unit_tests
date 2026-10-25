#include "h7_host.h"
int main(void)
{
    h7_prepare(64);
    CHECK(memcpy_to_flash(h7_source));
    h7_check_copy();
    h7_close();
    return 0;
}
