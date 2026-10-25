#include "support/system_command_host.h"

static unsigned clock_reads;
static bool read_only_clock(struct tm *time)
{
    clock_reads++;
    *time = (struct tm){.tm_year = 126, .tm_mon = 9, .tm_mday = 24,
        .tm_hour = 12, .tm_min = 34, .tm_sec = 56};
    return true;
}

int main(void)
{
    prepare_system_command();
    hal.driver_cap.rtc = true;
    hal.rtc.get_datetime = read_only_clock;
    CHECK(hal.rtc.set_datetime == NULL);
    CHECK(system_command("$RTC") == Status_OK);
    CHECK(strcmp(engine_output, "[RTC:2026-10-24T12:34:56]" ASCII_EOL) == 0);
    engine_output[0] = '\0';
    status_code_t status = system_command("$RTC=2026-10-25T01:02:03");
    CHECK(engine_output[0] == '\0');
    CHECK(system_command("$RTC") == Status_OK);
    CHECK(clock_reads == 2);
    CHECK(strcmp(engine_output, "[RTC:2026-10-24T12:34:56]" ASCII_EOL) == 0);
    fprintf(stderr, "Read-only RTC write status=%u; unchanged clock remains readable\n", (unsigned)status);
    CHECK(status != Status_OK);
    return EXIT_SUCCESS;
}
