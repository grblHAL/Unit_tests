#include "support/builtin_modbus_host.h"
#include "check.h"

int main(void)
{
    prepare_builtin_modbus();
    CHECK(builtin_macro_block("G65P7F16S7R16A4660B22136C39612") == Status_OK);
    uint8_t expected[] = {7, 16, 0, 16, 0, 3, 6, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC};
    CHECK(memcmp(builtin_bus_request.adu, expected, sizeof(expected)) == 0);
    CHECK(builtin_bus_request.tx_length == 15);
    CHECK(builtin_bus_calls == 1);
    return EXIT_SUCCESS;
}
