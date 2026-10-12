#include "support/plugin_settings_report_host.h"
#include "check.h"

int main(void)
{
    prepare_plugin_settings_report();
    report_grbl_settings(true, &report_setting_count);
    CHECK(saw_setting((setting_id_t)1001));
    CHECK(saw_setting((setting_id_t)1002));
    unsigned first = 512, second = 512;
    for(unsigned i = 0; i < report_setting_count; i++) {
        if(reported_setting_ids[i] == 1001) first = i;
        if(reported_setting_ids[i] == 1002) second = i;
    }
    CHECK(first < second);
    return EXIT_SUCCESS;
}
