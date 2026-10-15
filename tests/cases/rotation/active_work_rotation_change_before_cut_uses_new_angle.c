#include "support/motion_program_host.h"

int main(void)
{
    prepare_motion_program();
    char setup1[] = "G10L2P1R90"; CHECK(gc_execute_block(setup1) == Status_OK);
    char setup2[] = "G10L2P1R180"; CHECK(gc_execute_block(setup2) == Status_OK);
    CHECK(axis_pulses[X_AXIS] == 0 && axis_pulses[Y_AXIS] == 0);
    queue_motion_program("G1X3Y4F100");
    execute_motion_program();
    CHECK(physical_position[X_AXIS] == -240);
    CHECK(physical_position[Y_AXIS] == -320);
    CHECK(sys.position[X_AXIS] == -240);
    CHECK(sys.position[Y_AXIS] == -320);
    CHECK(axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
