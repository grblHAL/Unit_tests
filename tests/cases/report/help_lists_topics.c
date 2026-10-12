#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    char topic[] = "";
    CHECK(report_help(topic) == Status_OK);
    CHECK(strncmp(engine_output, "Help topics:" ASCII_EOL, strlen("Help topics:" ASCII_EOL)) == 0);
    CHECK(strstr(engine_output, " Commands" ASCII_EOL) != NULL);
    CHECK(strstr(engine_output, " Settings" ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
