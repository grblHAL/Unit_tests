#include "support/rtcp_routing_host.h"

int main(void)
{
    prepare_rtcp_routing();
    for(unsigned code = 850; code <= 852; code++) {
        parser_block_t block = {.user_mcode = (user_mcode_t)code};
        CHECK(grbl.user_mcode.validate(&block) == Status_OK);
        CHECK(block.user_mcode_sync);
    }
    CHECK(delegated_validations == 0);
    return EXIT_SUCCESS;
}
