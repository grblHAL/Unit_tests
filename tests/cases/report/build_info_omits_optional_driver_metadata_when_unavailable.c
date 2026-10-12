#include "support/build_report_host.h"
#include "check.h"

int main(void)
{
    prepare_build_report();
    hal.info = hal.driver_version = hal.driver_options = hal.board = NULL;
    hal.max_step_rate = 0;
    hal.get_free_mem = NULL;
    build_report(true);
    CHECK(strstr(engine_output, "[DRIVER:") == NULL);
    CHECK(strstr(engine_output, "[DRIVER VERSION:") == NULL);
    CHECK(strstr(engine_output, "[DRIVER OPTIONS:") == NULL);
    CHECK(strstr(engine_output, "[BOARD:") == NULL);
    CHECK(strstr(engine_output, "[MAX STEP RATE:") == NULL);
    CHECK(strstr(engine_output, "[FREE MEMORY:") == NULL);
    return EXIT_SUCCESS;
}
