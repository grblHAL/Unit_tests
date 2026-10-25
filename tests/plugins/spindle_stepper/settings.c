#include "stepper_host.h"
int main(void)
{
    stepper_prepare();
    spindle_ptrs_t *s = spindle_get(0);
    settings.axis[3].max_rate = 120;
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){.spindle = On});
    NEAR(s->rpm_max, 120);
    CHECK(stepper_previous_settings == 2);
    s->set_state(s, (spindle_state_t){.on = On}, 240);
    stepper_cruise(s);
    NEAR(s->get_data(SpindleData_RPM)->rpm, 120);
    stepper_stop(s);
    return 0;
}
