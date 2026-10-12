#include "support/builtin_macro_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    CHECK(!sys.override.control.spindle_wait_disable);
    CHECK(builtin_macro_block("G65P6") == Status_OK);
    CHECK(sys.override.control.spindle_wait_disable);
    NEAR(builtin_macro_result("_value_returned"), 0);
    return EXIT_SUCCESS;
}
