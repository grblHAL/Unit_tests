#include "support/multi_spindle_host.h"
#include "check.h"

int main(void)
{
    prepare_multi_spindle_program();
    spindle_ptrs_t *spindle = spindle_get(0);
    CHECK(spindle_set_state(spindle, (spindle_state_t){.on=true,.ccw=true}, 5000));
    CHECK(spindle_check_state(spindle, (spindle_state_t){.on=true,.ccw=true}));
    CHECK(!spindle_check_state(spindle, (spindle_state_t){.on=true,.ccw=false}));
    CHECK(!spindle_check_state(spindle, (spindle_state_t){.on=false,.ccw=true}));
    CHECK(spindle_check_state(spindle, (spindle_state_t){.on=true,.ccw=true,.at_speed=true,.override_disable=true}));
    return EXIT_SUCCESS;
}
