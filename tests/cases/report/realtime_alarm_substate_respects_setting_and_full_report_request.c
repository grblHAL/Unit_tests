#include "support/report_host.h"
#include "state_machine.h"

int main(void)
{
    prepare_report();
    sys.alarm = Alarm_HardLimit;
    state_set(STATE_ALARM);
    realtime_report();
    CHECK(strncmp(engine_output, "<Alarm|", 7) == 0);
    engine_output[0] = '\0';
    settings.status_report.alarm_substate = true;
    realtime_report();
    CHECK(strncmp(engine_output, "<Alarm:1|", 9) == 0);
    engine_output[0] = '\0';
    settings.status_report.alarm_substate = false;
    status_report_tracking_t tracking = {.flags = {.all = true}};
    report_realtime_status(hal.stream.write, &tracking);
    CHECK(strncmp(engine_output, "<Alarm:1|", 9) == 0);
    return EXIT_SUCCESS;
}
