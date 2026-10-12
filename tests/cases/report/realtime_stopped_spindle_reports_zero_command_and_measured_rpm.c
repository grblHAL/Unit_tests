#include "support/laser_program_host.h"
#include "check.h"
static spindle_data_t measured_feedback = {.rpm = 612.6f};
static unsigned measured_reads;
static spindle_data_t *read_measured_feedback(spindle_data_request_t request)
{ CHECK(request == SpindleData_RPM); measured_reads++; return &measured_feedback; }
int main(void)
{
    prepare_pwm_program_mode(Mode_Standard, false);
    spindle_get(0)->get_data = read_measured_feedback;
    settings.status_report.feed_speed = true; engine_output[0] = 0;
    status_report_tracking_t tracking = {0};
    report_realtime_status(hal.stream.write, &tracking);
    CHECK(strstr(engine_output, "|FS:0,0,613") != NULL); CHECK(measured_reads == 1);
    return EXIT_SUCCESS;
}
