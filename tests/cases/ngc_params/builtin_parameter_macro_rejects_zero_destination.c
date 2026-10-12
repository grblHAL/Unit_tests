#include "support/builtin_macro_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    CHECK(ngc_param_set(100, 12.5f));
    CHECK(builtin_macro_block("G65P3I100S0") == Status_GcodeValueOutOfRange);
    float value;
    CHECK(ngc_param_get(100, &value));
    NEAR(value, 12.5f);
    CHECK(ngc_call_level() == 0);
    return EXIT_SUCCESS;
}
