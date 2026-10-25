#include "therm_host.h"
int main(void)
{
    therm_start(false);
    CHECK(claims == 0);
    CHECK(therm_command("THRMTEMP", STATE_IDLE, NULL) == Status_InvalidStatement);
    CHECK(therm_command("THRMCAL", STATE_IDLE, "25") == Status_InvalidStatement);
    therm_report(true);
    CHECK(strcmp(output, "|previous") == 0 && reads == 0);
    return 0;
}
