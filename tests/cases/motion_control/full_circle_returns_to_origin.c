#include "support/motion_program_host.h"
#include "check.h"

int main(void)
{
    prepare_motion_program();
    queue_motion_program("G2I1F100");
    execute_motion_program();
    CHECK(sys.position[X_AXIS] == 0);
    CHECK(sys.position[Y_AXIS] == 0);
    CHECK(axis_pulses[X_AXIS] > 0);
    CHECK(axis_pulses[Y_AXIS] > 0);
    CHECK(axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
