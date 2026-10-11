#include "support/system_metadata_host.h"
#include "check.h"

int main(void)
{
    prepare_system_metadata();
    CHECK(system_command("$ESH") == Status_OK);
    CHECK(strstr(metadata_output, "Step pulse") != NULL);
    return EXIT_SUCCESS;
}
