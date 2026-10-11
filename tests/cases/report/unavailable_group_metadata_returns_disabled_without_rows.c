#include "support/settings_metadata_report_host.h"
#include "check.h"

int main(void)
{
    prepare_metadata_report();
    CHECK(report_settings_details(SettingsFormat_MachineReadable, Setting_SettingsAll, (setting_group_t)1002) == Status_SettingDisabled);
    CHECK(engine_output[0] == '\0');
    return EXIT_SUCCESS;
}
