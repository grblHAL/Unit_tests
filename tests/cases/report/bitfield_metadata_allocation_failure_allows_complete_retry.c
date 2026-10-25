#include "support/human_metadata_report_host.h"
#include "support/malloc_failure_host.h"

int main(void)
{
    prepare_human_metadata();
    human_metadata_setting.datatype = Format_Bitfield;
    human_metadata_setting.format = "Enable,Reverse";
    human_metadata_setting.flags.reboot_required = true;
    fail_malloc = true;
    report_human_metadata();
    fail_malloc = false;
    CHECK(failed_malloc_calls == 1);
    CHECK(strstr(engine_output, "$1001: Fixture") != NULL);
    CHECK(strstr(engine_output, "Reboot required.") != NULL);
    CHECK(strstr(engine_output, "    0 - Enable") == NULL);
    CHECK(human_metadata_value == 0);
    engine_output[0] = 0;
    report_human_metadata();
    CHECK(strstr(engine_output, "    0 - Enable (1)") != NULL);
    CHECK(strstr(engine_output, "    1 - Reverse (2)") != NULL);
    CHECK(strstr(engine_output, "Reboot required.") != NULL);
    CHECK(failed_malloc_calls == 1 && human_metadata_value == 0);
    return EXIT_SUCCESS;
}
