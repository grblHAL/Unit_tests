#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    CHECK(store_setting(Setting_ReportInches, "2") == Status_SettingValueOutOfRange);
    CHECK(!settings.flags.report_inches);
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
