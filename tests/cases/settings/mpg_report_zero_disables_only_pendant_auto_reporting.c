#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    settings.mpg_report_interval = 250;
    settings.report_interval = 500;
    sys.flags.mpg_auto_reporting = true;
    sys.flags.auto_reporting = true;
    CHECK(store_setting(Setting_MPGAutoReportInterval, "0") == Status_OK);
    CHECK(settings.mpg_report_interval == 0 && !sys.flags.mpg_auto_reporting);
    CHECK(settings.report_interval == 500 && sys.flags.auto_reporting);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
