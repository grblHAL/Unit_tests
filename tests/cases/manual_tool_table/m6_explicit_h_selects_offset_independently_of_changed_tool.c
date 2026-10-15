#include "support/manual_table_tool_change_host.h"

int main(void)
{
    prepare_manual_table_change();
    char change[] = "T3M6G43H4";
    CHECK(gc_execute_block(change) == Status_OK);
    CHECK(gc_state.g43_pending == 4);
    acknowledge_table_change();
    NEAR(gc_state.modal.tool_length_offset[Z_AXIS], 3);
    cut_with_table_offset(-160);
    return EXIT_SUCCESS;
}
