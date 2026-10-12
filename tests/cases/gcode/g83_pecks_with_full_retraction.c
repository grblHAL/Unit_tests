#include "support/canned_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_canned_motion();
    execute_canned("G83Z-1R0Q0.5F100");
    CHECK(sys.position[Z_AXIS] == 0 && axis_pulses[Z_AXIS] == 240);
    CHECK(engine_ticks == 500);
    return EXIT_SUCCESS;
}
