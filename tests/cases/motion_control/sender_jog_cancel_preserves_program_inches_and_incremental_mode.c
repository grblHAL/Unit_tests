#include "support/jog_cancel_stream_host.h"

int main(void)
{
    jog_program_inches_incremental = true;
    run_cancelled_jog(false);
    CHECK(gc_state.modal.units_imperial);
    CHECK(gc_state.modal.distance_incremental);
    CHECK(axis_pulses[X_AXIS] == jog_stop_pulses);
    return EXIT_SUCCESS;
}
