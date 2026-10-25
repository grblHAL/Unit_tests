#include "stepper_host.h"
int main(void)
{
    stepper_prepare();
    CHECK(stepper_save);
    settings.stepper_spindle_flags.cfg_as_rotary = On;
    stepper_save();
    CHECK(fabsf(settings.axis[3].steps_per_mm - 200.0f / 360) < 0.0001f);
    NEAR(settings.axis[3].max_rate, 216000);
    settings.stepper_spindle_flags.cfg_as_rotary = Off;
    stepper_save();
    NEAR(settings.axis[3].steps_per_mm, 200);
    NEAR(settings.axis[3].max_rate, 600);
    CHECK(stepper_saves == 2);
    return 0;
}
