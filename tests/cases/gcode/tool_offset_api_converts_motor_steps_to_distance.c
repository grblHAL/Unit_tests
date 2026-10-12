#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    settings.axis[Z_AXIS].steps_per_mm = 80;
    gc_set_tool_offset(ToolLengthOffset_EnableDynamic, Z_AXIS, 200);
    NEAR(gc_state.modal.tool_length_offset[Z_AXIS], 2.5f);
    NEAR(gc_state.tool->offset.values[Z_AXIS], 2.5f);
    CHECK(gc_state.modal.tool_offset_mode == ToolLengthOffset_EnableDynamic);
    return EXIT_SUCCESS;
}
