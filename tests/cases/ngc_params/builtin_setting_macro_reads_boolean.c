#include "support/builtin_macro_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    CHECK(builtin_macro_block("G65P1Q13") == Status_OK);
    NEAR(builtin_macro_result("_value"), 0);
    NEAR(builtin_macro_result("_value_returned"), 1);
    return EXIT_SUCCESS;
}
