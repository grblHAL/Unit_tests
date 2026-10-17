#include "support/system_metadata_host.h"
int main(void)
{
    prepare_system_metadata();
    grbl.tool_table.n_tools = 0;
    CHECK(system_command("$HELP COMMANDS") == Status_OK);
    CHECK(strstr(metadata_output, "$RST=# - reset offsets.") != NULL);
    CHECK(strstr(metadata_output, "reset offsets and tool data") == NULL);
    metadata_output[0] = 0;
    grbl.tool_table.n_tools = 6;
    CHECK(system_command("$HELP COMMANDS") == Status_OK);
    CHECK(strstr(metadata_output, "$RST=# - reset offsets and tool data.") != NULL);
    return EXIT_SUCCESS;
}
