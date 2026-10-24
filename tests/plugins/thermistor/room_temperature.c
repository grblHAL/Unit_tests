#include "therm_host.h"
int main(void)
{
    therm_start(true);
    CHECK(claims == 1);
    CHECK(therm_command("THRMTEMP", STATE_IDLE, NULL) == Status_OK);
    CHECK(strstr(output, "25.0 degC") && reads == 1);
    return 0;
}
