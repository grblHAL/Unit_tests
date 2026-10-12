#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    gc_state.modal.tool_length_offset[X_AXIS] = 7;
    gc_state.modal.tool_length_offset[Y_AXIS] = -3;
    settings.axis[Z_AXIS].steps_per_mm = 80;
    gc_set_tool_offset(ToolLengthOffset_EnableDynamic, Z_AXIS, -160);
    NEAR(gc_state.modal.tool_length_offset[X_AXIS], 7);
    NEAR(gc_state.modal.tool_length_offset[Y_AXIS], -3);
    NEAR(gc_state.modal.tool_length_offset[Z_AXIS], -2);
    return EXIT_SUCCESS;
}
