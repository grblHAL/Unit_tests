#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    settings.status_report.sync_on_wco_change = false;
    hal.stream.report.flags.value = 0;
    CHECK(store_setting(Setting_NGCDebugOut, "1") == Status_OK);
    CHECK(settings.flags.ngc_debug_out);
    CHECK(hal.stream.report.flags.value & Report_WCO);
    CHECK(change_callbacks == 1);
    const setting_detail_t *detail = setting_get_details(Setting_NGCDebugOut, NULL);
    CHECK(detail != NULL && setting_get_int_value(detail, 0) == 1);
    return EXIT_SUCCESS;
}
