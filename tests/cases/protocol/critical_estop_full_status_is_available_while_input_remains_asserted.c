#include "support/critical_alarm_host.h"
int main(void)
{
    lock_alarm = Alarm_EStop;
    lock_controls.e_stop = true;
    lock_release_after_callbacks = 3;
    lock_require_status_report = true;
    const char request[] = {CMD_STATUS_REPORT_ALL, 0};
    run_critical_alarm_input(request, 0);
    CHECK(lock_status_report_seen_while_asserted);
    CHECK(lock_reset_requested_while_input_asserted);
    CHECK(strstr(engine_output, "<Alarm") != NULL);
    CHECK(!(sys.rt_exec_state & EXEC_STATUS_REPORT));
    CHECK(realtime_calls >= 3 && !lock_controls.e_stop);
    CHECK(axis_pulses[X_AXIS] == 0 && axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
