#include "support/spindle_listing_report_host.h"

int main(void)
{
    listed_spindle.cap.rpm_range_locked = true;
    listed_spindle.rpm_min = 250.0f;
    listed_spindle.rpm_max = 24000.0f;
    prepare_spindle_listing();
    CHECK(report_spindles(true) == Status_OK);
    fprintf(stderr, "%s", engine_output);
    CHECK(strcmp(engine_output, "[SPINDLE:0|0|1|*R|fixture spindle|250.0,24000.0]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
