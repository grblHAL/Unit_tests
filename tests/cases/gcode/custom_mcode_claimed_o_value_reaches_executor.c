#include "support/user_mcode_host.h"
#include "check.h"

int main(void)
{
    prepare_user_mcodes();
    user_claimed.o = true;
    CHECK(user_mcode_block("M400O42") == Status_OK);
    CHECK(user_execute_calls == 1 && user_executed.words.o);
    CHECK(user_executed.values.o == 42);
    return EXIT_SUCCESS;
}
