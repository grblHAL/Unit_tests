#include "therm_host.h"
int main(void)
{
    claim_ok = false;
    therm_start(true);
    CHECK(claims == 1);
    CHECK(therm_command("THRMTEMP", STATE_IDLE, NULL) == Status_InvalidStatement);
    therm_report(true);
    CHECK(strcmp(output, "|previous") == 0 && reads == 0);
    return 0;
}
