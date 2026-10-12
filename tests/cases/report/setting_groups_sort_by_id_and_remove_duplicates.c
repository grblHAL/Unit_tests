#include "support/settings_metadata_report_host.h"
#include "check.h"

int main(void)
{
    prepare_metadata_report();
    CHECK(report_setting_group_details(true, NULL) == Status_OK);
    char *first = strstr(engine_output, "[SETTINGGROUP:1000|");
    char *second = strstr(engine_output, "[SETTINGGROUP:1001|");
    CHECK(first != NULL && second != NULL && first < second);
    CHECK(strstr(first + 1, "[SETTINGGROUP:1000|") == NULL);
    CHECK(strstr(engine_output, "Duplicate fixture") == NULL);
    CHECK(strstr(engine_output, "Unavailable fixture") == NULL);
    return EXIT_SUCCESS;
}
