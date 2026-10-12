#include "support/canned_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_canned_motion();
    settings.g73_retract = 0.1f;
    execute_canned("G73Z-1R0Q0.5F100");
    CHECK(sys.position[Z_AXIS] == 0 && axis_pulses[Z_AXIS] == 176);
    CHECK(engine_ticks == 500);
    return EXIT_SUCCESS;
}
