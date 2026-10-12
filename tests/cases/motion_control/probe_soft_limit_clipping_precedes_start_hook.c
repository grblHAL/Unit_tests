#include "support/probe_motion_host.h"
#include "check.h"
static unsigned start_calls;
static bool probe_started(axes_signals_t axes, float *target, plan_line_data_t *data) { CHECK(axes.mask == X_AXIS_BIT); NEAR(target[X_AXIS], .75f); NEAR(data->feed_rate, 100); CHECK(!hal.probe.get_state().is_probing); start_calls++; return true; }
int main(void)
{
    prepare_probe_motion();
    settings.probe.soft_limited = true;
    sys.homed.mask = X_AXIS_BIT;
    sys.work_envelope.min.x = 0;
    sys.work_envelope.max.x = .75f;
    grbl.on_probe_start = probe_started;
    CHECK(probe_to_one_mm((gc_parser_flags_t){0}) == GCProbe_Found);
    CHECK(start_calls == 1);
    CHECK(sys.probe_position[X_AXIS] == 40);
    CHECK(completed_calls == 1);
    return EXIT_SUCCESS;
}
