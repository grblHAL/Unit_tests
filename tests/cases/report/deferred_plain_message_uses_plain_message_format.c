#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    char message[] = "Ready";
    report_plain(message);
    CHECK(strcmp(engine_output, "[MSG:Ready]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
