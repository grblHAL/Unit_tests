#include "support/boot_host.h"
#if N_TOOLS != 0
#error This case verifies the normal build without a compiled tool table
#endif
int main(void)
{
    boot_program = "G10L0\n$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(grbl.tool_table.n_tools == 0 && grbl.tool_table.reload != NULL);
    CHECK(gc_state.tool->tool_id == 0);
    CHECK(strstr(engine_output, "error:") == NULL);
    CHECK(strstr(engine_output, "[GC:") != NULL);
    CHECK(plan_get_current_block() == NULL && sys.alarm == Alarm_None);
    for(unsigned axis = 0; axis < N_AXIS; axis++) CHECK(sys.position[axis] == 0);
    return EXIT_SUCCESS;
}
