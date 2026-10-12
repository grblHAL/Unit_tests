#include "support/build_report_host.h"
#include "check.h"

int main(void)
{
    prepare_build_report();
    hal.info = "fixture driver";
    hal.f_mcu = 120;
    hal.driver_version = "1.2.3";
    hal.driver_options = "option-a";
    hal.board = "fixture board";
    hal.max_step_rate = 250000;
    build_report(true);
    CHECK(strstr(engine_output, "[DRIVER:fixture driver@120MHz]" ASCII_EOL) != NULL);
    CHECK(strstr(engine_output, "[DRIVER VERSION:1.2.3]" ASCII_EOL) != NULL);
    CHECK(strstr(engine_output, "[DRIVER OPTIONS:option-a]" ASCII_EOL) != NULL);
    CHECK(strstr(engine_output, "[BOARD:fixture board]" ASCII_EOL) != NULL);
    CHECK(strstr(engine_output, "[MAX STEP RATE:250000 Hz]" ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
