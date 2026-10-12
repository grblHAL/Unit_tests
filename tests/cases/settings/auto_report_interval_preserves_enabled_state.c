#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    sys.flags.auto_reporting = true;
    CHECK(store_setting(Setting_AutoReportInterval, "500") == Status_OK);
    CHECK(settings.report_interval == 500 && sys.flags.auto_reporting);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
