#include "support/secondary_status_report_host.h"

int main(void)
{
    prepare_secondary_status_report();
    CHECK(spindle_program_block("M3S5000") == Status_OK);
    CHECK(spindle_program_block("M4S7000$1") == Status_OK);
    CHECK(spindle_program_block("M5$1") == Status_OK);
    CHECK(actual_spindle_states[0].on && !actual_spindle_states[1].on);
    expect_secondary_status("|SP1:0,,");
    CHECK(actual_spindle_states[0].on);
    return EXIT_SUCCESS;
}
