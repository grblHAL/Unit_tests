#include "onoff_host.h"
int main(void)
{
    on_prepare(2);
    on_settings->restore();
    CHECK(on_set(Setting_Spindle_OnPort, -1) == Status_OK);
    CHECK(on_get(Setting_Spindle_OnPort) == -1);
    on_settings->save();
    on_load();
    CHECK(on_warnings == 1 && !spindle_get(0) && !on_writes);
    return 0;
}
