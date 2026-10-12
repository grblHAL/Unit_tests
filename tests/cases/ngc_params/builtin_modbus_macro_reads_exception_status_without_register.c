#include "support/builtin_modbus_host.h"
#include "check.h"

int main(void)
{
    prepare_builtin_modbus();
    CHECK(builtin_macro_block("G65P7F7S7") == Status_OK);
    CHECK(builtin_bus_request.adu[0] == 7 && builtin_bus_request.adu[1] == 7);
    CHECK(builtin_bus_request.tx_length == 4 && builtin_bus_request.rx_length == 5);
    NEAR(builtin_macro_result("_value"), 165);
    NEAR(builtin_macro_result("_value_returned"), 1);
    return EXIT_SUCCESS;
}
