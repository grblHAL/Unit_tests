#include "support/stepper_host.h"
#include "check.h"

int main(void)
{
    prepare_stepper();
    run_stepper_move(3, 4, 0);
    CHECK(sys.position[X_AXIS] == 240);
    CHECK(sys.position[Y_AXIS] == 320);
    CHECK(axis_pulses[X_AXIS] == 240);
    CHECK(axis_pulses[Y_AXIS] == 320);
    CHECK(axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
