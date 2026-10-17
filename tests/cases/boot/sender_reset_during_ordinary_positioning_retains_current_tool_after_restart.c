#include "support/boot_tool_position_reset_host.h"
int main(void)
{
    prepare_boot_tool_position_reset();
    boot_reset_ordinary_motion = true;
    boot_program = "$H\nG0X-2Y-3Z-1\n$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(boot_tool_reset_sent && boot_tool_restart_observed);
    CHECK(!boot_tool_positioning);
    CHECK(boot_tool_resets_after_restart == boot_tool_resets_before_change + 1);
    CHECK(gc_state.tool->tool_id == 0 && !gc_state.tool_change);
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        CHECK(sys.position[axis] == boot_motor_position[axis] - boot_tool_home_offset[axis]);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
