#include "support/rtcp_host.h"
#include "check.h"

int main(void)
{
    prepare_rtcp();
    CHECK(grbl.user_mcode.check((user_mcode_t)850) == UserMCode_NoValueWords);
    CHECK(grbl.user_mcode.check((user_mcode_t)851) == UserMCode_NoValueWords);
    CHECK(grbl.user_mcode.check((user_mcode_t)852) == UserMCode_NoValueWords);
    CHECK(grbl.user_mcode.check((user_mcode_t)853) == UserMCode_Unsupported);
    return EXIT_SUCCESS;
}
