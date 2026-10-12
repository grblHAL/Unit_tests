#include "support/builtin_modbus_host.h"
#include "check.h"

int main(void)
{
    prepare_builtin_modbus();
    CHECK(builtin_macro_block("G65P7F15S7R16A4660X16") == Status_OK);
    uint8_t expected[] = {7, 15, 0, 16, 0, 16, 2, 0x34, 0x12};
    CHECK(memcmp(builtin_bus_request.adu, expected, sizeof(expected)) == 0);
    CHECK(builtin_bus_request.tx_length == 11);
    CHECK(builtin_bus_calls == 1);
    return EXIT_SUCCESS;
}
