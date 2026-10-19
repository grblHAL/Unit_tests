#include "support/system_command_host.h"
static unsigned rtc_reads;
static bool unreadable_clock(struct tm *time) { (void)time; rtc_reads++; return false; }
int main(void)
{
    prepare_system_command();
    hal.driver_cap.rtc = true;
    hal.rtc.get_datetime = unreadable_clock;
    CHECK(system_command("$RTC") == Status_InvalidStatement);
    CHECK(rtc_reads == 1 && engine_output[0] == 0);
    return EXIT_SUCCESS;
}
