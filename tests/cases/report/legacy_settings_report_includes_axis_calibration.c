#include "support/settings_report_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_report();
    report_grbl_settings(false, &report_setting_count);
    CHECK(report_setting_count > 20);
    CHECK(saw_setting(Setting_PulseMicroseconds));
    CHECK(saw_setting(Setting_AxisStepsPerMM));
    return EXIT_SUCCESS;
}
