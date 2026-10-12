#include "support/user_mcode_host.h"
#include "check.h"

int main(void)
{
    prepare_user_mcodes();
    user_claimed.f = true;
    CHECK(user_mcode_block("M400F") == Status_BadNumberFormat);
    CHECK(user_validate_calls == 0 && user_execute_calls == 0);
    return EXIT_SUCCESS;
}
