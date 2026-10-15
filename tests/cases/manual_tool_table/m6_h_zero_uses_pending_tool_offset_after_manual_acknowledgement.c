#include "support/manual_table_tool_change_host.h"

int main(void)
{
    prepare_manual_table_change();
    char change[] = "T3M6G43H0";
    CHECK(gc_execute_block(change) == Status_OK);
    CHECK(gc_state.g43_pending == 3);
    NEAR(gc_state.modal.tool_length_offset[Z_AXIS], 0);
    acknowledge_table_change();
    CHECK(gc_state.g43_pending == (tool_id_t)-1);
    NEAR(gc_state.modal.tool_length_offset[Z_AXIS], 2);
    return EXIT_SUCCESS;
}
