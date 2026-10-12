#include "support/description_metadata_host.h"
#include "check.h"

int main(void)
{
    prepare_description_metadata(); human_metadata_setting.flags.reboot_required = true;
    report_human_metadata();
    char *description = strstr(engine_output, "Third");
    char *note = strstr(engine_output, "NOTE: A hard reset of the controller is required");
    CHECK(description && note && description < note);
    CHECK(strstr(engine_output, "reboot required") != NULL);
    return EXIT_SUCCESS;
}
