#include "stepper_host.h"
#include <string.h>
int main(void)
{
    stepper_prepare();
    CHECK(grbl.on_set_axis_setting_unit);
    CHECK(!strcmp(grbl.on_set_axis_setting_unit(Setting_AxisStepsPerMM, 3), "step/rev"));
    CHECK(!strcmp(grbl.on_set_axis_setting_unit(Setting_AxisMaxRate, 3), "rev/min"));
    CHECK(!strcmp(grbl.on_set_axis_setting_unit(Setting_AxisAcceleration, 3), "rev/sec^2"));
    CHECK(!strcmp(grbl.on_set_axis_setting_unit(Setting_AxisMaxTravel, 3), "--"));
    CHECK(!strcmp(grbl.on_set_axis_setting_unit(Setting_AxisBacklash, 3), "--"));
    CHECK(!strcmp(grbl.on_set_axis_setting_unit(Setting_AxisStepsPerMM, 0), "driver unit"));
    CHECK(!strcmp(grbl.on_set_axis_setting_unit(Setting_StepperSpindle_Options, 3), "driver unit"));
    settings.stepper_spindle_flags.cfg_as_rotary = On;
    stepper_save();
    CHECK(!strcmp(grbl.on_set_axis_setting_unit(Setting_AxisStepsPerMM, 3), "driver unit"));
    return 0;
}
