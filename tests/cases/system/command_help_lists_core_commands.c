#include "support/system_metadata_host.h"
#include "check.h"

int main(void)
{
    prepare_system_metadata();
    CHECK(system_command("$HELP COMMANDS") == Status_OK);
    CHECK(strstr(metadata_output, "$G - output parser state.") != NULL);
    return EXIT_SUCCESS;
}
