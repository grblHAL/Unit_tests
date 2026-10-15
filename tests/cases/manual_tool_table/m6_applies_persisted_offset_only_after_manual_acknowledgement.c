#include "support/manual_table_tool_change_host.h"

int main(void)
{
    prepare_manual_table_change();
    char change[] = "T3M6G43H3";
    CHECK(gc_execute_block(change) == Status_OK);
    CHECK(gc_state.tool_change && gc_state.g43_pending == 3);
    NEAR(gc_state.modal.tool_length_offset[Z_AXIS], 0);
    CHECK(axis_pulses[Z_AXIS] == 0);
    acknowledge_table_change();
    NEAR(gc_state.modal.tool_length_offset[Z_AXIS], 2);
    cut_with_table_offset(-240);
    return EXIT_SUCCESS;
}
