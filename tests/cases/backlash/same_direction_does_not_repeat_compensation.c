#include "support/backlash_host.h"
#include "check.h"

int main(void)
{
    prepare_backlash();
    queue_motion_program("G1X1F100");
    queue_motion_program("G1X2F100");
    execute_motion_program();
    CHECK(axis_pulses[X_AXIS] == 168);
    CHECK(sys.position[X_AXIS] == 160);
    return EXIT_SUCCESS;
}
