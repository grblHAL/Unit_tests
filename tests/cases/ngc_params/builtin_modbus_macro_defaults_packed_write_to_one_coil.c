#include "support/builtin_modbus_host.h"
#include "check.h"

int main(void)
{
    prepare_builtin_modbus();
    /* Omitting X writes one coil; the next command must not inherit its value. */
    const char *commands[] = {"G65P7F15S7R16A1", "G65P7F15S7R16A0"};
    for(unsigned i = 0; i < 2; i++) {
        CHECK(builtin_macro_block(commands[i]) == Status_OK);
        const uint8_t expected[] = {7, 15, 0, 16, 0, 1, 1, (uint8_t)(1 - i)};
        CHECK(builtin_bus_request.tx_length == sizeof(expected) + 2);
        CHECK(memcmp(builtin_bus_request.adu, expected, sizeof(expected)) == 0);
        CHECK(builtin_bus_calls == i + 1);
        NEAR(builtin_macro_result("_value_returned"), 2);
    }
    return EXIT_SUCCESS;
}
