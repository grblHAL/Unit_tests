#include "support/secondary_spindle_host.h"

int main(void)
{
    prepare_spindle_motor();
    settings.stepper_spindle_flags.cfg_as_rotary = true;
    CHECK(st2_motor_bind_spindle(A_AXIS, &settings.axis[A_AXIS]));
    CHECK(grbl.on_set_axis_setting_unit == previous_axis_unit);
    CHECK(grbl.on_setting_get_description == previous_axis_description);
    return EXIT_SUCCESS;
}
