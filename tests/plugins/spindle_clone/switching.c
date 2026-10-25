#include "clone_host.h"
int main(void)
{
    clone_prepare();
    CHECK(spindle_select(0));
    spindle_ptrs_t *s = spindle_get(0);
    s->set_state(s, (spindle_state_t){.on = On}, 5000);
    unsigned calls = clone_calls;
    CHECK(spindle_select(1));
    CHECK(clone_calls == calls + 1 && !clone_output.on && !clone_output.ccw);
    s = spindle_get(0);
    s->set_state(s, (spindle_state_t){.on = On}, 500);
    calls = clone_calls;
    CHECK(spindle_select(0));
    CHECK(clone_calls == calls + 1 && !clone_output.on && !clone_output.ccw);
    CHECK(clone_selected == 3);
    return 0;
}
