#include "support/system_command_host.h"
#include "check.h"
static unsigned calls;
static struct tm captured;
static bool capture_datetime(struct tm *value) { captured = *value; calls++; return true; }
int main(void)
{
    prepare_system_command();
    hal.driver_cap.rtc = true;
    hal.rtc.set_datetime = capture_datetime;
    CHECK(system_command("$RTC=2026-10-09T12:34:56") == Status_OK);
    CHECK(calls == 1);
    CHECK(captured.tm_year == 126 && captured.tm_mon == 9 && captured.tm_mday == 9);
    CHECK(captured.tm_hour == 12 && captured.tm_min == 34 && captured.tm_sec == 56);
    return EXIT_SUCCESS;
}
