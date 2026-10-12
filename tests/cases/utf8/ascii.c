#include <stdint.h>
#include "utf8.h"
#include "check.h"
int main(void)
{
    uint8_t buffer[2] = {0xAA, 0xAA};
    CHECK(utf32_to_utf8(buffer, 'A') == 1);
    CHECK(buffer[0] == 'A');
    CHECK(buffer[1] == 0xAA);
    return EXIT_SUCCESS;
}
