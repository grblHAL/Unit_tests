#include "support/homing_host.h"
#include "check.h"

int main(void)
{
    prepare_homing();
    CHECK(mc_homing_cycle((axes_signals_t){.bits = 3}) == Status_OK);
    CHECK(sys.homed.bits == 3);
    CHECK(sys.position[X_AXIS] == -10);
    CHECK(sys.position[Y_AXIS] == -10);
    CHECK(physical_position[X_AXIS] == 70);
    CHECK(physical_position[Y_AXIS] == 110);
    CHECK(axis_pulses[X_AXIS] == 110);
    CHECK(axis_pulses[Y_AXIS] == 150);
    CHECK(homing_success);
    return EXIT_SUCCESS;
}
