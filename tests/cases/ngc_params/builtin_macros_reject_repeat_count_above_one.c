#include "support/builtin_macro_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    CHECK(builtin_macro_block("G65P1Q13L2") == Status_GcodeValueOutOfRange);
    NEAR(builtin_macro_result("_value_returned"), 0);
    CHECK(change_callbacks == 0);
    CHECK(ngc_call_level() == 0);
    return EXIT_SUCCESS;
}
