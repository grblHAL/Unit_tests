#include "support/multi_spindle_host.h"
#include "check.h"

int main(void)
{
    prepare_multi_spindle();
    CHECK(spindle_enable(1) == 1);
    CHECK(spindle_set_state(spindle_get(0), (spindle_state_t){.on = true}, 5000));
    CHECK(spindle_set_state(spindle_get(1), (spindle_state_t){.on = true}, 7000));
    spindle_all_off(true);
    CHECK(!spindle_is_on());
    CHECK(!actual_spindle_states[0].on && !actual_spindle_states[1].on);
    CHECK(actual_spindle_rpm[0] == 0 && actual_spindle_rpm[1] == 0);
    CHECK(spindle_get(0)->param->rpm == 0 && spindle_get(1)->param->rpm == 0);
    return EXIT_SUCCESS;
}
