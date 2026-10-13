#include "support/human_metadata_report_host.h"

int main(void)
{
    prepare_human_metadata();
    char value[] = "fixture-password-value";
    human_metadata_setting.datatype = Format_Password;
    human_metadata_setting.value = value;
    human_metadata_setting.format = "32";
    CHECK(report_settings_details(SettingsFormat_grblHAL, (setting_id_t)1001, Group_All) == Status_OK);
    CHECK(strstr(engine_output, "\tpassword\t32\t") != NULL);
    CHECK(strstr(engine_output, value) == NULL);
    return EXIT_SUCCESS;
}
