#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    CHECK(report_settings_details(SettingsFormat_MachineReadable, (setting_id_t)(Setting_AxisStepsPerMM + 1), Group_All) == Status_OK);
    CHECK(strncmp(engine_output, "[SETTING:101|", strlen("[SETTING:101|")) == 0);
    CHECK(strstr(engine_output, "|Y-axis travel resolution|step/mm|") != NULL);
    return EXIT_SUCCESS;
}
