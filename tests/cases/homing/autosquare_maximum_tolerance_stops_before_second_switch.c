#include "support/autosquare_homing_host.h"

int main(void)
{
    prepare_autosquare_homing();
    char percentage[] = "20", minimum[] = "0.1", maximum[] = "0.25";
    CHECK(settings_store_setting(Setting_DualAxisLengthFailPercent, percentage) == Status_OK);
    CHECK(settings_store_setting(Setting_DualAxisLengthFailMin, minimum) == Status_OK);
    CHECK(settings_store_setting(Setting_DualAxisLengthFailMax, maximum) == Status_OK);
    CHECK(mc_homing_cycle((axes_signals_t){.mask = X_AXIS_BIT}) == Status_Unhandled);
    CHECK(sys.alarm == Alarm_HomingFailAutoSquaringApproach);
    CHECK(sys.homed.mask == 0 && !homing_success && reset_calls == 1);
    CHECK(squared_primary == 80 && squared_secondary > 80 && squared_secondary < 120);
    CHECK(squared_switches().a.x && !squared_switches().b.x);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
