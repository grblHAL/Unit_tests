#include "support/settings_metadata_report_host.h"
#include "check.h"

int main(void)
{
    prepare_metadata_report();
    CHECK(report_settings_details(SettingsFormat_MachineReadable, Setting_SettingsAll, Group_YAxis) == Status_OK);
    CHECK(strstr(engine_output, "Y-axis travel resolution") != NULL);
    CHECK(strstr(engine_output, "X-axis travel resolution") == NULL);
    CHECK(strstr(engine_output, "Z-axis travel resolution") == NULL);
    CHECK(strstr(engine_output, "[SETTING:101|") != NULL);
    CHECK(strstr(engine_output, "[SETTING:100|") == NULL);
    CHECK(strstr(engine_output, "[SETTING:102|") == NULL);
    return EXIT_SUCCESS;
}
