#include "support/system_metadata_host.h"
#include "check.h"

int main(void)
{
    prepare_system_metadata();
    CHECK(system_command("$ES") == Status_OK);
    CHECK(strstr(metadata_output, "[SETTING:0|") != NULL);
    return EXIT_SUCCESS;
}
