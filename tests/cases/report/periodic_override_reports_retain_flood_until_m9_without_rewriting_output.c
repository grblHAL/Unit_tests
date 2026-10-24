#include "support/coolant_host.h"
#include <string.h>

static void poll_status(void)
{
    engine_output[0] = '\0';
    report_realtime_status(hal.stream.write, &hal.stream.report);
}

int main(void)
{
    prepare_coolant();
    hal.coolant_cap.flood = true;
    settings.status_report.overrides = true;
    char start[] = "M8", stop[] = "M9";
    CHECK(gc_execute_block(start) == Status_OK);
    CHECK(actual_coolant.flood && gc_state.modal.coolant.flood);
    unsigned writes = coolant_calls, refreshes = 0;
    for(unsigned poll = 0; poll <= 2 * REPORT_OVERRIDE_REFRESH_IDLE_COUNT; poll++) {
        poll_status();
        if(strstr(engine_output, "|Ov:")) {
            CHECK(strstr(engine_output, "|A:F") != NULL);
            refreshes++;
        }
        CHECK(actual_coolant.flood && coolant_calls == writes);
    }
    CHECK(refreshes >= 2);
    CHECK(gc_execute_block(stop) == Status_OK);
    CHECK(actual_coolant.mask == 0 && gc_state.modal.coolant.mask == 0);
    CHECK(coolant_calls == writes + 1);
    poll_status();
    CHECK(strstr(engine_output, "|A:") != NULL);
    CHECK(strstr(engine_output, "|A:F") == NULL);
    CHECK(coolant_calls == writes + 1 && state_get() == STATE_IDLE);
    return EXIT_SUCCESS;
}
