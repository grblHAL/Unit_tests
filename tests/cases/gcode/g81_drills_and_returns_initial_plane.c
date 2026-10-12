#include "support/canned_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_canned_motion();
    execute_canned("G98G81X1Y2Z-1R0F100");
    CHECK(sys.position[X_AXIS] == 80 && sys.position[Y_AXIS] == 160);
    CHECK(sys.position[Z_AXIS] == 0 && physical_position[Z_AXIS] == 0);
    CHECK(axis_pulses[Z_AXIS] == 160);
    CHECK(gc_state.modal.motion == MotionMode_CannedCycle81);
    return EXIT_SUCCESS;
}
