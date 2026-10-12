#include "support/builtin_macro_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    CHECK(builtin_macro_block("G65P1Q120S2.5") == Status_OK);
    NEAR(settings.axis[X_AXIS].acceleration, 9000);
    NEAR(builtin_macro_result("_value"), 2.5f);
    NEAR(builtin_macro_result("_value_returned"), 1);
    NEAR(gc_state.modal.spindle[0].rpm, 0);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
