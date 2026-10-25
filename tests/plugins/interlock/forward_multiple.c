#include "interlock_host.h"
int main(void)
{
    il_start();
    CHECK(il_float(900, 0) == Status_OK && il_float(903, 3) == Status_OK);
    levels[Port_Input][0] = 1;
    levels[Port_Input][3] = 1;
    il_command(true);
    CHECK(resets == 1 && warnings == 1);
    CHECK(strstr(warning, "FWD0 IN P0 high") && strstr(warning, "FWD3 IN P3 high"));
    return 0;
}
