#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    settings.report_interval = 250;
    sys.flags.auto_reporting = true;
    CHECK(store_setting(Setting_AutoReportInterval, "0") == Status_OK);
    CHECK(settings.report_interval == 0 && !sys.flags.auto_reporting);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
