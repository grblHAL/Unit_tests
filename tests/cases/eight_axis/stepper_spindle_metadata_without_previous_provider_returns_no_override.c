#include "support/secondary_spindle_host.h"

int main(void)
{
    prepare_spindle_motor();
    grbl.on_set_axis_setting_unit = NULL;
    grbl.on_setting_get_description = NULL;
    CHECK(st2_motor_bind_spindle(A_AXIS, &settings.axis[A_AXIS]));
    CHECK(strcmp(grbl.on_set_axis_setting_unit(Setting_AxisStepsPerMM, A_AXIS), "step/rev") == 0);
    CHECK(grbl.on_set_axis_setting_unit(Setting_AxisStepperCurrent, A_AXIS) == NULL);
    CHECK(grbl.on_set_axis_setting_unit(Setting_AxisStepsPerMM, X_AXIS) == NULL);
    CHECK(strcmp(grbl.on_setting_get_description(Setting_AxisStepsPerMM + A_AXIS),
                 "Stepper resolution in steps per revolution.") == 0);
    CHECK(grbl.on_setting_get_description(Setting_AxisStepperCurrent + A_AXIS) == NULL);
    CHECK(grbl.on_setting_get_description(Setting_AxisStepsPerMM + X_AXIS) == NULL);
    return EXIT_SUCCESS;
}
