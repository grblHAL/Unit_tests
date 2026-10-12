#include "support/builtin_macro_host.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    state_set(STATE_IDLE);
    CHECK(builtin_macro_block("G65P4") == Status_OK);
    NEAR(builtin_macro_result("_value"), 0);
    NEAR(builtin_macro_result("_value_returned"), 1);
    return EXIT_SUCCESS;
}
