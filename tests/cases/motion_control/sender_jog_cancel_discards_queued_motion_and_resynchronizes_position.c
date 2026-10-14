#include "support/jog_cancel_stream_host.h"

int main(void)
{
    run_cancelled_jog(false);
    CHECK(axis_pulses[X_AXIS] == jog_stop_pulses);
    CHECK(sys.position[X_AXIS] == physical_position[X_AXIS]);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
