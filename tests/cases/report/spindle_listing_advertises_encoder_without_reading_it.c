#include "support/spindle_listing_report_host.h"
static unsigned encoder_calls;
static spindle_data_t data;
static spindle_data_t *encoder(spindle_data_request_t request)
{
    (void)request; encoder_calls++; return &data;
}
int main(void)
{
    listed_spindle.get_data = encoder;
    prepare_spindle_listing();
    CHECK(report_spindles(true) == Status_OK);
    CHECK(strcmp(engine_output, "[SPINDLE:0|0|1|*E|fixture spindle]" ASCII_EOL) == 0);
    CHECK(encoder_calls == 0);
    return EXIT_SUCCESS;
}
