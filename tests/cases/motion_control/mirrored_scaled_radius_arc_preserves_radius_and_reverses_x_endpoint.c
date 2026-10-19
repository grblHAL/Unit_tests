#include "support/motion_program_host.h"
int main(void)
{
    prepare_motion_program();
    char scaling[] = "G51X-2Y2";
    CHECK(gc_execute_block(scaling) == Status_OK);
    queue_motion_program("G2X1Y1R1F100");
    execute_motion_program();
    CHECK(sys.position[X_AXIS] == -160 && sys.position[Y_AXIS] == 160);
    CHECK(physical_position[X_AXIS] == -160 && physical_position[Y_AXIS] == 160);
    CHECK(axis_pulses[X_AXIS] == 160 && axis_pulses[Y_AXIS] == 160);
    return EXIT_SUCCESS;
}
