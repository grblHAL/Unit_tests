#include "h7_host.h"
int main(void)
{
    h7_prepare(64);
    h7_erase_ok = false;
    CHECK(!memcpy_to_flash(h7_source));
    CHECK(h7_unlocks == 1 && h7_locks == 1 && h7_erases == 1 && !h7_programs);
    h7_close();
    return 0;
}
