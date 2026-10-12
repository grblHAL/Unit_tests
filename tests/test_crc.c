#include <stdint.h>
#include "crc.h"
#include "check.h"

int main(void)
{
    const uint8_t text[] = "123456789";
    const uint8_t request[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x0A};
    const uint8_t wrapped[] = {0xEE, 0x01, 0x03, 0x00, 0x00, 0x00, 0x0A, 0xEE};
    const uint8_t high[] = {0x80, 0xFF};
    const uint8_t zero[] = {0, 0, 0, 0};
    CHECK(grbl_crc8(NULL, 0) == 0);
    CHECK(modbus_crc16x(NULL, 0) == 0xFFFF);
    CHECK(ccitt_crc16(NULL, 0) == 0);
    /* Standard CRC-16/MODBUS and CRC-16/XMODEM check vectors. */
    CHECK(modbus_crc16x(text, 9) == 0x4B37);
    CHECK(ccitt_crc16(text, 9) == 0x31C3);
    CHECK(modbus_crc16x(request, sizeof(request)) == 0xCDC5);
    CHECK(modbus_crc16x(wrapped + 1, sizeof(request)) == 0xCDC5);
    CHECK(modbus_crc16x(text, 1) == 0x947E);
    CHECK(ccitt_crc16(text, 1) == 0x2672);
    /* grbl's rotating additive checksum: 0x80 rotates to 1, then +255 wraps to 0. */
    CHECK(grbl_crc8(high, 1) == 0x80);
    CHECK(grbl_crc8(high, 2) == 0);
    CHECK(grbl_crc8(zero, sizeof(zero)) == 0);
    CHECK(ccitt_crc16(zero, sizeof(zero)) == 0);
    puts("CRC checks passed");
    return EXIT_SUCCESS;
}
