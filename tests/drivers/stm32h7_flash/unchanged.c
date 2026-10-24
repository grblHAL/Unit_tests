#include "h7_host.h"
int main(void)
{
    h7_prepare(36);
    memcpy(h7_flash_words, h7_source, 36);
    CHECK(memcpy_to_flash(h7_source));
    CHECK(!h7_unlocks && !h7_locks && !h7_erases && !h7_programs);
    h7_close();
    return 0;
}
