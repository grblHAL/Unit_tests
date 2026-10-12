#include "support/user_mcode_host.h"
#include "check.h"

int main(void)
{
    prepare_user_mcodes();
    user_claimed.x = true;
    CHECK(user_mcode_block("M400X12.5") == Status_OK);
    CHECK(user_execute_calls == 1 && user_executed.words.x);
    NEAR(user_executed.values.xyz[X_AXIS], 12.5f);
    NEAR(gc_state.position[X_AXIS], 0);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
