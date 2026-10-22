#include "support/builtin_macro_host.h"

int main(void)
{
    prepare_settings_store();
    CHECK(grbl.tool_table.n_tools == 0);
    CHECK(ngc_param_set(17, 31));
    CHECK(builtin_macro_block("G65P2Q1R2") == Status_GcodeIllegalToolTableEntry);
    CHECK(ngc_call_level() == 0);
    NEAR(builtin_macro_result("_value_returned"), 0);
    float value;
    CHECK(ngc_param_get(17, &value));
    NEAR(value, 31);
    CHECK(builtin_macro_block("G65P3I100Q9") == Status_OK);
    CHECK(ngc_param_get(100, &value));
    NEAR(value, 9);
    CHECK(ngc_call_level() == 0 && grbl.tool_table.n_tools == 0);
    return EXIT_SUCCESS;
}
