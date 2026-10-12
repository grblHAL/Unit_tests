#include "support/spindle_sync_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_spindle_sync_motion(); queue_spindle_sync_line(10,true); sync_motion_feedback.rpm=0;
    state_set(STATE_CYCLE); CHECK(state_get()==STATE_ALARM); CHECK(sys.alarm==Alarm_Spindle);
    CHECK(wake_calls==0); CHECK(axis_pulses[Z_AXIS]==0); CHECK(sync_encoder_resets==0);
    return EXIT_SUCCESS;
}
