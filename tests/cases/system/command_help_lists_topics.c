#include "support/system_metadata_host.h"
#include "check.h"

int main(void)
{
    prepare_system_metadata();
    CHECK(system_command("$HELP") == Status_OK);
    CHECK(strstr(metadata_output, "Help topics:") != NULL);
    return EXIT_SUCCESS;
}
