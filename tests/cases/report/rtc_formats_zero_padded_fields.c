#include "support/report_host.h"
#include "check.h"
static bool fixed_clock(struct tm *time)
{
    *time = (struct tm){.tm_year = 126, .tm_mon = 0, .tm_mday = 2, .tm_hour = 3, .tm_min = 4, .tm_sec = 5};
    return true;
}

int main(void)
{
    prepare_report();
    hal.rtc.get_datetime = fixed_clock;
    CHECK(report_time() == Status_OK);
    CHECK(strcmp(engine_output, "[RTC:2026-01-02T03:04:05]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
