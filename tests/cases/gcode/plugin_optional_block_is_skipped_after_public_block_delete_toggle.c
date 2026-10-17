#include "support/motion_program_host.h"
static bool plugin_connected(void) { return true; }
int main(void)
{
    prepare_motion_program();
    hal.stream.is_connected = plugin_connected;
    char toggle[] = "$B", optional[] = "/G1X10F100";
    CHECK(system_execute_line(toggle, hal.stream.write) == Status_OK);
    CHECK(sys.flags.block_delete_enabled);
    CHECK(gc_execute_block(optional) == Status_OK);
    CHECK(plan_get_current_block() == NULL);
    NEAR(gc_state.position[X_AXIS], 0);
    queue_motion_program("G1X1F100");
    execute_motion_program();
    CHECK(axis_pulses[X_AXIS] == 80 && physical_position[X_AXIS] == 80);
    CHECK(sys.position[X_AXIS] == 80);
    return EXIT_SUCCESS;
}
