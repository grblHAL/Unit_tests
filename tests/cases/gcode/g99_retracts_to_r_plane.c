#include "support/canned_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_canned_motion();
    execute_canned("G99G81Z-1R-0.5F100");
    CHECK(sys.position[Z_AXIS] == -40 && physical_position[Z_AXIS] == -40);
    CHECK(axis_pulses[Z_AXIS] == 120);
    return EXIT_SUCCESS;
}
