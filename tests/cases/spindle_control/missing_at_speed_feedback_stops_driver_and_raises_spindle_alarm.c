#include "support/spindle_ready_host.h"
static uint32_t ready_alarm_tick;
static alarm_message_ptr previous_alarm;
static alarm_code_t capture_ready_alarm(alarm_code_t alarm)
{ CHECK(alarm == Alarm_Spindle); ready_alarm_tick = engine_ticks; return previous_alarm(alarm); }
int main(void)
{
    prepare_spindle_ready(UINT32_MAX, 400);
    previous_alarm = grbl.report.alarm_message; grbl.report.alarm_message = capture_ready_alarm;
    (void)ready_block("M3S6000");
    CHECK(ready_alarm_tick == 600);
    CHECK(ready_notifications == 0 && !ready_hardware.on);
    NEAR(ready_rpm, 0);
    CHECK(sys.alarm == Alarm_Spindle && state_get() == STATE_ALARM);
    return EXIT_SUCCESS;
}
