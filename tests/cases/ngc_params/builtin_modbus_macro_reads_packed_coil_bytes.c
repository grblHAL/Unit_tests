#include "support/builtin_modbus_host.h"
#include "check.h"

int main(void)
{
    prepare_builtin_modbus();
    CHECK(builtin_macro_block("G65P7F1S7R16X10") == Status_OK);
    uint8_t expected[] = {7, 1, 0, 16, 0, 10};
    CHECK(memcmp(builtin_bus_request.adu, expected, sizeof(expected)) == 0);
    CHECK(builtin_bus_request.rx_length == 7);
    NEAR(builtin_macro_result("_value"), 170);
    NEAR(builtin_macro_result("_value2"), 1);
    NEAR(builtin_macro_result("_value_returned"), 2);
    return EXIT_SUCCESS;
}
