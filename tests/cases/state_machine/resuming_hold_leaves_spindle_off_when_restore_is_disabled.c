#include "support/hold_spindle_host.h"
int main(void)
{
    start_spindle_hold(false);
    toggle_held_spindle();
    resume_spindle_hold_to_endpoint();
    CHECK(!hold_spindle_output_state.on);
    CHECK(!gc_spindle_get(0)->state.on);
    CHECK(sys.override.spindle_stop.value == 0);
    return EXIT_SUCCESS;
}
