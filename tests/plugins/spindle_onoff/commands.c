#include "onoff_host.h"
int main(void)
{
    on_prepare(2);
    on_load();
    CHECK(!on_warnings && spindle_select(0));
    spindle_ptrs_t *s = spindle_get(0);
    CHECK(s && s->type == SpindleType_Basic && s->cap.direction == TEST_DIRECTION);
    unsigned on = (unsigned)on_get(Setting_Spindle_OnPort);
    CHECK(!on_outputs[on]);
    s->set_state(s, (spindle_state_t){.on = On}, 1000);
    CHECK(on_outputs[on] && s->get_state(s).on);
    s->set_state(s, (spindle_state_t){.on = On, .ccw = On}, 1000);
    CHECK(on_outputs[on]);
#if TEST_DIRECTION
    unsigned dir = (unsigned)on_get(Setting_Spindle_DirPort);
    CHECK(dir != on && on_outputs[dir]);
#endif
    s->set_state(s, (spindle_state_t){0}, 0);
    CHECK(!on_outputs[on] && !s->get_state(s).on);
    return 0;
}
