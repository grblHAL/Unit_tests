#include "support/human_metadata_report_host.h"
#include "check.h"

int main(void)
{
    prepare_human_metadata();
    human_metadata_setting.datatype = Format_Bitfield;
    human_metadata_setting.format = "Enable,Reverse";
    human_metadata_setting.flags.reboot_required = true;
    report_human_metadata();
    char *option = strstr(engine_output, "    1 - Reverse (2)");
    char *notice = strstr(engine_output, ASCII_EOL ASCII_EOL "Reboot required.");
    CHECK(option != NULL && notice != NULL && option < notice);
    return EXIT_SUCCESS;
}
