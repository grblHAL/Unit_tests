#include "support/critical_alarm_host.h"
int main(void)
{
    lock_require_status_report = true;
    const char request[] = {CMD_STATUS_REPORT, 0};
    run_critical_alarm_input(request, 0);
    CHECK(strstr(engine_output, "<Alarm") != NULL);
    CHECK(strstr(engine_output, "0.000,0.000,0.000") != NULL);
    CHECK(!(sys.rt_exec_state & EXEC_STATUS_REPORT));
    CHECK(axis_pulses[X_AXIS] == 0 && axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
