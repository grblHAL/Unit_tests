#include "support/system_metadata_host.h"
int main(void)
{
    prepare_system_metadata();
    hal.driver_cap.rtc = false;
    CHECK(system_command("$HELP COMMANDS") == Status_OK);
    CHECK(strstr(metadata_output, "$RTC - output current time") == NULL);
    metadata_output[0] = 0;
    hal.driver_cap.rtc = true;
    CHECK(system_command("$HELP COMMANDS") == Status_OK);
    CHECK(strstr(metadata_output, "$RTC - output current time") != NULL);
    CHECK(strstr(metadata_output, "$RTC=<ISO8601 datetime> - set current time") != NULL);
    return EXIT_SUCCESS;
}
