#include "select_host.h"
#include <string.h>
int main(void)
{
    select_prepare();
    CHECK(select_binding(1, 2) == Status_OK);
    CHECK(select_command(true, 0.5f, false) == Status_GcodeValueOutOfRange);
    CHECK(select_command(false, 8, false) == Status_GcodeValueOutOfRange);
    CHECK(select_command(false, -1, false) == Status_GcodeValueOutOfRange);
    CHECK(select_command(false, 2, false) == Status_GcodeValueOutOfRange);
    parser_block_t b = {.user_mcode = Spindle_Select};
    CHECK(grbl.user_mcode.validate(&b) != Status_OK);
    b.words.p = b.words.q = On;
    b.values.p = 1;
    b.values.q = 1;
    CHECK(grbl.user_mcode.validate(&b) == Status_GcodeValueOutOfRange);
    return 0;
}
