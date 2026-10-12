#include "support/probe_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_probe_motion();
    contact_steps = 1000;
    CHECK(probe_to_one_mm((gc_parser_flags_t){.probe_is_no_error = true}) == GCProbe_FailEnd);
    CHECK(!sys.flags.probe_succeeded);
    CHECK(sys.position[X_AXIS] == 80);
    CHECK(sys.probe_position[X_AXIS] == 80);
    CHECK(sys.alarm == Alarm_None);
    CHECK(completed_calls == 1);
    return EXIT_SUCCESS;
}
