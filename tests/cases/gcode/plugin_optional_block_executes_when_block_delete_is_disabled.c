#include "support/motion_program_host.h"
int main(void)
{
    prepare_motion_program();
    CHECK(!sys.flags.block_delete_enabled);
    queue_motion_program("/G1X1F100");
    execute_motion_program();
    CHECK(axis_pulses[X_AXIS] == 80 && sys.position[X_AXIS] == 80);
    CHECK(physical_position[X_AXIS] == 80);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
