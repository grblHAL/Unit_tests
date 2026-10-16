#include "support/description_metadata_host.h"
int main(void)
{
    prepare_description_metadata();
    human_metadata_setting.flags.reboot_required = true;
    char command[] = "$SED=1001";
    CHECK(system_execute_line(command, hal.stream.write) == Status_OK);
    CHECK(strncmp(engine_output, "[SETTINGDESCR:1001|First\\nSecond\\nThird",
                  strlen("[SETTINGDESCR:1001|First\\nSecond\\nThird")) == 0);
    CHECK(strstr(engine_output, SETTINGS_HARD_RESET_REQUIRED "]" ASCII_EOL) != NULL);
    CHECK(strchr(engine_output, '\n') == engine_output + strlen(engine_output) - 1);
    return EXIT_SUCCESS;
}
