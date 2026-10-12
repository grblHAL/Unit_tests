#include "support/tool_change_host.h"
#include "check.h"

int main(void)
{
    prepare_tool_change();
    start_manual_change();
    sys.flags.probe_succeeded = false;
    grbl.on_probe_completed();
    CHECK(strstr(engine_output, "Probe failed, try again.") != NULL);
    CHECK(gc_state.modal.tool_length_offset[Z_AXIS] == 0.0f);
    CHECK(gc_state.tool_change);
    return EXIT_SUCCESS;
}
