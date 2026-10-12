#include "support/multi_spindle_host.h"
#include "check.h"

int main(void)
{
    prepare_multi_spindle();
    CHECK(spindle_enable(1) == 1);
    CHECK(spindle_set_state(spindle_get(0), (spindle_state_t){.on = true}, 5000));
    CHECK(spindle_set_state(spindle_get(1), (spindle_state_t){.on = true, .ccw = true}, 7000));
    CHECK(actual_spindle_states[0].on && !actual_spindle_states[0].ccw);
    CHECK(actual_spindle_states[1].on && actual_spindle_states[1].ccw);
    NEAR(actual_spindle_rpm[0], 5000);
    NEAR(actual_spindle_rpm[1], 7000);
    CHECK(spindle_get(0)->param != spindle_get(1)->param);
    NEAR(spindle_get(0)->param->rpm, 5000);
    NEAR(spindle_get(1)->param->rpm, 7000);
    return EXIT_SUCCESS;
}
