#include "support/numbered_setting_name_host.h"
int main(void)
{
    prepare_numbered_setting_name("? port gain", true);
    CHECK(report_settings_details(SettingsFormat_HumanReadable, (setting_id_t)1003, Group_All) == Status_OK);
    CHECK(strstr(engine_output, "$1003: 2 port gain") != NULL);
    CHECK(strchr(engine_output, '?') == NULL);
    CHECK(name_chunk_calls == 0);
    return EXIT_SUCCESS;
}
