#include "support/builtin_macro_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    CHECK(ngc_param_set(100, 12.5f));
    CHECK(builtin_macro_block("G65P3I100") == Status_OK);
    NEAR(builtin_macro_result("_value"), 12.5f);
    NEAR(builtin_macro_result("_value_returned"), 1);
    CHECK(ngc_call_level() == 0);
    return EXIT_SUCCESS;
}
