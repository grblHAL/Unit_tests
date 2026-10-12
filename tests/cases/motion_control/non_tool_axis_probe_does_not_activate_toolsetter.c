#include "support/probe_motion_host.h"
#include "check.h"
static unsigned setter_calls;
static bool toolsetter(tool_data_t *tool, coord_data_t *position, bool at_fixture, bool on) { (void)tool; (void)position; (void)at_fixture; setter_calls++; return on; }
int main(void)
{
    prepare_probe_motion();
    sys.homed.mask = X_AXIS_BIT | Z_AXIS_BIT;
    grbl.on_probe_toolsetter = toolsetter;
    CHECK(probe_to_one_mm((gc_parser_flags_t){0}) == GCProbe_Found);
    CHECK(setter_calls == 0);
    return EXIT_SUCCESS;
}
