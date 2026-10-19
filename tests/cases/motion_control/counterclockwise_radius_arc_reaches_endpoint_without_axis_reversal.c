#include "support/motion_program_host.h"
int main(void)
{
    prepare_motion_program();
    queue_motion_program("G3X1Y1R1F100");
    execute_motion_program();
    CHECK(sys.position[X_AXIS] == 80 && sys.position[Y_AXIS] == 80);
    CHECK(physical_position[X_AXIS] == 80 && physical_position[Y_AXIS] == 80);
    CHECK(axis_pulses[X_AXIS] == 80 && axis_pulses[Y_AXIS] == 80);
    return EXIT_SUCCESS;
}
