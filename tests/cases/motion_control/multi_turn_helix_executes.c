#include "support/motion_program_host.h"
#include "check.h"

int main(void)
{
    prepare_motion_program();
    settings.arc_tolerance = .08f;
    queue_motion_program("G3X1Y1Z1J1P2F100");
    execute_motion_program();
    CHECK(sys.position[X_AXIS] == 80);
    CHECK(sys.position[Y_AXIS] == 80);
    CHECK(sys.position[Z_AXIS] == 80);
    CHECK(axis_pulses[X_AXIS] > 80);
    CHECK(axis_pulses[Y_AXIS] > 80);
    CHECK(axis_pulses[Z_AXIS] == 80);
    return EXIT_SUCCESS;
}
