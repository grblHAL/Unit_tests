#include "support/description_metadata_host.h"
int main(void)
{
    prepare_description_metadata();
    human_metadata_setting.flags.reboot_required = true;
    human_metadata_setting.flags.hidden = true;
    char command[] = "$SED=1001";
    CHECK(system_execute_line(command, hal.stream.write) == Status_OK);
    CHECK(engine_output[0] == '\0');
    return EXIT_SUCCESS;
}
