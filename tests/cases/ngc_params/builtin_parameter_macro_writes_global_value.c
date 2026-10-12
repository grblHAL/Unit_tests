#include "support/builtin_macro_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    CHECK(builtin_macro_block("G65P3I100Q42.5") == Status_OK);
    float value;
    CHECK(ngc_param_get(100, &value));
    NEAR(value, 42.5f);
    NEAR(builtin_macro_result("_value_returned"), 0);
    CHECK(ngc_call_level() == 0);
    return EXIT_SUCCESS;
}
