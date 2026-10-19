#include "support/system_metadata_host.h"
int main(void)
{
    prepare_system_metadata();
    settings.axis[X_AXIS].steps_per_mm = 123.5f;
    settings.axis[Y_AXIS].max_rate = 456.25f;
    CHECK(system_command("$$") == Status_OK);
    CHECK(strstr(metadata_output, "$100=123.500") != NULL);
    CHECK(strstr(metadata_output, "$111=456.250") != NULL);
    metadata_output[0] = 0;
    CHECK(system_command("$+") == Status_OK);
    CHECK(strstr(metadata_output, "$100=123.500") != NULL);
    CHECK(strstr(metadata_output, "$111=456.250") != NULL);
    return EXIT_SUCCESS;
}
