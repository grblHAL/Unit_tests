#include "support/system_metadata_host.h"
#include "check.h"

int main(void)
{
    prepare_system_metadata();
    CHECK(system_command("$E*") == Status_OK);
    CHECK(strstr(metadata_output, "[ERRORCODE:1|") != NULL);
    return EXIT_SUCCESS;
}
