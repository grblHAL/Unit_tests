#include "support/tool_change_host.h"
#include "check.h"

int main(void)
{
    prepare_tool_change();
    start_manual_change();
    sys.tlo_reference_set.mask = Z_AXIS_BIT;
    sys.tlo_reference[Z_AXIS] = -160;
    sys.probe_position[Z_AXIS] = -80;
    sys.flags.probe_succeeded = true;
    grbl.on_probe_completed();
    CHECK(gc_state.modal.tool_length_offset[Z_AXIS] == 1.0f);
    CHECK(gc_state.modal.tool_offset_mode == ToolLengthOffset_EnableDynamic);
    CHECK(gc_state.modal.tool_length_offset[X_AXIS] == 0.0f);
    return EXIT_SUCCESS;
}
