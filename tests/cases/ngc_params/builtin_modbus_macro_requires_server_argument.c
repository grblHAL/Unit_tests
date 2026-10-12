#include "support/builtin_modbus_host.h"
#include "check.h"

int main(void)
{
    prepare_builtin_modbus();
    CHECK(builtin_macro_block("G65P7F3R0") == Status_GcodeValueWordMissing);
    CHECK(builtin_bus_calls == 0);
    CHECK(ngc_call_level() == 0);
    return EXIT_SUCCESS;
}
