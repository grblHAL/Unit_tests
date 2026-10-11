#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    report_pid_log();
    CHECK(strcmp(engine_output, "error:20" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
