#include "support/system_metadata_host.h"
int main(void)
{
    prepare_system_metadata();
    settings.axis[X_AXIS].steps_per_mm = 123.5f;
    CHECK(system_command("$$") == Status_OK);
    CHECK(strstr(metadata_output, "$100=123.500") != NULL);
    CHECK(strstr(metadata_output, "$398=") == NULL);
    metadata_output[0] = 0;
    CHECK(system_command("$+") == Status_OK);
    CHECK(strstr(metadata_output, "$100=123.500") != NULL);
    CHECK(strstr(metadata_output, "$398=") != NULL);
    return EXIT_SUCCESS;
}
