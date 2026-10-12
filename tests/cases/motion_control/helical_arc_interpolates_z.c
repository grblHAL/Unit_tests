#include "support/motion_program_host.h"
#include "check.h"

int main(void)
{
    prepare_motion_program();
    queue_motion_program("G3X1Y1Z1J1F100");
    execute_motion_program();
    CHECK(sys.position[X_AXIS] == 80);
    CHECK(sys.position[Y_AXIS] == 80);
    CHECK(sys.position[Z_AXIS] == 80);
    CHECK(axis_pulses[Z_AXIS] == 80);
    return EXIT_SUCCESS;
}
