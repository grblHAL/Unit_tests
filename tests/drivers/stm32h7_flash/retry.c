#include "h7_host.h"
int main(void)
{
    h7_prepare(64);
    h7_fail_program = 2;
    CHECK(!memcpy_to_flash(h7_source));
    h7_fail_program = 0;
    h7_programs = 0;
    CHECK(memcpy_to_flash(h7_source));
    CHECK(!memcmp(h7_flash_words, h7_source, 64) && h7_unlocks == 2 && h7_erases == 2 &&
          h7_locks == 2 && h7_programs == 2);
    h7_close();
    return 0;
}
