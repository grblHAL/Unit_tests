#include "support/motion_program_host.h"
#include "check.h"

int main(void)
{
    prepare_motion_program(); settings.axis[X_AXIS].jerk=216000; settings.axis[Y_AXIS].jerk=648000;
    CHECK(settings_override_jerk(X_AXIS,2)); NEAR(settings.axis[X_AXIS].jerk,432000); NEAR(settings.axis[Y_AXIS].jerk,648000);
    CHECK(settings_override_jerk(Y_AXIS,4)); NEAR(settings.axis[Y_AXIS].jerk,864000);
    CHECK(settings_override_jerk(X_AXIS,0)); NEAR(settings.axis[X_AXIS].jerk,216000); NEAR(settings.axis[Y_AXIS].jerk,864000);
    return EXIT_SUCCESS;
}
