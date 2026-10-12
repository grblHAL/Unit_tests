#include "support/user_mcode_host.h"
#include "check.h"

int main(void)
{
    prepare_user_mcodes();
    user_claimed.s = true;
    CHECK(user_mcode_block("M400S123") == Status_OK);
    CHECK(user_execute_calls == 1 && user_executed.words.s);
    NEAR(user_executed.values.s, 123);
    NEAR(gc_spindle_get(0)->rpm, 0);
    return EXIT_SUCCESS;
}
