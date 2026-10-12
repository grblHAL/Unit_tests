#include "support/canned_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_canned_motion();
    execute_canned("G81X1Z-1R0F100");
    execute_canned("X2");
    CHECK(sys.position[X_AXIS] == 160 && axis_pulses[X_AXIS] == 160);
    CHECK(sys.position[Z_AXIS] == 0 && axis_pulses[Z_AXIS] == 320);
    return EXIT_SUCCESS;
}
