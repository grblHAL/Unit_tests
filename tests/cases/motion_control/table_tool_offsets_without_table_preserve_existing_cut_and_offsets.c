#include "support/queued_motion_rejection_host.h"
int main(void)
{
    prepare_motion_program();
    grbl.tool_table.n_tools = 0;
    queue_motion_program("G1X1F100");
    plan_block_t *first = plan_get_current_block();
    unsigned available = plan_get_block_buffer_available();
    char primary[] = "G43H1";
    CHECK(gc_execute_block(primary) == Status_GcodeUnsupportedCommand);
    CHECK(plan_get_current_block() == first && plan_get_block_buffer_available() == available);
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        NEAR(gc_state.modal.tool_length_offset[axis], 0);
    check_rejected_block_preserves_queued_motion("G43.2H1", Status_GcodeUnsupportedCommand);
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        NEAR(gc_state.modal.tool_length_offset[axis], 0);
    return EXIT_SUCCESS;
}
