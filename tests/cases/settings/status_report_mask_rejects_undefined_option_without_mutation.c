#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    settings.status_report.mask = 3;
    CHECK(store_setting(Setting_StatusReportMask, "32768") == Status_SettingValueOutOfRange);
    CHECK(settings.status_report.mask == 3);
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
