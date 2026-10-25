#include "h7_host.h"
int main(void)
{
    h7_prepare(64);
    h7_unlock_ok = false;
    CHECK(!memcpy_to_flash(h7_source));
    CHECK(h7_unlocks == 1 && !h7_locks && !h7_erases && !h7_programs);
    h7_close();
    return 0;
}
