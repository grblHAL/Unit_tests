#include "support/user_mcode_host.h"
#include "check.h"

int main(void)
{
    prepare_user_mcodes();
    gc_state.feed_rate = 100;
    user_claimed.f = true;
    CHECK(user_mcode_block("M400F42.5") == Status_OK);
    CHECK(user_execute_calls == 1 && user_executed.words.f);
    NEAR(user_executed.values.f, 42.5f);
    NEAR(gc_state.feed_rate, 100);
    return EXIT_SUCCESS;
}
