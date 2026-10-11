#include "support/system_metadata_host.h"
#include "check.h"

int main(void)
{
    prepare_system_metadata();
    CHECK(system_command("$EAG") == Status_OK);
    CHECK(strstr(metadata_output, "Alarm Code in v1.1+") != NULL);
    return EXIT_SUCCESS;
}
