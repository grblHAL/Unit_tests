#include "support/human_metadata_report_host.h"

int main(void)
{
    prepare_human_metadata();
    human_metadata_setting.min_value = "5";
    report_human_metadata();
    CHECK(strstr(engine_output, "$1001: Fixture, min: 5") != NULL);
    CHECK(strstr(engine_output, "range:") == NULL && strstr(engine_output, "max:") == NULL);
    return EXIT_SUCCESS;
}
