#include "support/report_host.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    prepare_report();
    settings.flags.report_inches = true;
    settings.status_report.machine_position = true;
    report_init();
    sys.position[X_AXIS] = 2032;
    realtime_report();
    CHECK(strcmp(engine_output, "<Check|MPos:1.0000,0.0000,0.0000>" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
