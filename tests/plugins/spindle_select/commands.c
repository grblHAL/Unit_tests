#include "select_host.h"
#include <string.h>
int main(void)
{
    select_prepare();
    CHECK(select_binding(1, 2) == Status_OK);
    CHECK(grbl.user_mcode.check(Spindle_Select) == UserMCode_Normal);
    CHECK(select_command(true, 1, true) == Status_OK && spindle_get_default() == 1);
    CHECK(select_command(true, 0, true) == Status_OK && spindle_get_default() == 0);
    CHECK(select_command(false, 1, true) == Status_OK && spindle_get_default() == 1);
    return 0;
}
