#include "support/canned_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_canned_motion();
    execute_canned("G82Z-1R0P0.1F100");
    CHECK(sys.position[Z_AXIS] == 0 && axis_pulses[Z_AXIS] == 160);
    CHECK(engine_ticks == 100);
    return EXIT_SUCCESS;
}
