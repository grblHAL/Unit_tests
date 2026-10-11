#include "support/system_metadata_host.h"
#include "check.h"

int main(void)
{
    prepare_system_metadata();
    CHECK(system_command("$HELP missingfixturetopic") == Status_OK);
    CHECK(strcmp(metadata_output, ASCII_EOL "N/A" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
