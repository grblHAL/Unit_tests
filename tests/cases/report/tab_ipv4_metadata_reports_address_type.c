#include "support/human_metadata_report_host.h"

int main(void)
{
    prepare_human_metadata();
    char value[] = "192.168.1.10";
    human_metadata_setting.datatype = Format_IPv4;
    human_metadata_setting.value = value;
    CHECK(report_settings_details(SettingsFormat_grblHAL, (setting_id_t)1001, Group_All) == Status_OK);
    CHECK(strstr(engine_output, "\tipv4\t") != NULL);
    return EXIT_SUCCESS;
}
