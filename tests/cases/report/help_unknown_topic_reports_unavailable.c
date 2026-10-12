#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    char topic[] = "doesnotexist";
    CHECK(report_help(topic) == Status_OK);
    CHECK(strcmp(topic, "DOESNOTEXIST") == 0);
    CHECK(strcmp(engine_output, ASCII_EOL "N/A" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
