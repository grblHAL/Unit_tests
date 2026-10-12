#include "support/builtin_modbus_host.h"
#include "check.h"

int main(void)
{
    prepare_builtin_modbus();
    builtin_bus_failure = true;
    CHECK(builtin_macro_block("G65P7F3S7R0") == Status_AccessDenied);
    CHECK(builtin_bus_calls == 1);
    NEAR(builtin_macro_result("_value_returned"), 0);
    CHECK(ngc_call_level() == 0);
    return EXIT_SUCCESS;
}
