#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    settings.status_report.mask = 16383;
    CHECK(store_setting(Setting_StatusReportMask, "0") == Status_OK);
    CHECK(settings.status_report.mask == 0);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
