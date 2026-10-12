#include "support/canned_motion_host.h"
#include "spindle_control.h"
#include "check.h"

int main(void)
{
    prepare_canned_motion();
    CHECK(!spindle_get(0)->cap.at_speed);
    CHECK(canned_block("G84Z0R1P0F100") == Status_GcodeUnsupportedCommand);
    CHECK(plan_get_current_block() == NULL);
    CHECK(axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
