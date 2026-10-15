#include "support/settings_metadata_report_host.h"
int main(void)
{
    prepare_metadata_report();
    char topic[] = "zulufixture";
    CHECK(report_help(topic) == Status_OK);
    CHECK(strstr(engine_output, "---- Zulu fixture:") != NULL);
    CHECK(strstr(engine_output, "Visible first") != NULL);
    CHECK(strstr(engine_output, "Visible second") != NULL);
    CHECK(strstr(engine_output, "Other group") == NULL);
    CHECK(strstr(engine_output, "Hidden setting") == NULL);
    CHECK(strstr(engine_output, "Unavailable in group") == NULL);
    return EXIT_SUCCESS;
}
