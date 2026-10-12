#include "support/settings_metadata_report_host.h"
#include "check.h"

int main(void)
{
    prepare_metadata_report();
    CHECK(report_settings_details(SettingsFormat_Grbl, Setting_SettingsAll, (setting_group_t)1000) == Status_OK);
    CHECK(strncmp(engine_output, "\"$-Code\",\" Setting\",\" Units\",\" Setting Description\"" ASCII_EOL, strlen("\"$-Code\",\" Setting\",\" Units\",\" Setting Description\"" ASCII_EOL)) == 0);
    char *first = strstr(engine_output, "\"1001\",\"Visible first\"");
    char *second = strstr(engine_output, "\"1002\",\"Visible second\"");
    CHECK(first != NULL && second != NULL && first < second);
    return EXIT_SUCCESS;
}
