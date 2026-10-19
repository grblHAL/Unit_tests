#include "support/system_metadata_host.h"
int main(void)
{
    prepare_system_metadata();
    CHECK(system_command("$$=ABC") == Status_BadNumberFormat);
    CHECK(system_command("$+=ABC") == Status_BadNumberFormat);
    CHECK(system_command("$$=999999") == Status_SettingDisabled);
    CHECK(system_command("$+=999999") == Status_SettingDisabled);
    CHECK(metadata_output[0] == 0);
    return EXIT_SUCCESS;
}
