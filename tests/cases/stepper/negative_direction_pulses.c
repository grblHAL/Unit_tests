#include "support/stepper_host.h"
#include "check.h"

int main(void)
{
    prepare_stepper();
    run_stepper_move(-1, .5f, 0);
    CHECK(sys.position[X_AXIS] == -80);
    CHECK(sys.position[Y_AXIS] == 40);
    CHECK(axis_pulses[X_AXIS] == 80);
    CHECK(axis_pulses[Y_AXIS] == 40);
    return EXIT_SUCCESS;
}
