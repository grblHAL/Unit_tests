#include "clone_host.h"
int main(void)
{
    clone_prepare();
    settings.mode = Mode_Laser;
    CHECK(spindle_select(0));
    spindle_ptrs_t *s = spindle_get(0);
    CHECK(s->cap.direction && clone_selected == 1);
    s->set_state(s, (spindle_state_t){.on = On, .ccw = On}, 5000);
    CHECK(!clone_output.on && clone_output.ccw && clone_pwm == 500);
    CHECK(spindle_select(0) && clone_selected == 1);
    s->set_state(s, (spindle_state_t){0}, 0);
    CHECK(!clone_output.on && !clone_output.ccw);
    CHECK(spindle_select(1));
    s = spindle_get(0);
    CHECK(!s->cap.direction && !s->cap.laser && s->cap.cloned);
    s->set_state(s, (spindle_state_t){.on = On, .ccw = On}, 1000);
    CHECK(clone_output.on && !clone_output.ccw && clone_pwm == 500);
    return 0;
}
