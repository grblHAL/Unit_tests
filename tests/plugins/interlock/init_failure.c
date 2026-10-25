#include "interlock_host.h"
int main(void)
{
    il_prepare();
    alloc_ok = false;
    spindle_interlock_init();
    CHECK(!registered_settings && startup_warnings == 1);
    CHECK(grbl.on_spindle_select(&spindle));
    il_command(true);
    CHECK(hardware_spindles == 1 && resets == 0);
    return 0;
}
