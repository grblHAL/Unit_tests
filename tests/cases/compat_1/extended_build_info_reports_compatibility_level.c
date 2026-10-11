#include "support/build_report_host.h"
#include "check.h"

int main(void)
{
    prepare_build_report();
    build_report(true);
    CHECK(strstr(engine_output, "[COMPATIBILITY LEVEL:1]" ASCII_EOL) != NULL);
    CHECK(strstr(engine_output, "[NEWOPT:") != NULL);
    CHECK(build_options_calls == 2);
    return EXIT_SUCCESS;
}
