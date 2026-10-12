#include "support/build_report_host.h"
#include "check.h"

int main(void)
{
    prepare_build_report();
    build_report(true);
    CHECK(strstr(engine_output, "[AXS:8:XYZABCUV]" ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
