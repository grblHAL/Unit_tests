#include "interlock_host.h"
int main(void)
{
    il_start();
    CHECK(il_float(900, 0) == Status_OK);
    levels[Port_Input][0] = -1;
    il_command(true);
    CHECK(hardware_spindles == 1 && resets == 0);
    input_count = 0;
    il_command(true);
    CHECK(hardware_spindles == 2 && resets == 0);
    return 0;
}
