#include "support/user_mcode_host.h"
#include "check.h"

int main(void)
{
    prepare_user_mcodes();
    CHECK(user_mcode_block("M400P1") == Status_GcodeUnusedWords);
    CHECK(user_validate_calls == 1 && user_execute_calls == 0);
    return EXIT_SUCCESS;
}
