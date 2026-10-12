#include "support/description_metadata_host.h"
#include "check.h"

int main(void)
{
    prepare_description_metadata(); report_human_metadata();
    CHECK(strstr(engine_output, "First" ASCII_EOL "Second" ASCII_EOL "Third") != NULL);
    CHECK(strstr(engine_output, "\\n") == NULL);
    return EXIT_SUCCESS;
}
