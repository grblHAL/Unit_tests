#include "support/spindle_listing_report_host.h"

int main(void)
{
    listed_spindle.cap.at_speed = true;
    listed_spindle.cap.direction = true;
    listed_spindle.cap.laser = true;
    listed_spindle.cap.pid = true;
    listed_spindle.cap.pwm_invert = true;
    listed_spindle.cap.pwm_linearization = true;
    listed_spindle.cap.rpm_range_locked = true;
    listed_spindle.cap.variable = true;
    prepare_spindle_listing();
    CHECK(report_spindles(true) == Status_OK);
    fprintf(stderr, "%s", engine_output);
    CHECK(strcmp(engine_output, "[SPINDLE:0|0|1|*SDLPINRV|fixture spindle]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
