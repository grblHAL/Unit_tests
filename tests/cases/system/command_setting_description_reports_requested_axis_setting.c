#include "support/system_metadata_host.h"
int main(void)
{
    prepare_system_metadata();
    CHECK(system_command("$SED=100") == Status_OK);
    CHECK(strstr(metadata_output, "[SETTINGDESCR:100|") != NULL);
    CHECK(strstr(metadata_output, "N/A") == NULL);
    CHECK(strstr(metadata_output, "[SETTINGDESCR:101|") == NULL);
    return EXIT_SUCCESS;
}
