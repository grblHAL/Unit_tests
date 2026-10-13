#include "support/spindle_listing_report_host.h"
static unsigned pulse_calls;
static void pulse(spindle_ptrs_t *spindle, uint_fast16_t duration)
{
    (void)spindle; (void)duration; pulse_calls++;
}
int main(void)
{
    listed_spindle.cap.laser = true;
    listed_spindle.pulse_on = pulse;
    prepare_spindle_listing();
    CHECK(report_spindles(true) == Status_OK);
    CHECK(strcmp(engine_output, "[SPINDLE:0|0|1|*LA|fixture spindle]" ASCII_EOL) == 0);
    CHECK(pulse_calls == 0);
    return EXIT_SUCCESS;
}
