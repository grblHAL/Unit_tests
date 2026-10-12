#include "support/settings_metadata_report_host.h"
#include "support/calloc_failure_host.h"
#include "check.h"

int main(void)
{
    prepare_metadata_report();
    fail_calloc = true;
    CHECK(report_setting_group_details(true, NULL) == Status_OK);
    fail_calloc = false;
    CHECK(failed_calloc_calls == 1);
    CHECK(strstr(engine_output, "[SETTINGGROUP:1000|") != NULL);
    CHECK(strstr(engine_output, "[SETTINGGROUP:1001|") != NULL);
    CHECK(strstr(engine_output, "Unavailable fixture") == NULL);
    return EXIT_SUCCESS;
}
