#include "support/user_mcode_host.h"
#include "check.h"

int main(void)
{
    prepare_user_mcodes();
    user_type = UserMCode_NoValueWords;
    user_claimed.p = user_claimed.q = true;
    CHECK(user_mcode_block("M400PQ") == Status_OK);
    CHECK(user_validate_calls == 1 && user_execute_calls == 1);
    CHECK(isnan(user_validated.values.p));
    CHECK(isnan(user_validated.values.q));
    CHECK(isnan(user_executed.values.p));
    CHECK(isnan(user_executed.values.q));
    return EXIT_SUCCESS;
}
