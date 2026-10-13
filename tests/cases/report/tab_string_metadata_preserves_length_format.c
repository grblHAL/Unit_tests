#include "support/human_metadata_report_host.h"

int main(void)
{
    prepare_human_metadata();
    char value[] = "fixture";
    human_metadata_setting.datatype = Format_String;
    human_metadata_setting.value = value;
    human_metadata_setting.format = "48";
    CHECK(report_settings_details(SettingsFormat_grblHAL, (setting_id_t)1001, Group_All) == Status_OK);
    CHECK(strstr(engine_output, "\tstring\t48\t") != NULL);
    return EXIT_SUCCESS;
}
