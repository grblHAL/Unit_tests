#include "support/motion_program_host.h"
#include "check.h"

int main(void)
{
    prepare_motion_program();
    queue_motion_program("G5.1X1Y1I1J0F100");
    execute_motion_program();
    CHECK(sys.position[X_AXIS] == 80);
    CHECK(sys.position[Y_AXIS] == 80);
    CHECK(sys.position[Z_AXIS] == 0);
    CHECK(axis_pulses[X_AXIS] == 80);
    CHECK(axis_pulses[Y_AXIS] == 80);
    return EXIT_SUCCESS;
}
