#include "support/jog_cancel_stream_host.h"

int main(void)
{
    run_cancelled_jog(true);
    CHECK(jog_resume_started);
    CHECK(axis_pulses[X_AXIS] == jog_stop_pulses + 80);
    CHECK(sys.position[X_AXIS] == jog_stop_position + 80);
    CHECK(sys.position[X_AXIS] == physical_position[X_AXIS]);
    NEAR(gc_state.position[X_AXIS], jog_stop_parser_position + 1);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
