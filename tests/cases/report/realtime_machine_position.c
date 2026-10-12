#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    settings.status_report.machine_position = true;
    sys.position[X_AXIS] = 80;
    sys.position[Y_AXIS] = 160;
    sys.position[Z_AXIS] = 240;
    realtime_report();
    CHECK(strcmp(engine_output, "<Check|MPos:1.000,2.000,3.000>" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
