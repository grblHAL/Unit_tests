#include "support/build_report_host.h"
#include "check.h"

int main(void)
{
    prepare_build_report();
    build_report(false);
    CHECK(strstr(engine_output, "[VER:") != NULL);
    CHECK(strstr(engine_output, "[OPT:") != NULL);
    CHECK(strstr(engine_output, "[NEWOPT:") == NULL);
    CHECK(strstr(engine_output, "[FIRMWARE:") == NULL);
    CHECK(strstr(engine_output, "[AXS:") == NULL);
    CHECK(build_options_calls == 0);
    return EXIT_SUCCESS;
}
