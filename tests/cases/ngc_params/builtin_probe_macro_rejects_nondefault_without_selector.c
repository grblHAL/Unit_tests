#include "support/builtin_macro_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    CHECK(builtin_macro_block("G65P5Q1") == Status_GcodeValueOutOfRange);
    NEAR(builtin_macro_result("_value_returned"), 0);
    return EXIT_SUCCESS;
}
