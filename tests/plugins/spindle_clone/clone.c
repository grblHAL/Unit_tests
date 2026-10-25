#include "clone_host.h"
int main(void)
{
    clone_prepare();
    CHECK(clone_settings);
    clone_float(Setting_RpmMax1, 2000);
    CHECK(spindle_select(0) && spindle_select(1));
    spindle_ptrs_t *s = spindle_get(0);
    CHECK(s->id == 1 && s->cap.cloned && !s->cap.direction);
    NEAR(s->rpm_max, 2000);
    s->set_state(s, (spindle_state_t){.on = On, .ccw = On}, 1000);
    CHECK(clone_output.on && !clone_output.ccw && clone_pwm == 500);
    CHECK(s->get_state(s).on && s->get_state(s).ccw);
    s->set_state(s, (spindle_state_t){0}, 0);
    CHECK(!clone_output.on && !clone_output.ccw && clone_pwm == 0);
    return 0;
}
