#include "support/motion_program_host.h"
#include "check.h"

int main(void)
{
    prepare_motion_program(); settings.axis[X_AXIS].jerk=216000;
    queue_motion_program("G1X10F100"); state_set(STATE_CYCLE); CHECK(state_get()==STATE_CYCLE);
    CHECK(!settings_override_jerk(X_AXIS,2)); NEAR(settings.axis[X_AXIS].jerk,216000);
    CHECK(!settings_override_jerk(X_AXIS,0)); NEAR(settings.axis[X_AXIS].jerk,216000);
    return EXIT_SUCCESS;
}
