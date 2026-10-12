#include "support/probe_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_probe_motion();
    contact_steps = 1000;
    CHECK(probe_to_one_mm((gc_parser_flags_t){0}) == GCProbe_FailEnd);
    CHECK(!sys.flags.probe_succeeded);
    CHECK(sys.probe_position[X_AXIS] == 80);
    CHECK(sys.alarm == Alarm_ProbeFailContact);
    CHECK(state_get() == STATE_ALARM);
    CHECK(plan_get_current_block() == NULL);
    CHECK(completed_calls == 1);
    return EXIT_SUCCESS;
}
