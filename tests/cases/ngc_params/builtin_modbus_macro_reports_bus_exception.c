#include "support/builtin_modbus_host.h"
#include "check.h"

int main(void)
{
    prepare_builtin_modbus();
    builtin_bus_exception = 2;
    CHECK(builtin_macro_block("G65P7F3S7R0") == Status_OK);
    NEAR(builtin_macro_result("_value"), 2);
    NEAR(builtin_macro_result("_value_returned"), 0);
    return EXIT_SUCCESS;
}
