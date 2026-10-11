#include "support/settings_metadata_report_host.h"
#include "support/calloc_failure_host.h"
#include "check.h"

int main(void)
{
    prepare_metadata_report();
    fail_calloc = true;
    CHECK(report_settings_details(SettingsFormat_MachineReadable, Setting_SettingsAll, (setting_group_t)1000) == Status_OK);
    fail_calloc = false;
    CHECK(failed_calloc_calls == 1);
    CHECK(strstr(engine_output, "[SETTING:1001|") != NULL);
    CHECK(strstr(engine_output, "[SETTING:1002|") != NULL);
    CHECK(strstr(engine_output, "Hidden setting") == NULL);
    CHECK(strstr(engine_output, "Unavailable in group") == NULL);
    CHECK(strstr(engine_output, "Other group") == NULL);
    return EXIT_SUCCESS;
}
