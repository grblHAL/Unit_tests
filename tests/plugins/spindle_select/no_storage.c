#include "select_host.h"
#include <string.h>
int main(void)
{
    select_storage = false;
    select_prepare();
    CHECK(!select_settings && select_warnings == 1);
    CHECK(grbl.user_mcode.check(Spindle_Select) == UserMCode_Unsupported);
    return 0;
}
