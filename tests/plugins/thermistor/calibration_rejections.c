#include "therm_host.h"
int main(void)
{
    therm_start(true);
    unsigned before = saves;
    CHECK(therm_command("THRMCAL", STATE_CYCLE, "30") == Status_IdleError);
    CHECK(therm_command("THRMCAL", STATE_IDLE, NULL) == Status_BadNumberFormat);
    CHECK(therm_command("THRMCAL", STATE_IDLE, "") == Status_BadNumberFormat);
    CHECK(therm_command("THRMCAL", STATE_IDLE, "bad") == Status_BadNumberFormat);
    adc = 0;
    CHECK(therm_command("THRMCAL", STATE_IDLE, "30") == Status_GcodeValueWordMissing);
    CHECK(saves == before);
    return 0;
}
