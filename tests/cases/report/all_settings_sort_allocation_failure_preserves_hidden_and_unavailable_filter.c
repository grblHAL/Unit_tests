#include "support/plugin_settings_report_host.h"
#include "support/calloc_failure_host.h"
int main(void)
{
    prepare_plugin_settings_report();
    report_grbl_settings(true, &report_setting_count);
    CHECK(saw_setting((setting_id_t)1001) && saw_setting((setting_id_t)1002));
    CHECK(!saw_setting((setting_id_t)1003) && !saw_setting((setting_id_t)1004));
    report_setting_count = 0;
    fail_calloc = true;
    report_grbl_settings(true, &report_setting_count);
    fail_calloc = false;
    CHECK(failed_calloc_calls == 1);
    CHECK(saw_setting((setting_id_t)1001) && saw_setting((setting_id_t)1002));
    fprintf(stderr, "Fallback reports hidden=%u unavailable=%u\n", saw_setting((setting_id_t)1003), saw_setting((setting_id_t)1004));
    CHECK(!saw_setting((setting_id_t)1003) && !saw_setting((setting_id_t)1004));
    return EXIT_SUCCESS;
}
