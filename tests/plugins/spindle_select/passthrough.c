#include "select_host.h"
#include <string.h>
int main(void)
{
    select_prepare();
    CHECK(grbl.user_mcode.check((user_mcode_t)999) == UserMCode_Unsupported);
    parser_block_t b = {.user_mcode = (user_mcode_t)999};
    CHECK(grbl.user_mcode.validate(&b) == Status_Unhandled);
    grbl.user_mcode.execute(STATE_IDLE, &b);
    CHECK(select_previous_checks == 1 && select_previous_validates == 1 &&
          select_previous_executes == 1);
    return 0;
}
