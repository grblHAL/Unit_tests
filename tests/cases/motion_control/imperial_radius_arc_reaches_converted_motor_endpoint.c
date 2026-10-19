#include "support/motion_program_host.h"
int main(void)
{
    prepare_motion_program();
    char units[] = "G20";
    CHECK(gc_execute_block(units) == Status_OK);
    queue_motion_program("G2X0.125Y0.125R0.125F20");
    execute_motion_program();
    CHECK(sys.position[X_AXIS] == 254 && sys.position[Y_AXIS] == 254);
    CHECK(physical_position[X_AXIS] == 254 && physical_position[Y_AXIS] == 254);
    CHECK(axis_pulses[X_AXIS] == 254 && axis_pulses[Y_AXIS] == 254);
    return EXIT_SUCCESS;
}
