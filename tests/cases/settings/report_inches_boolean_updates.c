#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    CHECK(store_setting(Setting_ReportInches, "1") == Status_OK);
    CHECK(settings.flags.report_inches);
    CHECK(store_setting(Setting_ReportInches, "0") == Status_OK);
    CHECK(!settings.flags.report_inches);
    CHECK(change_callbacks == 2);
    return EXIT_SUCCESS;
}
