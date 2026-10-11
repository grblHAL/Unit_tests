#include "support/human_metadata_report_host.h"
#include "check.h"

int main(void)
{
    prepare_human_metadata();
    human_metadata_setting.datatype = Format_Bool;
    report_human_metadata();
    CHECK(strstr(engine_output, "$1001: Fixture as boolean") != NULL);
    return EXIT_SUCCESS;
}
