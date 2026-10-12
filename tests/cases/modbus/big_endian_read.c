#include <string.h>
#include "grbl.h"
#include "modbus.h"
#include "check.h"

int main(void)
{
    uint8_t bytes[] = {0xEE, 0x12, 0x34, 0xEE};
    CHECK(modbus_read_u16(bytes + 1) == 0x1234);
    uint8_t maximum[] = {0xFF, 0xFF}; CHECK(modbus_read_u16(maximum) == UINT16_MAX);
    return EXIT_SUCCESS;
}
