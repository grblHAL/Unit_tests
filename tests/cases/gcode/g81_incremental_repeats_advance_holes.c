#include "support/canned_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_canned_motion();
    execute_canned("G91G81X1Z-1R0L3F100");
    CHECK(sys.position[X_AXIS] == 240 && axis_pulses[X_AXIS] == 240);
    CHECK(sys.position[Z_AXIS] == 0 && axis_pulses[Z_AXIS] == 480);
    return EXIT_SUCCESS;
}
