#include "h7_host.h"
int main(void)
{
    h7_prepare(64);
    h7_fail_program = H7_FAIL_WORD;
    CHECK(!memcpy_to_flash(h7_source));
    CHECK(h7_programs == H7_FAIL_WORD && h7_locks == 1 && h7_erases == 1);
    CHECK(!memcmp(h7_flash_words, h7_source, (H7_FAIL_WORD - 1) * FLASH_WRITE_SIZE));
    CHECK(((uint8_t *)h7_flash_words)[(H7_FAIL_WORD - 1) * FLASH_WRITE_SIZE] == 255);
    h7_close();
    return 0;
}
