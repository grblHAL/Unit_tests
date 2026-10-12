#include "support/report_host.h"
#include "check.h"
static unsigned encoder_calls;
static spindle_data_t encoder_report = {.index_count = 7, .pulse_count = 1234, .error_count = 2, .angular_position = 1.25f};
static spindle_data_t *read_encoder_report(spindle_data_request_t request)
{
    CHECK(request == (encoder_calls == 0 ? SpindleData_AngularPosition : SpindleData_Counters));
    encoder_calls++;
    return &encoder_report;
}

int main(void)
{
    prepare_report();
    gc_spindle_get(-1)->hal->get_data = read_encoder_report;
    CHECK(report_spindle_data(STATE_IDLE, NULL) == Status_OK);
    CHECK(encoder_calls == 2);
    CHECK(strcmp(engine_output, "[SPINDLEENCODER:7,1234,2,1.250]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
