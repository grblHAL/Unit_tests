#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    CHECK(report_settings_details(SettingsFormat_MachineReadable, (setting_id_t)9999, Group_All) == Status_SettingDisabled);
    CHECK(engine_output[0] == '\0');
    return EXIT_SUCCESS;
}
