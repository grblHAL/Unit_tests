#include "support/user_mcode_host.h"
#include "check.h"

int main(void)
{
    prepare_user_mcodes();
    CHECK(user_mcode_block("M400M400") == Status_GcodeModalGroupViolation);
    CHECK(user_validate_calls == 0 && user_execute_calls == 0);
    return EXIT_SUCCESS;
}
