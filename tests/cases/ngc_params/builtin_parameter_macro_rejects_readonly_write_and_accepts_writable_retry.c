#include "support/builtin_macro_host.h"

int main(void)
{
    prepare_settings_store();
    float before, after;
    CHECK(ngc_param_get(5420, &before));
    CHECK(ngc_param_set(17, 31));
    CHECK(builtin_macro_block("G65P3I5420Q7") == Status_GcodeValueOutOfRange);
    CHECK(ngc_param_get(5420, &after));
    NEAR(after, before);
    CHECK(ngc_param_get(17, &after));
    NEAR(after, 31);
    CHECK(ngc_call_level() == 0);
    NEAR(builtin_macro_result("_value_returned"), 0);
    CHECK(builtin_macro_block("G65P3I100Q9") == Status_OK);
    CHECK(ngc_param_get(100, &after));
    NEAR(after, 9);
    CHECK(ngc_param_get(5420, &after));
    NEAR(after, before);
    CHECK(ngc_call_level() == 0);
    return EXIT_SUCCESS;
}
