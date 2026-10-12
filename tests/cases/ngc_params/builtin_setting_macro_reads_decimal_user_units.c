#include "support/builtin_macro_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    settings.axis[X_AXIS].acceleration = 9000;
    CHECK(builtin_macro_block("G65P1Q120") == Status_OK);
    NEAR(builtin_macro_result("_value"), 2.5f);
    NEAR(builtin_macro_result("_value_returned"), 1);
    CHECK(change_callbacks == 0);
    CHECK(ngc_call_level() == 0);
    return EXIT_SUCCESS;
}
