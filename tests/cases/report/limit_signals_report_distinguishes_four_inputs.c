#include "support/report_host.h"
#include "check.h"
static limit_signals_t limit_report_inputs(void)
{
    return (limit_signals_t){.min = {.mask = 1}, .max = {.mask = 2}, .min2 = {.mask = 4}, .max2 = {.mask = 3}};
}

int main(void)
{
    prepare_report();
    hal.limits.get_state = limit_report_inputs;
    CHECK(report_current_limit_state(STATE_IDLE, NULL) == Status_OK);
    CHECK(strcmp(engine_output, "[LIMITS:X,Y,Z,XY]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
