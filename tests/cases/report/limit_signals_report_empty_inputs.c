#include "support/report_host.h"
#include "check.h"
static limit_signals_t empty_limit_inputs(void) { return (limit_signals_t){0}; }

int main(void)
{
    prepare_report();
    hal.limits.get_state = empty_limit_inputs;
    CHECK(report_current_limit_state(STATE_IDLE, NULL) == Status_OK);
    CHECK(strcmp(engine_output, "[LIMITS:,,,]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
