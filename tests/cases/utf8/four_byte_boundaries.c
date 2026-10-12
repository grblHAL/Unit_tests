#include <stdint.h>
#include <string.h>
#include "utf8.h"
#include "check.h"

int main(void)
{
    {
        uint8_t buffer[6];
        memset(buffer, 0xAA, sizeof(buffer));
        CHECK(utf32_to_utf8(buffer + 1, 0x10000) == 4);
        CHECK(buffer[1] == 0xF0);
        CHECK(buffer[2] == 0x90);
        CHECK(buffer[3] == 0x80);
        CHECK(buffer[4] == 0x80);
        CHECK(buffer[0] == 0xAA);
        CHECK(buffer[5] == 0xAA);
    }
    {
        uint8_t buffer[6];
        memset(buffer, 0xAA, sizeof(buffer));
        CHECK(utf32_to_utf8(buffer + 1, 0x10FFFF) == 4);
        CHECK(buffer[1] == 0xF4);
        CHECK(buffer[2] == 0x8F);
        CHECK(buffer[3] == 0xBF);
        CHECK(buffer[4] == 0xBF);
        CHECK(buffer[0] == 0xAA);
        CHECK(buffer[5] == 0xAA);
    }
    {
        uint8_t buffer[6];
        memset(buffer, 0xAA, sizeof(buffer));
        CHECK(utf32_to_utf8(buffer + 1, 0x1F600) == 4);
        CHECK(buffer[1] == 0xF0);
        CHECK(buffer[2] == 0x9F);
        CHECK(buffer[3] == 0x98);
        CHECK(buffer[4] == 0x80);
        CHECK(buffer[0] == 0xAA);
        CHECK(buffer[5] == 0xAA);
    }
    return EXIT_SUCCESS;
}
