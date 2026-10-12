#include "support/canned_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_canned_motion();
    execute_canned("G98G81Z-1R-0.5F100");
    CHECK(sys.position[Z_AXIS] == 0 && physical_position[Z_AXIS] == 0);
    CHECK(axis_pulses[Z_AXIS] == 160);
    return EXIT_SUCCESS;
}
