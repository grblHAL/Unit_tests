#include <stdint.h>
#include <string.h>
#include "utf8.h"
#include "check.h"

int main(void)
{
    {
        uint8_t buffer[6];
        memset(buffer, 0xAA, sizeof(buffer));
        CHECK(utf32_to_utf8(buffer + 1, 0x80) == 2);
        CHECK(buffer[1] == 0xC2);
        CHECK(buffer[2] == 0x80);
        CHECK(buffer[0] == 0xAA);
        CHECK(buffer[3] == 0xAA);
    }
    {
        uint8_t buffer[6];
        memset(buffer, 0xAA, sizeof(buffer));
        CHECK(utf32_to_utf8(buffer + 1, 0x7FF) == 2);
        CHECK(buffer[1] == 0xDF);
        CHECK(buffer[2] == 0xBF);
        CHECK(buffer[0] == 0xAA);
        CHECK(buffer[3] == 0xAA);
    }
    return EXIT_SUCCESS;
}
