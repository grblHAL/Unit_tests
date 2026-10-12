#include "support/report_host.h"
#include "check.h"
static home_signals_t home_report_inputs(void) { return (home_signals_t){.a = {.mask = 1}, .b = {.mask = 2}}; }

int main(void)
{
    prepare_report();
    hal.homing.get_state = home_report_inputs;
    CHECK(report_current_home_signal_state(STATE_IDLE, NULL) == Status_OK);
    CHECK(strcmp(engine_output, "[HOMES:X,Y:L]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
