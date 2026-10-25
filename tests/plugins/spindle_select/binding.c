#include "select_host.h"
#include <string.h>
int main(void)
{
    select_prepare();
    CHECK(select_binding(1, 1) == Status_InvalidStatement);
    CHECK(select_binding(1, 3) == Status_SettingValueOutOfRange);
    CHECK(select_binding(1, 2) == Status_OK);
    CHECK(spindle_select_get_binding(0) == 0 && spindle_select_get_binding(1) == 1);
    CHECK(select_binding(1, 0) == Status_OK);
    CHECK(spindle_select_get_binding(1) == -1 && spindle_select_get_binding(-1) == -1);
    return 0;
}
