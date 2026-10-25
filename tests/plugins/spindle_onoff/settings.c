#include "onoff_host.h"
int main(void)
{
    on_prepare(3);
    CHECK(on_settings);
    on_settings->restore();
    CHECK(on_set(Setting_Spindle_OnPort, 0.5f) == Status_BadNumberFormat);
    CHECK(on_set(Setting_Spindle_OnPort, 3) == Status_AuxiliaryPortUnavailable);
    CHECK(on_set(Setting_Spindle_OnPort, 0) == Status_OK);
#if TEST_DIRECTION
    CHECK(on_set(Setting_Spindle_DirPort, 1) == Status_OK);
#endif
    on_settings->save();
    on_load();
    CHECK(!on_warnings && spindle_select(0));
    spindle_ptrs_t *s = spindle_get(0);
    s->set_state(s, (spindle_state_t){.on = On, .ccw = On}, 0);
    CHECK(on_outputs[0]);
#if TEST_DIRECTION
    CHECK(on_outputs[1]);
#endif
    return 0;
}
