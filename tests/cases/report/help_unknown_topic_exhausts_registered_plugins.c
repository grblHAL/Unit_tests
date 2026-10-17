#include "support/second_settings_metadata_report_host.h"
int main(void)
{
    prepare_second_metadata_report();
    char topic[] = "missingdevice";
    CHECK(report_help(topic) == Status_OK);
    CHECK(strstr(engine_output, "N/A") != NULL);
    CHECK(strstr(engine_output, "---- ") == NULL);
    CHECK(strstr(engine_output, "Second port limit") == NULL);
    return EXIT_SUCCESS;
}
