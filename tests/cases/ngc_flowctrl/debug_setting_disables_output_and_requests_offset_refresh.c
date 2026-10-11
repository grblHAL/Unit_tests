#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    settings.flags.ngc_debug_out = true;
    settings.status_report.sync_on_wco_change = false;
    hal.stream.report.flags.value = 0;
    CHECK(store_setting(Setting_NGCDebugOut, "0") == Status_OK);
    CHECK(!settings.flags.ngc_debug_out);
    CHECK(hal.stream.report.flags.value & Report_WCO);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
