#include "support/boot_tool_position_reset_host.h"
int main(void)
{
    prepare_boot_tool_position_reset();
    CHECK(grbl_enter() == 0);
    CHECK(boot_tool_reset_sent && boot_tool_restart_observed);
    CHECK(boot_tool_resets_after_restart == boot_tool_resets_before_change + 1);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    CHECK(boot_reads == strlen(boot_program));
    CHECK(!HOST_PARSER_FLAGS.tool_change);
    CHECK(boot_tool_reset_z >= -40 && boot_tool_reset_z < 0);
    CHECK(sys.position[X_AXIS] == -160 && sys.position[Y_AXIS] == -240);
    CHECK(plan_get_current_block() == NULL);
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        CHECK(sys.position[axis] == boot_motor_position[axis] - boot_tool_home_offset[axis]);
    CHECK(gc_state.tool->tool_id == 0);
    return EXIT_SUCCESS;
}
