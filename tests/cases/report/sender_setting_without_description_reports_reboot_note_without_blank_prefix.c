#include "support/human_metadata_report_host.h"
int main(void)
{
    prepare_human_metadata();
    human_metadata_setting.flags.reboot_required = true;
    char command[] = "$SED=1001";
    CHECK(system_execute_line(command, hal.stream.write) == Status_OK);
    CHECK(strncmp(engine_output, "[SETTINGDESCR:1001|NOTE: ",
                  strlen("[SETTINGDESCR:1001|NOTE: ")) == 0);
    CHECK(strstr(engine_output, "\\n") == NULL);
    CHECK(strstr(engine_output, "after changing this setting.]" ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
