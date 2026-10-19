#include "support/system_metadata_host.h"
int main(void)
{
    prepare_system_metadata();
    CHECK(system_command("$22=1") == Status_OK);
    CHECK(system_command("$HELP COMMANDS") == Status_OK);
    CHECK(strstr(metadata_output, "$H - home configured axes.") != NULL);
    CHECK(strstr(metadata_output, "$H<axisletter> - home single axis.") == NULL);
    metadata_output[0] = 0;
    CHECK(system_command("$22=3") == Status_OK);
    CHECK(system_command("$HELP COMMANDS") == Status_OK);
    CHECK(strstr(metadata_output, "$H - home configured axes.") != NULL);
    CHECK(strstr(metadata_output, "$H<axisletter> - home single axis.") != NULL);
    return EXIT_SUCCESS;
}
