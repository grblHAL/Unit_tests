#include <stdint.h>
#include <string.h>
#include "utf8.h"
#include "check.h"

int main(void)
{
    {
        uint8_t buffer[6];
        memset(buffer, 0xAA, sizeof(buffer));
        CHECK(utf32_to_utf8(buffer + 1, 0x110000) == 0);
        CHECK(buffer[0] == 0xAA);
        CHECK(buffer[1] == 0xAA);
    }
    {
        uint8_t buffer[6];
        memset(buffer, 0xAA, sizeof(buffer));
        CHECK(utf32_to_utf8(buffer + 1, UINT32_MAX) == 0);
        CHECK(buffer[0] == 0xAA);
        CHECK(buffer[1] == 0xAA);
    }
    return EXIT_SUCCESS;
}
