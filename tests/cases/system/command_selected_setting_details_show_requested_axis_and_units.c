#include "support/system_metadata_host.h"
int main(void)
{
    prepare_system_metadata();
    CHECK(system_command("$$=100") == Status_OK);
    CHECK(strstr(metadata_output, "$100: X-axis travel resolution") != NULL);
    CHECK(strstr(metadata_output, "step/mm") != NULL);
    CHECK(strstr(metadata_output, "$101:") == NULL);
    CHECK(strstr(metadata_output, "$110:") == NULL);
    return EXIT_SUCCESS;
}
