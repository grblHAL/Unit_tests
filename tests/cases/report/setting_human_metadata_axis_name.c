#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    CHECK(report_settings_details(SettingsFormat_HumanReadable, Setting_AxisStepsPerMM, Group_All) == Status_OK);
    CHECK(strstr(engine_output, "$100: X-axis travel resolution") != NULL);
    CHECK(strstr(engine_output, "step/mm") != NULL);
    return EXIT_SUCCESS;
}
