#include "therm_host.h"
int main(void)
{
    therm_start(true);
    unsigned before = saves;
    CHECK(therm_command("THRMCAL", STATE_IDLE, "30") == Status_OK);
    CHECK(saves == before + 1);
    CHECK(therm_command("THRMTEMP", STATE_IDLE, NULL) == Status_OK);
    CHECK(strstr(output, "30.0 degC"));
    CHECK(therm_command("THRMCAL", STATE_ALARM, "20") == Status_OK);
    CHECK(therm_command("THRMTEMP", STATE_IDLE, NULL) == Status_OK);
    CHECK(strstr(output, "20.0 degC"));
    return 0;
}
