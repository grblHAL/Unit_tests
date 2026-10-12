#include "support/program_end_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    prepare_program_end(false);
    CHECK(program_block("G43.1Z5") == Status_OK);
    CHECK(program_block("M70") == Status_OK);
    CHECK(program_block("G49") == Status_OK);
    CHECK(program_block("M72") == Status_OK);
    CHECK(gc_state.modal.tool_offset_mode == ToolLengthOffset_EnableDynamic);
    NEAR(gc_state.modal.tool_length_offset[Z_AXIS], 5.0f);
    ngc_modal_state_invalidate();
    return EXIT_SUCCESS;
}
