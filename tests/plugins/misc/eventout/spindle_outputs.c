#include "event_host.h"
int main(void)
{
    load_events();
    bind_event(0, 1);
    bind_event(1, 2);
    bind_event(2, 7);
    spindle_ptrs_t normal = {0}, laser = {.cap = {.laser = On}};
    grbl.on_spindle_programmed(&normal, (spindle_state_t){.on = On}, 500, (spindle_rpm_mode_t)0);
    CHECK(levels[0] && !levels[1] && !levels[2]);
    grbl.on_spindle_programmed(&laser, (spindle_state_t){.on = On}, 500, (spindle_rpm_mode_t)0);
    CHECK(levels[0] && levels[1] && !levels[2]);
    grbl.on_spindle_at_speed(&normal, (spindle_state_t){.on = On});
    CHECK(levels[2]);
    grbl.on_spindle_programmed(&normal, (spindle_state_t){0}, 500, (spindle_rpm_mode_t)0);
    CHECK(!levels[0] && levels[1] && levels[2]);
    grbl.on_spindle_at_speed(&normal, (spindle_state_t){0});
    CHECK(!levels[2]);
    CHECK(spindle_calls == 3 && speed_calls == 2 && writes == 5 && !levels[3]);
    return 0;
}
