#include "support/user_mcode_host.h"
#include "check.h"

int main(void)
{
    prepare_user_mcodes();
    user_type = UserMCode_NoValueWords;
    user_claimed.p = user_claimed.q = true;
    CHECK(user_mcode_block("M400PQ3") == Status_OK);
    CHECK(user_execute_calls == 1);
    CHECK(isnan(user_executed.values.p));
    NEAR(user_executed.values.q, 3.0f);
    return EXIT_SUCCESS;
}
