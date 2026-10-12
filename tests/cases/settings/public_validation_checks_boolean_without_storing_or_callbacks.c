#include "support/settings_validation_host.h"

int main(void)
{
    prepare_settings_store();
    settings.flags.report_inches = false;
    char on[] = "1", invalid[] = "2";
    CHECK(setting_validate(Setting_ReportInches, 1, on) == Status_OK);
    CHECK(setting_validate(Setting_ReportInches, 2, invalid) == Status_SettingValueOutOfRange);
    CHECK(!settings.flags.report_inches && change_callbacks == 0);
    return EXIT_SUCCESS;
}
