#include "support/rtcp_routing_host.h"

int main(void)
{
    prepare_rtcp_routing();
    parser_block_t block = {.user_mcode = (user_mcode_t)900};
    grbl.user_mcode.execute(STATE_CHECK_MODE, &block);
    CHECK(delegated_executions == 1 && delegated_block == &block);
    CHECK(delegated_state == STATE_CHECK_MODE);
    return EXIT_SUCCESS;
}
