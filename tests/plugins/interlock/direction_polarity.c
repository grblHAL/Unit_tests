#include "interlock_host.h"
int main(void)
{
    il_start();
    CHECK(il_float(900, 1) == Status_OK);
    levels[Port_Input][1] = 1;
    levels[Port_Output][1] = 0;
    il_command(true);
    CHECK(hardware_spindles == 0 && resets == 1 && strstr(warning, "IN P1 high"));
    il_int(904, 1);
    il_command(true);
    CHECK(hardware_spindles == 1 && resets == 1);
    il_int(908, 0);
    il_command(true);
    CHECK(hardware_spindles == 1 && resets == 2 && strstr(warning, "OUT P1 low"));
    levels[Port_Output][1] = 1;
    il_command(true);
    CHECK(hardware_spindles == 2 && resets == 2);
    il_int(904, 0);
    il_command(true);
    CHECK(hardware_spindles == 3 && resets == 2 && il_read_int(904) == 0 && il_read_int(908) == 0);
    return 0;
}
