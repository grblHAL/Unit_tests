#include "support/system_metadata_host.h"
int main(void)
{
    prepare_system_metadata();
    CHECK(system_command("$22=3") == Status_OK);
    CHECK(system_command("$22=0") == Status_OK);
    metadata_output[0] = 0;
    CHECK(system_command("$HELP COMMANDS") == Status_OK);
    CHECK(strstr(metadata_output, "$H - home configured axes.") == NULL);
    CHECK(strstr(metadata_output, "$H<axisletter> - home single axis.") == NULL);
    CHECK(strstr(metadata_output, "$G - output parser state.") != NULL);
    return EXIT_SUCCESS;
}
