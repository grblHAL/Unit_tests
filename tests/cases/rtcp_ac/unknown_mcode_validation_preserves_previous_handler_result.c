#include "support/rtcp_routing_host.h"

int main(void)
{
    prepare_rtcp_routing();
    parser_block_t block = {.user_mcode = (user_mcode_t)900};
    CHECK(grbl.user_mcode.validate(&block) == Status_GcodeValueWordMissing);
    CHECK(delegated_validations == 1 && delegated_block == &block);
    CHECK(!block.user_mcode_sync);
    return EXIT_SUCCESS;
}
