#include "support/system_metadata_host.h"
#include "support/motion_program_host.h"
#include "check.h"

int main(void)
{
    prepare_system_metadata();
    CHECK(system_command("$E*") == Status_OK);
    char *alarms = strstr(metadata_output, "[ALARMCODE:");
    char *errors = strstr(metadata_output, "[ERRORCODE:");
    char *groups = strstr(metadata_output, "[SETTINGGROUP:");
    char *settings_text = strstr(metadata_output, "[SETTING:");
    CHECK(alarms && errors && groups && settings_text);
    CHECK(alarms < errors && errors < groups && groups < settings_text);
    return EXIT_SUCCESS;
}
