#include "interlock_host.h"
int main(void)
{
    il_start();
    CHECK(il_float(901, 3) == Status_OK);
    il_int(905, 1);
    il_int(909, 0);
    levels[Port_Output][3] = 0;
    il_command(true);
    CHECK(hardware_spindles == 0 && resets == 1);
    CHECK(strstr(warning, "FWD1 OUT P3 low"));
    levels[Port_Output][3] = 1;
    il_command(true);
    CHECK(hardware_spindles == 1);
    return 0;
}
