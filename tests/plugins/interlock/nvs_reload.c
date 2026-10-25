#include "interlock_host.h"
int main(void)
{
    il_start();
    CHECK(il_float(900, 1) == Status_OK);
    registered_settings->save();
    CHECK(il_float(900, -1) == Status_OK);
    registered_settings->load();
    levels[Port_Input][1] = 1;
    il_command(true);
    CHECK(resets == 1 && hardware_spindles == 0 && saves == 2);
    return 0;
}
