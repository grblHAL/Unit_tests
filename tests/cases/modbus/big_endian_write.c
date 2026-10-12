#include <string.h>
#include "grbl.h"
#include "modbus.h"
#include "check.h"

int main(void)
{
    uint8_t bytes[] = {0xEE, 0, 0, 0xEE};
    modbus_write_u16(bytes + 1, 0x1234);
    CHECK(bytes[1] == 0x12); CHECK(bytes[2] == 0x34); CHECK(bytes[0] == 0xEE); CHECK(bytes[3] == 0xEE);
    modbus_write_u16(bytes + 1, UINT16_MAX); CHECK(modbus_read_u16(bytes + 1) == UINT16_MAX);
    return EXIT_SUCCESS;
}
