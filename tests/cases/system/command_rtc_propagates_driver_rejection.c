#include "support/system_command_host.h"
#include "check.h"
static unsigned calls;
static bool reject_datetime(struct tm *value) { (void)value; calls++; return false; }
int main(void)
{
    prepare_system_command();
    hal.driver_cap.rtc = true;
    hal.rtc.set_datetime = reject_datetime;
    CHECK(system_command("$RTC=2026-10-09T12:34:56") == Status_InvalidStatement);
    CHECK(calls == 1);
    return EXIT_SUCCESS;
}
