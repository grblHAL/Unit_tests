#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    settings.status_report.mask = 0;
    CHECK(store_setting(Setting_StatusReportMask, "16383") == Status_OK);
    CHECK(settings.status_report.mask == 16383);
    CHECK(change_callbacks == 1);
    const setting_detail_t *detail = setting_get_details(Setting_StatusReportMask, NULL);
    CHECK(detail != NULL && setting_get_int_value(detail, 0) == 16383);
    return EXIT_SUCCESS;
}
