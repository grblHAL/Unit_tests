#include "interlock_host.h"
int main(void)
{
    il_start();
    CHECK(il_float(900, 4) == Status_AuxiliaryPortUnavailable);
    CHECK(il_float(912, 4) == Status_AuxiliaryPortUnavailable);
    CHECK(il_float(900, 1) == Status_OK);
    CHECK(il_float(900, -1) == Status_OK);
    levels[Port_Input][1] = 1;
    il_command(true);
    CHECK(hardware_spindles == 1);
    return 0;
}
