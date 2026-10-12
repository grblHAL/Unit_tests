#include "support/builtin_modbus_host.h"
#include "check.h"

int main(void)
{
    prepare_builtin_modbus();
    CHECK(builtin_macro_block("G65P7F6S7R4660A22136") == Status_OK);
    uint8_t expected[] = {7, 6, 0x12, 0x34, 0x56, 0x78};
    CHECK(memcmp(builtin_bus_request.adu, expected, sizeof(expected)) == 0);
    CHECK(builtin_bus_request.tx_length == 8);
    CHECK(builtin_bus_calls == 1);
    NEAR(builtin_macro_result("_value_returned"), 2);
    return EXIT_SUCCESS;
}
