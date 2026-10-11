#include "support/human_metadata_report_host.h"
#include "check.h"

int main(void)
{
    prepare_human_metadata();
    human_metadata_setting.unit = "rpm";
    human_metadata_setting.min_value = "100";
    human_metadata_setting.max_value = "12000";
    report_human_metadata();
    CHECK(strstr(engine_output, "$1001: Fixture in rpm, range: 100 - 12000") != NULL);
    return EXIT_SUCCESS;
}
