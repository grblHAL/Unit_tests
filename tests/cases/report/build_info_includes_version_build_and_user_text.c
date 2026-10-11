#include "support/build_report_host.h"
#include "check.h"

int main(void)
{
    prepare_build_report();
    build_report(false);
    char expected[100];
    snprintf(expected, sizeof(expected), "[VER:%s.%u:fixture]" ASCII_EOL, GRBL_VERSION, (unsigned)GRBL_BUILD);
    CHECK(strncmp(engine_output, expected, strlen(expected)) == 0);
    CHECK(strstr(engine_output, "[FIRMWARE:grblHAL]" ASCII_EOL) != NULL);
    CHECK(strstr(engine_output, "[AXS:3:XYZ]" ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
