#include "support/stepper_host.h"
#include "check.h"

int main(void)
{
    prepare_stepper();
    run_stepper_move(0, 0, -1);
    CHECK(sys.position[Z_AXIS] == -80);
    CHECK(axis_pulses[X_AXIS] == 0);
    CHECK(axis_pulses[Y_AXIS] == 0);
    CHECK(axis_pulses[Z_AXIS] == 80);
    return EXIT_SUCCESS;
}
