#include "support/settings_metadata_report_host.h"
#include "check.h"

int main(void)
{
    prepare_metadata_report();
    CHECK(report_settings_details(SettingsFormat_MachineReadable, Setting_SettingsAll, (setting_group_t)1000) == Status_OK);
    char *first = strstr(engine_output, "[SETTING:1001|");
    char *second = strstr(engine_output, "[SETTING:1002|");
    CHECK(first != NULL && second != NULL && first < second);
    CHECK(strstr(engine_output, "Visible first") != NULL);
    CHECK(strstr(engine_output, "Visible second") != NULL);
    CHECK(strstr(engine_output, "Hidden setting") == NULL);
    CHECK(strstr(engine_output, "Unavailable setting") == NULL);
    CHECK(strstr(engine_output, "Other group") == NULL);
    return EXIT_SUCCESS;
}
