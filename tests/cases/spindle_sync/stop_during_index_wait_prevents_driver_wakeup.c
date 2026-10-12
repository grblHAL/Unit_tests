#include "support/spindle_sync_motion_host.h"
#include "check.h"
static void abort_sync_index(sys_state_t state) { (void)state; system_set_exec_state_flag(EXEC_STOP); }
int main(void)
{
    prepare_spindle_sync_motion(); queue_spindle_sync_line(10,false); grbl.on_execute_realtime=abort_sync_index;
    state_set(STATE_CYCLE); CHECK(sys.rt_exec_state & EXEC_RESET); CHECK(wake_calls==0);
    CHECK(axis_pulses[Z_AXIS]==0); CHECK(sync_encoder_resets==1);
    return EXIT_SUCCESS;
}
