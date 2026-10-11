#include "support/human_metadata_report_host.h"
#include "check.h"

int main(void)
{
    prepare_human_metadata();
    human_metadata_setting.datatype = Format_RadioButtons;
    human_metadata_setting.format = "Off,N/A,On";
    report_human_metadata();
    CHECK(strstr(engine_output, "$1001: Fixture:") != NULL);
    CHECK(strstr(engine_output, "    0 - Off") != NULL);
    CHECK(strstr(engine_output, "    2 - On") != NULL);
    CHECK(strstr(engine_output, "N/A") == NULL);
    CHECK(strstr(engine_output, "(1)") == NULL);
    CHECK(strstr(engine_output, "(4)") == NULL);
    return EXIT_SUCCESS;
}
