#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    sys.flags.mpg_auto_reporting = true;
    CHECK(store_setting(Setting_MPGAutoReportInterval, "250") == Status_OK);
    CHECK(settings.mpg_report_interval == 250 && sys.flags.mpg_auto_reporting);
    CHECK(change_callbacks == 1);
    const setting_detail_t *detail = setting_get_details(Setting_MPGAutoReportInterval, NULL);
    CHECK(detail != NULL && setting_get_int_value(detail, 0) == 250);
    return EXIT_SUCCESS;
}
