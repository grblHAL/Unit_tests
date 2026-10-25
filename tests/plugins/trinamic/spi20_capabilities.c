#include "tmc_host.h"
int main(void)
{
    tmc_prepare();
    tmc_start();
    CHECK(tmc_drivers[0]->get_en_pwm_mode == NULL);
    CHECK(grbl.user_mcode.check(Trinamic_ModeToggle) == UserMCode_Unsupported);
    CHECK(grbl.user_mcode.check(Trinamic_StepperCurrent) == UserMCode_Normal);
    CHECK(grbl.user_mcode.check(Trinamic_DebugReport) == UserMCode_NoValueWords);
    return 0;
}
