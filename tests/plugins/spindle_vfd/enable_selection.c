#include "enable_host.h"

static spindle_set_state_ptr chained_state;
static unsigned chained_calls;
static void prior_set_state(spindle_ptrs_t *spindle, spindle_state_t state, float rpm)
{
    CHECK(++chained_calls < 10);
    chained_state(spindle, state, rpm);
}
static void prior_selected(spindle_ptrs_t *spindle)
{
    if(spindle->type == SpindleType_VFD) {
        CHECK(spindle->set_state != prior_set_state);
        chained_state = spindle->set_state;
        spindle->set_state = prior_set_state;
    }
}
int main(void)
{
    enable_prepare_ports(false);
    vfd_selection_observer = prior_selected;
    vfd_prepare(true);
    vfd_start();
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On}, 6000);
    CHECK(enable_levels[3] && chained_calls == 1);
    CHECK(spindle_select(0));
    vfd_motor->set_state(vfd_motor, (spindle_state_t){0}, 0);
    CHECK(!enable_levels[3] && chained_calls == 2 && vfd_previous_selected == 1);
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On}, 6000);
    CHECK(enable_levels[3] && chained_calls == 3);
    spindle_id_t idle = spindle_add_null();
    CHECK(idle == 1 && spindle_select(idle));
    CHECK(!enable_levels[3]);
    CHECK(spindle_select(0));
    vfd_motor = spindle_get(0);
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On}, 6000);
    CHECK(enable_levels[3] && chained_calls == 4 && vfd_previous_selected == 3);
    enable_expect_claim(true);
    return 0;
}
