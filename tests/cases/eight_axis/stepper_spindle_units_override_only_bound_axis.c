#include "support/secondary_spindle_host.h"

int main(void)
{
    prepare_spindle_motor();
    CHECK(st2_motor_bind_spindle(A_AXIS, &settings.axis[A_AXIS]));
    CHECK(strcmp(grbl.on_set_axis_setting_unit(Setting_AxisStepsPerMM, A_AXIS), "step/rev") == 0);
    CHECK(strcmp(grbl.on_set_axis_setting_unit(Setting_AxisMaxRate, A_AXIS), "rev/min") == 0);
    CHECK(strcmp(grbl.on_set_axis_setting_unit(Setting_AxisAcceleration, A_AXIS), "rev/sec^2") == 0);
    CHECK(strcmp(grbl.on_set_axis_setting_unit(Setting_AxisMaxTravel, A_AXIS), "--") == 0);
    CHECK(strcmp(grbl.on_set_axis_setting_unit(Setting_AxisStepsPerMM, X_AXIS), "original unit") == 0);
    return EXIT_SUCCESS;
}
