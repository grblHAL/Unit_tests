#include "support/settings_metadata_report_host.h"
int main(void)
{
    prepare_metadata_report();
    char topic[] = "alph";
    CHECK(report_help(topic) == Status_OK);
    CHECK(strstr(engine_output, "---- Alpha fixture:") != NULL);
    CHECK(strstr(engine_output, "Other group") != NULL);
    CHECK(strstr(engine_output, "Visible first") == NULL);
    return EXIT_SUCCESS;
}
