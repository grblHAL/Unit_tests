#include "support/user_mcode_host.h"
#include "check.h"

int main(void)
{
    prepare_user_mcodes();
    user_claimed.t = true;
    CHECK(user_mcode_block("M400T12.5") == Status_OK);
    CHECK(user_execute_calls == 1 && user_executed.words.t);
    NEAR(user_executed.values.t, 12.5f);
    CHECK(gc_state.tool_pending == 0);
    return EXIT_SUCCESS;
}
