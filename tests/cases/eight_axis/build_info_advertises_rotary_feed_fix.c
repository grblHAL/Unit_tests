#include "support/build_report_host.h"
#include "check.h"

int main(void)
{
    prepare_build_report();
    settings.flags.rotary_fix_enable = true;
    build_report(true);
    CHECK(strstr(engine_output, ",RF,") != NULL);
    return EXIT_SUCCESS;
}
