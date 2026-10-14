#include "support/secondary_status_report_host.h"

int main(void)
{
    prepare_secondary_status_report();
    settings.status_report.overrides = true;
    CHECK(spindle_program_block("M4S7000$1") == Status_OK);
    spindle_set_override(spindle_get(1), 125);
    CHECK(spindle_program_block("M5$1") == Status_OK);
    expect_secondary_status("|SP1:0,,,125");
    CHECK(!actual_spindle_states[1].on);
    return EXIT_SUCCESS;
}
