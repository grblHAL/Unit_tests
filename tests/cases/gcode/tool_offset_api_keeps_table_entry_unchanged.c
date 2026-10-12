#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    grbl.tool_table.n_tools = 1;
    gc_state.tool->offset.values[Z_AXIS] = 12;
    settings.axis[Z_AXIS].steps_per_mm = 80;
    gc_set_tool_offset(ToolLengthOffset_EnableDynamic, Z_AXIS, 160);
    NEAR(gc_state.modal.tool_length_offset[Z_AXIS], 2);
    NEAR(gc_state.tool->offset.values[Z_AXIS], 12);
    return EXIT_SUCCESS;
}
