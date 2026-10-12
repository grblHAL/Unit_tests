#include "support/human_metadata_report_host.h"
#include "check.h"

int main(void)
{
    prepare_human_metadata();
    human_metadata_setting.datatype = Format_Bitfield;
    human_metadata_setting.format = "Enable,N/A,Reverse";
    report_human_metadata();
    CHECK(strstr(engine_output, "$1001: Fixture as bitfield:") != NULL);
    CHECK(strstr(engine_output, "    0 - Enable (1)") != NULL);
    CHECK(strstr(engine_output, "    2 - Reverse (4)") != NULL);
    CHECK(strstr(engine_output, "N/A") == NULL);
    return EXIT_SUCCESS;
}
