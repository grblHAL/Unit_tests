#include "support/user_mcode_host.h"
#include "check.h"

int main(void)
{
    prepare_user_mcodes();
    CHECK(user_mcode_block("M400") == Status_OK);
    CHECK(user_validate_calls == 1 && user_execute_calls == 1);
    CHECK(user_executed.user_mcode == OpenPNP_FinishMoves);
    CHECK(user_execution_state == STATE_IDLE);
    return EXIT_SUCCESS;
}
