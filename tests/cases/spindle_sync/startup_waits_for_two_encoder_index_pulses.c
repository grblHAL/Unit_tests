#include "support/spindle_sync_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_spindle_sync_motion(); queue_spindle_sync_line(10,false); state_set(STATE_CYCLE);
    CHECK(state_get()==STATE_CYCLE); CHECK(wake_calls==1); CHECK(sync_encoder_resets==1);
    CHECK(sync_motion_feedback.index_count==2); CHECK(sync_realtime_calls>0); CHECK(engine_ticks<5000);
    CHECK(axis_pulses[Z_AXIS]==0);
    return EXIT_SUCCESS;
}
