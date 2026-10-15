#include "support/system_metadata_host.h"
int main(void)
{
    prepare_system_metadata();
    CHECK(system_command("$+=110") == Status_OK);
    CHECK(strstr(metadata_output, "$110: X-axis maximum rate") != NULL);
    CHECK(strstr(metadata_output, "mm/min") != NULL);
    CHECK(strstr(metadata_output, "$100:") == NULL);
    return EXIT_SUCCESS;
}
