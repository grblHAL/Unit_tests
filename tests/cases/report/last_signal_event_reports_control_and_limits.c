#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    sys.last_event.control.reset = true;
    sys.last_event.limits.min.mask = 1;
    sys.last_event.limits.max.mask = 2;
    CHECK(report_last_signals_event(STATE_IDLE, NULL) == Status_OK);
    CHECK(strcmp(engine_output, "[LASTEVENTS:R,X,Y,,]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
