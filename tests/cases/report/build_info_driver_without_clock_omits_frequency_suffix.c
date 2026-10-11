#include "support/build_report_host.h"
#include "check.h"

int main(void)
{
    prepare_build_report();
    hal.info = "fixture driver";
    hal.f_mcu = 0;
    build_report(true);
    CHECK(strstr(engine_output, "[DRIVER:fixture driver]" ASCII_EOL) != NULL);
    CHECK(strstr(engine_output, "MHz]") == NULL);
    return EXIT_SUCCESS;
}
