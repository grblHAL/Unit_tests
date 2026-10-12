#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    CHECK(report_settings_details(SettingsFormat_Grbl, Setting_AxisStepsPerMM, Group_All) == Status_OK);
    CHECK(strncmp(engine_output, "\"100\",\"X-axis travel resolution\",\"step/mm\",", strlen("\"100\",\"X-axis travel resolution\",\"step/mm\",")) == 0);
    return EXIT_SUCCESS;
}
