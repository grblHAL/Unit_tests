#include "support/numbered_setting_name_host.h"
int main(void)
{
    prepare_numbered_setting_name("Port ? gain", false);
    CHECK(report_settings_details(SettingsFormat_HumanReadable, (setting_id_t)1001, Group_All) == Status_OK);
    CHECK(strstr(engine_output, "$1001: Port 1 gain") != NULL);
    CHECK(strchr(engine_output, '?') == NULL);
    CHECK(name_chunk_calls == 1);
    return EXIT_SUCCESS;
}
