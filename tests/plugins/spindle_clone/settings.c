#include "clone_host.h"
int main(void)
{
    clone_prepare();
    CHECK(spindle_select(0));
    clone_float(Setting_RpmMax1, 2000);
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){.spindle = On});
    CHECK(spindle_select(1));
    spindle_ptrs_t *s = spindle_get(0);
    s->set_state(s, (spindle_state_t){.on = On}, 1000);
    CHECK(clone_pwm == 500);
    clone_float(Setting_RpmMax1, 4000);
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){.spindle = On});
    s->set_state(s, (spindle_state_t){.on = On}, 1000);
    CHECK(clone_pwm == 250);
    return 0;
}
