#include "support/rtcp_routing_host.h"

int main(void)
{
    prepare_rtcp_routing();
    CHECK(grbl.user_mcode.check((user_mcode_t)900) == UserMCode_Normal);
    CHECK(delegated_checks == 1);
    CHECK(grbl.user_mcode.check((user_mcode_t)851) == UserMCode_NoValueWords);
    CHECK(delegated_checks == 1);
    return EXIT_SUCCESS;
}
