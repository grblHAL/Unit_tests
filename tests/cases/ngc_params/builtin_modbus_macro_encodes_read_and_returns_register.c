#include "support/builtin_modbus_host.h"
#include "check.h"

int main(void)
{
    prepare_builtin_modbus();
    CHECK(builtin_macro_block("G65P7F3S7R4660") == Status_OK);
    CHECK(builtin_bus_calls == 1);
    uint8_t expected[] = {7, 3, 0x12, 0x34, 0, 1};
    CHECK(memcmp(builtin_bus_request.adu, expected, sizeof(expected)) == 0);
    CHECK(builtin_bus_request.tx_length == 8 && builtin_bus_request.rx_length == 7);
    NEAR(builtin_macro_result("_value"), 17);
    NEAR(builtin_macro_result("_value_returned"), 1);
    return EXIT_SUCCESS;
}
