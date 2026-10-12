#include "support/user_mcode_host.h"
#include "check.h"

int main(void)
{
    prepare_user_mcodes();
    user_claimed.i = user_claimed.j = user_claimed.k = true;
    CHECK(user_mcode_block("M400I1J2K3") == Status_OK);
    CHECK(user_execute_calls == 1);
    CHECK(user_executed.words.i && user_executed.words.j && user_executed.words.k);
    NEAR(user_executed.values.ijk[0], 1);
    NEAR(user_executed.values.ijk[1], 2);
    NEAR(user_executed.values.ijk[2], 3);
    return EXIT_SUCCESS;
}
