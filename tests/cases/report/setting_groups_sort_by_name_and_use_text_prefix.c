#include "support/settings_metadata_report_host.h"
#include "check.h"

int main(void)
{
    prepare_metadata_report();
    CHECK(report_setting_group_details(false, "Group: ") == Status_OK);
    char *first = strstr(engine_output, "Group: Alpha fixture" ASCII_EOL);
    char *second = strstr(engine_output, "Group: Zulu fixture" ASCII_EOL);
    CHECK(first != NULL && second != NULL && first < second);
    CHECK(strstr(engine_output, "Group: Duplicate fixture") == NULL);
    CHECK(strstr(engine_output, "Group: Unavailable fixture") == NULL);
    return EXIT_SUCCESS;
}
