#include "select_host.h"
#include <string.h>
int main(void)
{
    select_setup_ok = false;
    select_prepare();
    CHECK(select_settings && !select_warnings);
    CHECK(grbl.user_mcode.check(Spindle_Select) == UserMCode_Unsupported);
    CHECK(select_previous_checks == 1);
    return 0;
}
