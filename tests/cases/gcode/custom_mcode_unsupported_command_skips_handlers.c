#include "support/user_mcode_host.h"
#include "check.h"

int main(void)
{
    prepare_user_mcodes();
    CHECK(user_mcode_block("M499") == Status_GcodeUnsupportedCommand);
    CHECK(user_check_calls == 1);
    CHECK(user_validate_calls == 0);
    CHECK(user_execute_calls == 0);
    return EXIT_SUCCESS;
}
