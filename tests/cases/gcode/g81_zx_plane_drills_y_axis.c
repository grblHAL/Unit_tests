#include "support/canned_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_canned_motion();
    execute_canned("G18G81X1Y-1Z2R0F100");
    CHECK(sys.position[X_AXIS] == 80 && sys.position[Z_AXIS] == 160);
    CHECK(sys.position[Y_AXIS] == 0 && axis_pulses[Y_AXIS] == 160);
    return EXIT_SUCCESS;
}
