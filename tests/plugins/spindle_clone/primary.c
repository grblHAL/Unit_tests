#include "clone_host.h"
int main(void)
{
    clone_prepare();
    CHECK(clone_settings && spindle_select(0));
    spindle_ptrs_t *s = spindle_get(0);
    CHECK(!s->cap.direction);
    s->set_state(s, (spindle_state_t){.on = On}, 5000);
    CHECK(!clone_output.on && clone_output.ccw && clone_pwm == 500);
    CHECK(s->get_state(s).on && !s->get_state(s).ccw);
    s->set_state(s, (spindle_state_t){0}, 0);
    CHECK(!clone_output.on && !clone_output.ccw && clone_pwm == 0);
    return 0;
}
