#include "support/settings_report_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_report();
    report_grbl_settings(true, &report_setting_count);
    CHECK(report_setting_count > 20);
    CHECK(saw_setting(Setting_JogSoftLimited));
    return EXIT_SUCCESS;
}
