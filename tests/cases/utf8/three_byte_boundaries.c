#include <stdint.h>
#include <string.h>
#include "utf8.h"
#include "check.h"

int main(void)
{
    {
        uint8_t buffer[6];
        memset(buffer, 0xAA, sizeof(buffer));
        CHECK(utf32_to_utf8(buffer + 1, 0x800) == 3);
        CHECK(buffer[1] == 0xE0);
        CHECK(buffer[2] == 0xA0);
        CHECK(buffer[3] == 0x80);
        CHECK(buffer[0] == 0xAA);
        CHECK(buffer[4] == 0xAA);
    }
    {
        uint8_t buffer[6];
        memset(buffer, 0xAA, sizeof(buffer));
        CHECK(utf32_to_utf8(buffer + 1, 0xFFFF) == 3);
        CHECK(buffer[1] == 0xEF);
        CHECK(buffer[2] == 0xBF);
        CHECK(buffer[3] == 0xBF);
        CHECK(buffer[0] == 0xAA);
        CHECK(buffer[4] == 0xAA);
    }
    {
        uint8_t buffer[6];
        memset(buffer, 0xAA, sizeof(buffer));
        CHECK(utf32_to_utf8(buffer + 1, 0x20AC) == 3);
        CHECK(buffer[1] == 0xE2);
        CHECK(buffer[2] == 0x82);
        CHECK(buffer[3] == 0xAC);
        CHECK(buffer[0] == 0xAA);
        CHECK(buffer[4] == 0xAA);
    }
    return EXIT_SUCCESS;
}
