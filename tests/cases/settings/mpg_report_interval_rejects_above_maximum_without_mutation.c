#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    settings.mpg_report_interval = 250;
    CHECK(store_setting(Setting_MPGAutoReportInterval, "1001") == Status_SettingValueOutOfRange);
    CHECK(settings.mpg_report_interval == 250);
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
