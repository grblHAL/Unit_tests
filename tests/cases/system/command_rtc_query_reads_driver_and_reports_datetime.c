#include "support/system_command_host.h"
static unsigned rtc_reads;
static bool query_clock(struct tm *time)
{
    rtc_reads++;
    *time = (struct tm){.tm_year = 126, .tm_mon = 9, .tm_mday = 19,
        .tm_hour = 12, .tm_min = 34, .tm_sec = 56};
    return true;
}
int main(void)
{
    prepare_system_command();
    hal.driver_cap.rtc = true;
    hal.rtc.get_datetime = query_clock;
    CHECK(system_command("$RTC") == Status_OK);
    CHECK(rtc_reads == 1);
    CHECK(strcmp(engine_output, "[RTC:2026-10-19T12:34:56]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
