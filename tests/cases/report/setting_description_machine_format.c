#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    CHECK(report_setting_description(SettingsFormat_MachineReadable, Setting_AxisStepsPerMM) == Status_OK);
    CHECK(strncmp(engine_output, "[SETTINGDESCR:100|", strlen("[SETTINGDESCR:100|")) == 0);
    CHECK(strstr(engine_output, "]" ASCII_EOL) != NULL);
    CHECK(strlen(engine_output) > 20);
    return EXIT_SUCCESS;
}
