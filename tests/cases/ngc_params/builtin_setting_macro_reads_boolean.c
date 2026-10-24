#include "support/builtin_macro_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    CHECK(builtin_macro_block("G65P1Q13") == Status_OK);
    NEAR(builtin_macro_result("_value"), 0);
    NEAR(builtin_macro_result("_value_returned"), 1);
    CHECK(ngc_float_decimals() == N_DECIMAL_COORDVALUE_MM);
    CHECK(builtin_macro_block("G65P1Q13S1") == Status_OK);
    NEAR(builtin_macro_result("_value"), 1);
    CHECK(ngc_float_decimals() == N_DECIMAL_COORDVALUE_INCH);
    CHECK(builtin_macro_block("G65P1Q13S0") == Status_OK);
    NEAR(builtin_macro_result("_value"), 0);
    CHECK(ngc_float_decimals() == N_DECIMAL_COORDVALUE_MM);
    return EXIT_SUCCESS;
}
