#include "support/plugin_settings_report_host.h"
#include "check.h"

int main(void)
{
    prepare_plugin_settings_report();
    report_grbl_settings(false, &report_setting_count);
    CHECK(!saw_setting((setting_id_t)1001));
    CHECK(!saw_setting((setting_id_t)1002));
    return EXIT_SUCCESS;
}
