#include "support/secondary_spindle_host.h"

int main(void)
{
    prepare_spindle_motor();
    CHECK(st2_motor_bind_spindle(A_AXIS, &settings.axis[A_AXIS]));
    CHECK(strcmp(grbl.on_setting_get_description(Setting_AxisStepsPerMM + A_AXIS), "Stepper resolution in steps per revolution.") == 0);
    CHECK(strcmp(grbl.on_setting_get_description(Setting_AxisMaxRate + A_AXIS), "Max RPM for stepper spindle.") == 0);
    CHECK(strcmp(grbl.on_setting_get_description(Setting_AxisAcceleration + A_AXIS), "Acceleration in revolutions/sec^2.") == 0);
    CHECK(strcmp(grbl.on_setting_get_description(Setting_AxisMaxTravel + A_AXIS), "This setting is ignored for stepper spindles.") == 0);
    CHECK(strcmp(grbl.on_setting_get_description(Setting_AxisStepsPerMM + X_AXIS), "original description") == 0);
    CHECK(strcmp(grbl.on_setting_get_description((setting_id_t)(Setting_AxisStepperCurrent + A_AXIS)), "original description") == 0);
    return EXIT_SUCCESS;
}
