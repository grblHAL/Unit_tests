#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    CHECK(report_settings_details(SettingsFormat_MachineReadable, Setting_AxisStepsPerMM, Group_All) == Status_OK);
    CHECK(strncmp(engine_output, "[SETTING:100|", strlen("[SETTING:100|")) == 0);
    CHECK(strstr(engine_output, "|X-axis travel resolution|step/mm|") != NULL);
    CHECK(strstr(engine_output, "]" ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
