#include "support/report_host.h"
#include "check.h"
static bool failing_clock(struct tm *time) { (void)time; return false; }

int main(void)
{
    prepare_report();
    hal.rtc.get_datetime = failing_clock;
    CHECK(report_time() == Status_InvalidStatement);
    CHECK(engine_output[0] == '\0');
    return EXIT_SUCCESS;
}
