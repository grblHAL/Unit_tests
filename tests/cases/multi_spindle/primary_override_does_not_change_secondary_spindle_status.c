#include "support/secondary_status_report_host.h"

int main(void)
{
    prepare_secondary_status_report();
    settings.status_report.overrides = true;
    CHECK(spindle_program_block("M3S5000") == Status_OK);
    CHECK(spindle_program_block("M4S7000$1") == Status_OK);
    unsigned secondary_outputs = spindle_output_calls[1];
    spindle_set_override(spindle_get(0), 150);
    expect_secondary_status("|SP1:7000,,C,100");
    CHECK(spindle_output_calls[1] == secondary_outputs);
    CHECK(spindle_get(0)->param->override_pct == 150);
    return EXIT_SUCCESS;
}
