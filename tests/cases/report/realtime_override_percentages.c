#include "support/report_host.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    prepare_report();
    settings.status_report.overrides = true;
    sys.override.feed_rate = 150;
    sys.override.rapid_rate = 50;
    realtime_report();
    CHECK(strcmp(engine_output, "<Check|WPos:0.000,0.000,0.000|Ov:150,50,100>" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
