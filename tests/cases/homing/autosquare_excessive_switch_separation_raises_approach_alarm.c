#include "support/autosquare_homing_host.h"

int main(void)
{
    prepare_autosquare_homing();
    settings.homing.dual_axis.fail_length_percent = 0;
    settings.homing.dual_axis.fail_distance_min = 0.125f;
    settings.homing.dual_axis.fail_distance_max = 0.125f;
    CHECK(mc_homing_cycle((axes_signals_t){.mask = X_AXIS_BIT}) == Status_Unhandled);
    CHECK(sys.alarm == Alarm_HomingFailAutoSquaringApproach);
    CHECK(sys.homed.mask == 0 && !homing_success);
    CHECK(reset_calls == 1);
    CHECK(squared_primary == 80 && squared_secondary < 120);
    return EXIT_SUCCESS;
}
