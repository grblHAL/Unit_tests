#include "support/secondary_status_report_host.h"

int main(void)
{
    prepare_secondary_status_report();
    CHECK(spindle_program_block("M3S3100$1") == Status_OK);
    CHECK(actual_spindle_states[1].on && !actual_spindle_states[1].ccw);
    NEAR(actual_spindle_rpm[1], 3100);
    expect_secondary_status("|SP1:3100,,S");
    return EXIT_SUCCESS;
}
