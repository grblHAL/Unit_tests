#include "support/user_mcode_host.h"
#include "check.h"

int main(void)
{
    prepare_user_mcodes();
    user_type = UserMCode_NoValueWords;
    user_claimed.f = true;
    CHECK(user_mcode_block("M400F") == Status_OK);
    CHECK(user_validate_calls == 1 && user_execute_calls == 1);
    CHECK(isnan(user_validated.values.f) && isnan(user_executed.values.f));
    CHECK(user_executed.words.f);
    return EXIT_SUCCESS;
}
