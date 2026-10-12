#include "support/canned_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_canned_motion();
    execute_canned("G19G81X-1Y1Z2R0F100");
    CHECK(sys.position[Y_AXIS] == 80 && sys.position[Z_AXIS] == 160);
    CHECK(sys.position[X_AXIS] == 0 && axis_pulses[X_AXIS] == 160);
    return EXIT_SUCCESS;
}
