#include "support/builtin_macro_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    CHECK(builtin_macro_block("G65P1Q13S1") == Status_OK);
    CHECK(settings.flags.report_inches);
    NEAR(builtin_macro_result("_value"), 1);
    NEAR(builtin_macro_result("_value_returned"), 1);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
