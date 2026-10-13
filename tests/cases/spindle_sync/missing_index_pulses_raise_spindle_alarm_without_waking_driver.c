#include "support/spindle_sync_motion_host.h"
#include "check.h"
static uint32_t alarm_tick;
static alarm_message_ptr original_alarm;
static alarm_code_t capture_sync_alarm(alarm_code_t alarm)
{
    CHECK(alarm == Alarm_Spindle);
    alarm_tick = engine_ticks;
    return original_alarm(alarm);
}
static void missing_sync_index(sys_state_t state) { (void)state; engine_ticks++; }
int main(void)
{
    prepare_spindle_sync_motion(); queue_spindle_sync_line(10,false); grbl.on_execute_realtime=missing_sync_index;
    original_alarm = grbl.report.alarm_message; grbl.report.alarm_message = capture_sync_alarm;
    state_set(STATE_CYCLE); CHECK(state_get()==STATE_ALARM); CHECK(sys.alarm==Alarm_Spindle);
    CHECK(alarm_tick==5001); CHECK(wake_calls==0); CHECK(axis_pulses[Z_AXIS]==0);
    return EXIT_SUCCESS;
}
