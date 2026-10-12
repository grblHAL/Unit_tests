#include "support/spindle_sync_motion_host.h"
#include "check.h"
static void missing_sync_index(sys_state_t state) { (void)state; engine_ticks++; }
int main(void)
{
    prepare_spindle_sync_motion(); queue_spindle_sync_line(10,false); grbl.on_execute_realtime=missing_sync_index;
    state_set(STATE_CYCLE); CHECK(state_get()==STATE_ALARM); CHECK(sys.alarm==Alarm_Spindle);
    CHECK(engine_ticks==5001); CHECK(wake_calls==0); CHECK(axis_pulses[Z_AXIS]==0);
    return EXIT_SUCCESS;
}
