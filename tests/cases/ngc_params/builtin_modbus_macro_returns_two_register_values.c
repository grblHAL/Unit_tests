#include "support/builtin_modbus_host.h"
#include "check.h"

int main(void)
{
    prepare_builtin_modbus();
    builtin_reply_registers = 2;
    CHECK(builtin_macro_block("G65P7F3S7R0X2") == Status_OK);
    NEAR(builtin_macro_result("_value"), 17);
    NEAR(builtin_macro_result("_value2"), 34);
    NEAR(builtin_macro_result("_value_returned"), 2);
    return EXIT_SUCCESS;
}
