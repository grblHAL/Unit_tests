#include "support/backlash_host.h"
#include "check.h"

int main(void)
{
    prepare_backlash();
    queue_motion_program("G1X1F100");
    execute_motion_program();
    CHECK(axis_pulses[X_AXIS] == 88);
    CHECK(sys.position[X_AXIS] == 80);
    CHECK(sys.position[Y_AXIS] == 0);
    return EXIT_SUCCESS;
}
