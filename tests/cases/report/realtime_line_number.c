#include "support/report_host.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    prepare_report();
    settings.status_report.line_numbers = true;
    gc_state.line_number = 42;
    realtime_report();
    CHECK(strcmp(engine_output, "<Check|WPos:0.000,0.000,0.000|Ln:42>" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
