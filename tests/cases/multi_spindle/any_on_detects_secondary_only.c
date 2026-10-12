#include "support/multi_spindle_host.h"
#include "check.h"

int main(void)
{
    prepare_multi_spindle();
    CHECK(spindle_enable(1) == 1);
    CHECK(!spindle_is_on());
    CHECK(spindle_set_state(spindle_get(1), (spindle_state_t){.on = true}, 7000));
    CHECK(spindle_is_on());
    CHECK(!actual_spindle_states[0].on && actual_spindle_states[1].on);
    return EXIT_SUCCESS;
}
