#include "support/probe_motion_host.h"
#include "check.h"
static unsigned start_calls;
static bool probe_started(axes_signals_t axes, float *target, plan_line_data_t *data) { CHECK(axes.mask == (X_AXIS_BIT | Y_AXIS_BIT | Z_AXIS_BIT)); NEAR(target[0],1); NEAR(target[1],2); NEAR(target[2],3); NEAR(data->feed_rate,100); start_calls++; return true; }
int main(void)
{
    prepare_probe_motion();
    grbl.on_probe_start = probe_started;
    float target[N_AXIS] = {1, 2, 3};
    plan_line_data_t data;
    plan_data_init(&data);
    data.feed_rate = 100;
    data.condition.target_validated = data.condition.target_valid = true;
    CHECK(mc_probe_cycle(target, &data, (gc_parser_flags_t){0}) == GCProbe_Found);
    CHECK(start_calls == 1);
    CHECK(sys.probe_position[X_AXIS] == 40);
    CHECK(labs(sys.probe_position[Y_AXIS] - 80) <= 1);
    CHECK(labs(sys.probe_position[Z_AXIS] - 120) <= 1);
    CHECK(completed_calls == 1);
    return EXIT_SUCCESS;
}
