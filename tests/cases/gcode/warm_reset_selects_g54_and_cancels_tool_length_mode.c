#include "support/named_parameter_host.h"

int main(void)
{
    engine_parser_prepare();
    CHECK(named_parameter_block("G55G43.1Z4") == Status_OK);
    CHECK(named_parameter_block("G92X3") == Status_OK);
    float g92_x = gc_state.g92_offset.coord.values[X_AXIS];
    sys.cold_start = false;
    gc_init(false);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G54);
    CHECK(gc_state.modal.tool_offset_mode == ToolLengthOffset_Cancel);
    NEAR(gc_state.modal.tool_length_offset[Z_AXIS], 4);
    NEAR(gc_state.g92_offset.coord.values[X_AXIS], g92_x);
    return EXIT_SUCCESS;
}
