#include "support/human_metadata_report_host.h"
#include "check.h"

int main(void)
{
    prepare_human_metadata();
    human_metadata_setting.datatype = Format_XBitfield;
    human_metadata_setting.format = "Enable,Reverse";
    report_human_metadata();
    CHECK(strstr(engine_output, "as bitfield where setting bit 0 enables the rest:") != NULL);
    CHECK(strstr(engine_output, "    0 - Enable (1)") != NULL);
    CHECK(strstr(engine_output, "    1 - Reverse (2)") != NULL);
    return EXIT_SUCCESS;
}
