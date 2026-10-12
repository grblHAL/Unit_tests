#include "support/engine_host.h"
#include "report.h"
#include <string.h>
#include "check.h"
static bool connected(void) { return true; }
int main(void)
{
    engine_prepare();
    hal.stream.is_connected = connected;
    report_init_fns();
    report_init();
    CHECK(grbl.report.alarm_message(Alarm_HardLimit) == Alarm_HardLimit);
    CHECK(strcmp(engine_output, "ALARM:1" ASCII_EOL) == 0);
    CHECK(engine_ticks == 100);
    return EXIT_SUCCESS;
}
