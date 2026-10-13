#include "support/human_metadata_report_host.h"

int main(void)
{
    prepare_human_metadata();
    human_metadata_setting.max_value = "20";
    report_human_metadata();
    CHECK(strstr(engine_output, "$1001: Fixture, max: 20") != NULL);
    CHECK(strstr(engine_output, "range:") == NULL && strstr(engine_output, "min:") == NULL);
    return EXIT_SUCCESS;
}
