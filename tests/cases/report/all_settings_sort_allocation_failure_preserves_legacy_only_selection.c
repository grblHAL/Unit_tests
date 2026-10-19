#include "support/plugin_settings_report_host.h"
#include "support/calloc_failure_host.h"
int main(void)
{
    prepare_plugin_settings_report();
    report_grbl_settings(false, &report_setting_count);
    CHECK(report_setting_count > 0 && !saw_setting((setting_id_t)1001));
    report_setting_count = 0;
    fail_calloc = true;
    report_grbl_settings(false, &report_setting_count);
    fail_calloc = false;
    CHECK(failed_calloc_calls == 1 && report_setting_count > 0);
    fprintf(stderr, "Legacy fallback reports extended plugin setting=%u\n", saw_setting((setting_id_t)1001));
    CHECK(!saw_setting((setting_id_t)1001) && !saw_setting((setting_id_t)1002));
    return EXIT_SUCCESS;
}
