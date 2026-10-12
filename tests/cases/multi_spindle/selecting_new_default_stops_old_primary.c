#include "support/multi_spindle_host.h"
#include "check.h"

int main(void)
{
    prepare_multi_spindle();
    CHECK(spindle_set_state(spindle_get(0), (spindle_state_t){.on = true}, 5000));
    CHECK(spindle_select(2));
    CHECK(spindle_get_default() == 2);
    CHECK(spindle_get(0)->id == 2);
    CHECK(!actual_spindle_states[0].on && actual_spindle_rpm[0] == 0);
    CHECK(spindle_config_calls[2] == 1);
    return EXIT_SUCCESS;
}
