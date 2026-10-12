#include "support/multi_spindle_host.h"
#include "check.h"

int main(void)
{
    prepare_multi_spindle();
    sys.abort = true;
    CHECK(!spindle_set_state(spindle_get(0), (spindle_state_t){.on = true}, 5000));
    CHECK(spindle_output_calls[0] == 0);
    CHECK(!actual_spindle_states[0].on);
    return EXIT_SUCCESS;
}
