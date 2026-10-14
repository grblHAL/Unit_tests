#include "support/secondary_status_report_host.h"

int main(void)
{
    prepare_secondary_status_report();
    settings.status_report.overrides = true;
    CHECK(spindle_program_block("M4S7000$1") == Status_OK);
    spindle_set_override(spindle_get(1), 125);
    NEAR(spindle_get(1)->param->rpm_overridden, 8750);
    expect_secondary_status("|SP1:8750,,C,125");
    CHECK(spindle_get(0)->param->override_pct == 100);
    return EXIT_SUCCESS;
}
