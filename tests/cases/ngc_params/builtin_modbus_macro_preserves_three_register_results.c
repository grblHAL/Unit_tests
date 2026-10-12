#include "support/builtin_modbus_host.h"
#include "check.h"

int main(void)
{
    prepare_builtin_modbus();
    builtin_reply_registers = 3;
    CHECK(builtin_macro_block("G65P7F3S7R0X3") == Status_OK);
    NEAR(builtin_macro_result("_value_returned"), 3);
    NEAR(builtin_macro_result("_value"), 17);
    fprintf(stderr, "observed second result=%g, expected=34\n", builtin_macro_result("_value2"));
    NEAR(builtin_macro_result("_value2"), 34);
    NEAR(builtin_macro_result("_value3"), 51);
    return EXIT_SUCCESS;
}
