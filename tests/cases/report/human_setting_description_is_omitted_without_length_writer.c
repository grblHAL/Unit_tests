#include "support/description_metadata_host.h"
#include "check.h"

int main(void)
{
    prepare_description_metadata(); hal.stream.write_n = NULL; report_human_metadata();
    CHECK(strstr(engine_output, "$1001: Fixture") != NULL);
    CHECK(strstr(engine_output, "First") == NULL);
    return EXIT_SUCCESS;
}
