#include "support/tool_offset_host.h"
#include "check.h"

int main(void)
{
    prepare_offset_tool();
    for(unsigned axis = 0; axis < N_AXIS; axis++) gc_state.modal.tool_length_offset[axis] = 10;
    char block[] = "G43H1";
    CHECK(gc_execute_block(block) == Status_OK);
    for(unsigned axis = 0; axis < N_AXIS; axis++) NEAR(gc_state.modal.tool_length_offset[axis], 2 + axis);
    CHECK(gc_state.tool->tool_id == 0);
    return EXIT_SUCCESS;
}
