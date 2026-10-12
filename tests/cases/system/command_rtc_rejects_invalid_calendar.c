#include "support/system_command_host.h"
#include "check.h"
static unsigned calls;
static bool capture_datetime(struct tm *value) { (void)value; calls++; return true; }
int main(void)
{
    prepare_system_command();
    hal.driver_cap.rtc = true;
    hal.rtc.set_datetime = capture_datetime;
    CHECK(system_command("$RTC=2026-02-30T12:34:56") == Status_BadNumberFormat);
    CHECK(calls == 0);
    return EXIT_SUCCESS;
}
