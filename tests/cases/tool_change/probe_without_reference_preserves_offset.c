#include "support/tool_change_host.h"
#include "check.h"

int main(void)
{
    prepare_tool_change();
    start_manual_change();
    gc_state.modal.tool_length_offset[Z_AXIS] = 2.0f;
    sys.probe_position[Z_AXIS] = -80;
    sys.flags.probe_succeeded = true;
    grbl.on_probe_completed();
    CHECK(gc_state.modal.tool_length_offset[Z_AXIS] == 2.0f);
    return EXIT_SUCCESS;
}
