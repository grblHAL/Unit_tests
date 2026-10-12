#include "support/probe_motion_host.h"
#include "check.h"
static unsigned setter_on_calls, setter_off_calls, start_calls;
static bool toolsetter(tool_data_t *tool, coord_data_t *position, bool at_fixture, bool on) { CHECK(tool == NULL); CHECK(position == NULL); CHECK(at_fixture); if(on) setter_on_calls++; else setter_off_calls++; return on; }
static bool probe_started(axes_signals_t axes, float *target, plan_line_data_t *data) { CHECK(axes.mask == X_AXIS_BIT); NEAR(target[X_AXIS],1); CHECK(data->condition.probing_toolsetter); CHECK(setter_on_calls == 1); start_calls++; return true; }
int main(void)
{
    prepare_probe_motion();
    settings.mode = Mode_Lathe;
    sys.homed.mask = X_AXIS_BIT | Y_AXIS_BIT;
    grbl.on_probe_toolsetter = toolsetter;
    grbl.on_probe_start = probe_started;
    CHECK(probe_to_one_mm((gc_parser_flags_t){0}) == GCProbe_Found);
    CHECK(setter_on_calls == 1 && setter_off_calls == 1);
    CHECK(start_calls == 1);
    CHECK(completed_calls == 1);
    return EXIT_SUCCESS;
}
