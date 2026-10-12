#include "support/motion_program_host.h"
#include "check.h"

int main(void)
{
    prepare_motion_program();
    settings.arc_tolerance = .05f;
    queue_motion_program("G2X1Y1R-1F100");
    execute_motion_program();
    CHECK(sys.position[X_AXIS] == 80);
    CHECK(sys.position[Y_AXIS] == 80);
    CHECK(axis_pulses[X_AXIS] > 80);
    CHECK(axis_pulses[Y_AXIS] > 80);
    return EXIT_SUCCESS;
}
